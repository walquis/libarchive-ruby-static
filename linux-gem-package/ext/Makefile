arch=$(shell uname)
ifeq ($(arch), Darwin)
	EXT:=bundle
else
	EXT:=so
endif

libarchive_ruby.$(EXT):
	cp libarchive-0.1.1/ext/libarchive_ruby.$(EXT) .

install:
	mkdir -p ../lib
	/usr/bin/install -c -m 0755 libarchive_ruby.$(EXT) ../lib
