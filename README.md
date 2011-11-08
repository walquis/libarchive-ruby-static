A libarchive Ruby wrapper (derived by unpacking libarchive-0.1.1.gem) that has its libarchive and zlib dependencies statically linked with it.

At my company, we use libarchive as a pre-requisite for a dependency manager named [Fig](http://github.com/mfoemmel/fig) on various platforms--Linux RedHat and Ubuntu, Windows--and Ruby 1.8.6 and 1.9.2.  On Windows, we see mswin32 and mingw32 flavors of Ruby (especially with 1.8.6).

Anyway, a "gem install fig" would often fail due to missing dependencies.  For instance, Ubuntu doesn't come with zlib, and Windows usually isn't set up to build anything at all.  If the platform flavor didn't match up with the "mswin32" version of prebuilt libarchive-0.1.1 that's available...FAIL.  AND, if that was all correct, but the gem install was done with Ruby 1.9.2...FAIL (libarchive-0.1.1-mswin32.gem only works with Ruby 1.8.6, and as of October 2011--as far as I know, a gem's Ruby version dependency cannot be cleanly specified.  One is forced to pick a default version and append a Ruby version to the name, e.g., fig18, libarchive-static-ruby186).


# How to package prebuilt libarchive-static gems for Windows:

Most target Windows machines do not have an environment suitable for building.  Therefore, the binary is prebuilt
and packaged into the gem so that a compile/link is not necessary.

Windows Build Environment Prerequisites
* C:\Ruby192
* C:\rubydev

To install the Windows pre-requisites...

Run the Ruby 1.9.2 MingW installer: http://files.rubyforge.vm.bytemark.co.uk/rubyinstaller/rubyinstaller-1.9.2-p290.exe (Install in C:\ruby192)

Download and run http://github.com/downloads/oneclick/rubyinstaller/DevKit-tdm-32-4.5.2-20110712-1620-sfx.exe (Install in C:\rubydev)

Follow these instructions to set up your dev env:  https://github.com/oneclick/rubyinstaller/wiki/Development-Kit

This gem supports a "gem install fig" (as of a fig version soon after 0.1.37) that should work on any Linux or Mac system, and on Windows systems running ruby-1.9.2 mingw32 and mswin32 platforms. A "gem install fig18" will work for Windows systems running Ruby 1.8.6.

When the pre-reqs are in place, run `ruby winbuid.rb`.  This unpacks all the sources, builds zlib, builds libarchive,
and builds the Ruby wrapper around them all, producing a libarchive_ruby.so.  This libarchive_ruby.so is then packaged into
two gems via a 'gem build' command: one for mingw32, and one for mswin32.

# How to package the libarchive-static gem for Linux and Mac:

Unlike Windows, the gem produced for Linux and Mac is not prebuilt; rather, the building is left up to the 'gem install', which
assumes a suitable build environment on the target machine.

Run `ruby generic-gem-package.rb`.  The sources are unpacked, as for Windows, but then instead of being built, they
are copied into the 'generic-gem-package/ext' directory (or rather, the files essential to building are copied).  A
single 'gem build' then produces the libarchive-static gem.

# Here is what happens when fig is installed on different architectures and rubies:

<table>
<tr>
  <th>&nbsp;</th>
  <th>1.8.6</th>
  <th>1.9.2</th>
</tr>
<tr>
  <td>redhat, ubuntu, MacOS</td>
  <td>gem install fig18<br>fig18-0.1.38-x86_64-linux.gem<br>\->libarchive-static-1.0.0.gem (compiles native ext)</td>
  <td>gem install fig<br>fig-0.1.38-x86_64-linux.gem<br>\->libarchive-static-1.0.0.gem (compiles native ext)</td>
</tr>  
<tr>
  <td>mswin32</td>
  <td>gem install fig18<br>fig18-0.1.38.gem<br>\->libarchive-static-ruby186-1.0.0-i386-mswin32.gem (no compile)</td>
  <td>gem install fig<br>fig-0.1.38.gem<br>\->libarchive-static-1.0.0-i386-mswin32.gem (no compile)</td>
</tr>
<tr>
  <td>mingw32</td>
  <td>gem install fig18<br>fig18-0.1.38.gem<br>\->libarchive-static-ruby186-1.0.0-i386-mingw32.gem (no compile)</td>
  <td>gem install fig<br>fig-0.1.38.gem<br>\->libarchive-static-1.0.0-i386-mingw32.gem (no compile)</td>
</tr>
</table>

If you want to update the versions of the various sources, here is how to get them:

libarchive-wrapper:  gem fetch libarchive --version 0.1.1

libarchive: wget http://libarchive.googlecode.com/files/libarchive-2.8.4.zip

zlib: wget http://zlib.net/zlib125.zip -O zlib-1.2.5.zip

Misc: 

About build-xplatform-probably-stale.rb - It was working last I checked, but I moved away from it due to the differing packaging needs of Windows and Linux:  Windows mswin32 and mingw32 gems can package the same binary as distinct architectures, but the Rubies on Ubuntu and RedHat are indistinguishable from an architecture perspective, so a single "x86_64-linux" build cannot be pre-built and packaged.  Instead, the gem on Linux needs to compile upon install.
