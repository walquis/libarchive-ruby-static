require 'rbconfig'
Gem::Specification.new do |s|
  s.name              = "libarchive-static" + (RUBY_VERSION =~ /1.8/ ? "-ruby186" : "")
  s.version           = ENV['BUILD_VERSION'].dup
  s.platform          = ENV['RUBY_PLATFORM']
  s.summary           = 'Ruby bindings for Libarchive.'
  s.description       = 'Ruby bindings for Libarchive, yeah.'
  s.require_paths     = %w(lib)
  s.files             = %w(lib/libarchive_ruby.so README.txt libarchive.c)
  s.author            = 'Chris Walquist'
  s.email             = 'chris@walquist.net'
  s.homepage          = 'http://github.com/walquis/libarchive-ruby-static'
  s.has_rdoc          = false
  s.rubyforge_project = 'libarchive-static'
end
