#include ../Makefile.common
include Makefile.tc.list

#################### Configuration area #####################
#------------ Compiling options --------------#
VML_INCLUDE_DIR := ../
CFLAGS       := -m64 -O2 -fPIC -Wall -march=skylake-avx512 -ffast-math -ftree-loop-vectorize -fstack-protector-strong -fPIE -fPIC -D_FORTIFY_SOURCE=2 -Werror=format-security
CXXFLAGS     := -m64 -O2 -fPIC -std=c++11 -Wall
CPPFLAGS     := -m64 -O2 -fPIC -Wall -I$(VML_INCLUDE_DIR)
LDFLAGS      := -z noexecstack -z relro -z now -pie -lm
#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################

#-------------- Main entries -----------------#
cbin = $(addsuffix .bin, $(C_TEST_CASES))
cppbin = $(addsuffix .bin, $(CPP_TEST_CASES))
refbench = $(addsuffix .bin, $(REF_TEST_CASES))

$(cbin):
	$(CC) $(CPPFLAGS) -ffast-math -ftree-loop-vectorize $(shell echo $@|awk -F '.' '{ print $$1 }').c -o $@ $(LDFLAGS)

$(cppbin):
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(shell echo $@|awk -F '.' '{ print $$1 }').cpp -o $@ $(LDFLAGS)

$(refbench):
	$(CC) $(CFLAGS) $(CPPFLAGS) $(shell echo $@|awk -F '.' '{ print $$1 }').c -o $(shell echo $@|awk -F '.' '{ print $$1 }')_vec.bin $(LDFLAGS)
	$(CC) $(CPPFLAGS) $(shell echo $@|awk -F '.' '{ print $$1 }').c -o $@ -lm

.DEFAULT_GOAL := all

all : $(cbin) $(cppbin) $(refbench)
	mkdir -p bin
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		mv $(cpp_test_case).bin bin; \
	)
	$(foreach c_test_case, $(C_TEST_CASES), \
		mv $(c_test_case).bin bin; \
	)
	$(foreach refc_test_case, $(REF_TEST_CASES), \
		mv $(refc_test_case).bin bin; \
		mv $(refc_test_case)_vec.bin bin; \
	)

runtest :
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		export LD_LIBRARY_PATH=../lib; \
		./bin/$(cpp_test_case).bin \
	)
	$(foreach c_test_case, $(C_TEST_CASES), \
		export LD_LIBRARY_PATH=../lib; \
		./bin/$(c_test_case).bin \
	)

clean :
	-rm -rf ./bin

#---------------------------------------------#
#############################################################
