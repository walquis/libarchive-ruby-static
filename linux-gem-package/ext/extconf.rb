require 'fileutils'
include FileUtils
require 'rbconfig'  # For RbConfig::CONFIG

def patch_libarchive_reader_for_mac
  return unless `uname` =~ /Darwin/
  text = File.read("libarchive_reader.c")
  File.open("libarchive_reader.c", 'w') { |f| f.puts text.gsub(/_close\(fd\);/, "close(fd);") }
end

debug = (ARGV[0]=="debug") # Set true to bypass all the removing, unpacking and sh-configure'ing

cfg = RbConfig::CONFIG # "c" for short...

zlib = 'zlib-1.2.5'
libar = 'libarchive-2.8.4'
wrapper = 'libarchive-0.1.1'

ruby_root = File.dirname cfg['bindir']  # For the Makefiles

build_root = Dir.getwd

# Build zlib...
puts "Building #{zlib}..."
cd zlib do
  system "sh configure" unless debug or File.exist? 'Makefile'
  exit $?.exitstatus unless $?.nil? or $?.exitstatus == 0
  system "make libz.a"
  exit $?.exitstatus if $?.exitstatus > 0
end

ENV['CFLAGS'] = "-I#{build_root}/#{zlib} -fPIC"
ENV['ZLIB_A'] = "#{build_root}/#{zlib}/libz.a"

# Build libarchive...
puts "Building #{libar}..."
cd libar do
  unless debug
    system "sh configure --with-zlib=yes --without-xml2 --without-expat --without-openssl --without-bz2lib" unless debug or File.exist? 'Makefile'
    exit $?.exitstatus unless $?.nil? or $?.exitstatus == 0
  end
  cd 'libarchive' do
    system "make -f ../../libarchive-static-makefile"
    exit $?.exitstatus unless $?.nil? or $?.exitstatus == 0
  end
end

# Build the Ruby wrapper around libarchive and zlib...
puts "Building wrapper #{wrapper}..."
ENV.delete 'LIBS'
ENV['LDFLAGS'] = "-L#{ruby_root}/lib -L#{build_root}/#{zlib} -L#{build_root}/#{libar}/libarchive -larchive"
ENV['CFLAGS']  = "-fPIC -I#{build_root}/#{libar}/libarchive \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/#{cfg['arch']} \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/ruby/backward \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']} \
-I#{cfg['archdir']} "

cd "#{wrapper}/ext" do
  patch_libarchive_reader_for_mac
  unless debug
    system "sh configure" unless debug or File.exist? 'Makefile'
    exit $?.exitstatus unless $?.nil? or $?.exitstatus == 0
  end
  system "make -e -f ../../libarchive-static-wrapper-makefile"
  exit $?.exitstatus if $?.exitstatus > 0
end

exit 0
