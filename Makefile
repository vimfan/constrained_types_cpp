ifeq ($(CXX),)
	CXX=g++
endif

ifeq ($(VERBOSE), 1)
	CTEST_FLAGS=-V
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
	@cd $(BUILD_DIR) && ctest $(CTEST_FLAGS) | sed -e 's/[0-9]*: \//\//g' 
	@# the above sed invokation is a workaround to be able to navigate over
	@# quickfix in vim

tags:
	ctags -R .

clean:
	rm -Rf $(BUILD_DIR_PARENT)
