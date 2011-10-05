require 'fileutils'
include FileUtils
require 'rbconfig'  # For RbConfig::CONFIG

debug = (ARGV[0]=="debug") # Set true to bypass all the removing, unpacking and sh-configure'ing

unzip = {
  :win => '"C:/Program Files/7-Zip/7z.exe" x',
  :linux => "unzip"
}

cfg = RbConfig::CONFIG # "c" for short...

zlib = 'zlib-1.2.5'
libar = 'libarchive-2.8.4'
wrapper = 'libarchive-0.1.1'

os = ENV['OS']=~/Windows/i ? :win : :linux

ruby_root = File.dirname cfg['bindir']  # For the Makefiles

build_root = Dir.getwd

unless debug
  rm_rf libar if File.directory? libar
  system "#{unzip[os]} #{libar}.zip"

  rm_rf zlib if File.directory? zlib
  system "#{unzip[os]} #{zlib}.zip"

  rm_rf wrapper if File.directory? wrapper
  system "gem unpack #{wrapper}.gem"
end

# Build zlib...
cd zlib do
  if os==:win
    ENV['PATH']   = "c:/rubydev/bin;c:/rubydev/mingw/bin;#{ENV['PATH']}"
    system "make -f win32/Makefile.gcc"
    exit $?.exitstatus if $?.exitstatus > 0
  else
    system "sh configure"
    exit $?.exitstatus if $?.exitstatus > 0
    system "make"
    exit $?.exitstatus if $?.exitstatus > 0
  end
end

ENV['CFLAGS'] = "-I#{build_root}/#{zlib}"
if os==:win
  ENV['PATH']   = "c:/rubydev/bin;c:/rubydev/mingw/bin;#{ENV['PATH']}"
  ENV['ZLIB_A'] = "#{build_root}/#{zlib}/libzdll.a"
else
  ENV['ZLIB_A'] = "#{build_root}/#{zlib}/libz.a"
  ENV['CFLAGS'] += " -fPIC"
end

# Build libarchive...
cd libar do
  unless debug
    system "sh configure --with-zlib=yes --without-xml2 --without-expat"
    exit $?.exitstatus if $?.exitstatus > 0
  end
  cd 'libarchive' do
    system "make -f ../../libarchive-static-makefile"
    exit $?.exitstatus if $?.exitstatus > 0
  end
end

# Build the Ruby wrapper around libarchive and zlib...
ENV.delete 'LIBS'
ENV['LDFLAGS'] = "-L#{ruby_root}/lib -L#{build_root}/#{zlib} -L#{build_root}/#{libar}/libarchive -larchive"
ENV['CFLAGS']  = "-I#{build_root}/#{libar}/libarchive \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/#{cfg['arch']} \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/ruby/backward \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']} \
-I#{cfg['archdir']} "

if os==:win
  ENV['LDFLAGS']  += " -l#{cfg['RUBY_SO_NAME']} -lshell32 -lws2_32"
  ENV['CFLAGS']   += " -DLIBARCHIVE_EXPORTS -D__USE_MINGW_ANSI_STDIO"
else
  ENV['CFLAGS']   += " -fPIC"
end

cd "#{wrapper}/ext" do
  unless debug
    system "sh configure"
    exit $?.exitstatus if $?.exitstatus > 0
  end
  system "make -e -f ../../libarchive-static-wrapper-makefile"
  exit $?.exitstatus if $?.exitstatus > 0
end

exit 0
