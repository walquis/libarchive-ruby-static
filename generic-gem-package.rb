require 'fileutils'
include FileUtils
require 'rbconfig'  # For RbConfig::CONFIG

debug = (ARGV[0]=="debug") # Set true to bypass all the removing, unpacking and sh-configure'ing

cfg = RbConfig::CONFIG # "c" for short...

zlib = 'zlib-1.2.5'
libar = 'libarchive-2.8.4'
wrapper = 'libarchive-0.1.1'

ruby_root = File.dirname cfg['bindir']  # For the Makefiles

build_root = Dir.getwd

unless debug
  rm_rf libar if File.directory? libar
  system "unzip #{libar}.zip"

  rm_rf zlib if File.directory? zlib
  system "unzip #{zlib}.zip"

  rm_rf wrapper if File.directory? wrapper
  system "gem unpack #{wrapper}.gem"
end
exit $?.exitstatus if $?.exitstatus > 0

# Set up the linux gem package directory.

cd 'generic-gem-package/ext' do
  rm_rf zlib
  mkdir_p zlib
  cp Dir["../../#{zlib}/*.[ch]"], zlib
  cp ["../../#{zlib}/configure", "../../#{zlib}/Makefile.in"], zlib
  rm_rf libar
  mkdir_p "#{libar}/libarchive"
  cp_r Dir["../../#{libar}/libarchive/*.[ch]"], "#{libar}/libarchive"
  mkdir_p "#{libar}/build"
  cp_r "../../#{libar}/build/autoconf", "#{libar}/build"
  cp_r "../../#{libar}/build/pkgconfig", "#{libar}/build"
  cp ["../../#{libar}/configure", "../../#{libar}/Makefile.in", "../../#{libar}/config.h.in"], libar

  rm_rf wrapper
  cp_r "../../#{wrapper}", "."
  cp ["../../libarchive-static-makefile", "../../libarchive-static-wrapper-makefile"], "."
end

# Package the gem.
cd 'generic-gem-package' do
  ENV['BUILD_VERSION'] ||= '1.0.0'
  system "gem build libarchive-static.gemspec"
  exit $?.exitstatus if $?.exitstatus > 0
end

exit 0
