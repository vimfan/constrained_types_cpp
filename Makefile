ifeq ($(CXX),)
	CXX=g++
endif

BUILD_DIR_PARENT=build
BUILD_DIR=$(BUILD_DIR_PARENT)/build_$(CXX)

.PHONY: all rebuild tests

all: rebuild tests

all_compilers:
	CXX=g++ make
	CXX=clang++ make

rebuild:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -V $(PWD) && make

tests:
	@cd $(BUILD_DIR) && ctest | sed -e 's/[0-9]*: \//\//g' 
	@# the above sed invokation is a workaround to be able to navigate over
	@# quickfix in vim

tests_verbose:
	@cd $(BUILD_DIR) && ctest -V | sed -e 's/[0-9]*: \//\//g' 

tags:
	ctags -R .

clean:
	rm -Rf $(BUILD_DIR_PARENT)
