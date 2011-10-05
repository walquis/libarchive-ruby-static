all:
	ruby build.rb

clean:
	cd libarchive-2.8.4/libarchive && make -f ../../libarchive-static-makefile clean
	cd libarchive-0.1.1/ext && make -f ../../libarchive-static-wrapper-makefile clean
	cd zlib-1.2.5 && make clean
