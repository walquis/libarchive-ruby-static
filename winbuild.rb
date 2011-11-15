require 'fileutils'
include FileUtils
require 'rbconfig'

debug = (ARGV[0]=="debug") # Set true to bypass all the removing, unpacking and sh-configure'ing

unzip = '"C:/Program Files/7-Zip/7z.exe" x'
cfg = RbConfig::CONFIG # "c" for short...
rbver = RUBY_VERSION =~ /1.8/ ? "-ruby186" : ""
bldver = ( ENV['BUILD_VERSION'] ||= '1.0.3' )
zlib = 'zlib-1.2.5'
libar = 'libarchive-2.8.4'
wrapper = 'libarchive-0.1.1'
ruby_root = File.dirname cfg['bindir']  # For the Makefiles
build_root = Dir.getwd

unless debug
  rm_rf libar if File.directory? libar
  system "#{unzip} #{libar}.zip"

  rm_rf zlib if File.directory? zlib
  system "#{unzip} #{zlib}.zip"

  rm_rf wrapper if File.directory? wrapper
  system "gem unpack #{wrapper}.gem"
end

ENV['PATH']   = "c:/rubydev/bin;c:/rubydev/mingw/bin;#{ENV['PATH']}"

# Build zlib...
cd zlib do
  system "make -f win32/Makefile.gcc"
  exit $?.exitstatus if $?.exitstatus > 0
end


# Build libarchive...
ENV['CFLAGS'] = "-I#{build_root}/#{zlib}"
ENV['PATH']   = "c:/rubydev/bin;c:/rubydev/mingw/bin;#{ENV['PATH']}"
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
ENV.delete 'LIBS'  # Can cause problems if it's set to anything
ENV['LDFLAGS'] = "-L#{ruby_root}/lib -L#{build_root}/#{zlib} -L#{build_root}/#{libar}/libarchive -larchive -l#{cfg['RUBY_SO_NAME']} -lshell32 -lws2_32 -lzdll"
ENV['CFLAGS']  = "-I#{build_root}/#{libar}/libarchive \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/#{cfg['arch']} \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']}/ruby/backward \
-I#{cfg['includedir']}/ruby-#{cfg['ruby_version']} \
-I#{cfg['archdir']} \
-DLIBARCHIVE_EXPORTS -D__USE_MINGW_ANSI_STDIO"

cd "#{wrapper}/ext" do
  unless debug
    system "sh configure"
    exit $?.exitstatus if $?.exitstatus > 0
  end
  system "make -e -f ../../libarchive-static-wrapper-makefile"
  exit $?.exitstatus if $?.exitstatus > 0
end

# Package gem for mswin32 and mingw32 platforms
cd "windows-gem-package" do
  File.directory? 'lib' or mkdir "lib"
  cp "#{build_root}/#{wrapper}/ext/libarchive_ruby.so", "lib"
  ['mingw32', 'mswin32'].each do |w|
    ENV['RUBY_PLATFORM'] = "i386-#{w}"
    system "gem build libarchive-static-win.gemspec"
    exit $?.exitstatus if $?.exitstatus > 0
    # Gem builder gets the filename wrong ("x86"), which upsets the gem indexer (rubygems version on both machines is 1.3.7).
    mv "libarchive-static#{rbver}-#{bldver}-x86-#{w}.gem", "libarchive-static#{rbver}-#{bldver}-i386-#{w}.gem"
  end
end

exit 0
