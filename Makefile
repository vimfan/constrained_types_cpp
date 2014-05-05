.PHONY: all rebuild tests

all: rebuild tests

rebuild:
	mkdir -p build
	cd build && cmake .. && make

tests:
	@cd build && ctest | sed -e 's/[0-9]*: \//\//g' 
	@# the above sed invokation is a workaround to be able to navigate over
	@# quickfix in vim

tests_verbose:
	@cd build && ctest -V | sed -e 's/[0-9]*: \//\//g' 

tags:
	ctags -R .

clean:
	rm -Rf build
