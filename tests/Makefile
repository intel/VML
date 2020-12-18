# include ../Makefile.common
include Makefile.tc.list

#################### Configuration area #####################
#------------ Compiling options --------------#
VML_INCLUDE_DIR := ../
CFLAGS       := -m64 -O2 -fPIC -Wall -ffast-math -ftree-loop-vectorize -fstack-protector-strong -fPIE -fPIC -D_FORTIFY_SOURCE=2 -Werror=format-security
CXXFLAGS     := -m64 -O2 -fPIC -std=c++11 -Wall
CPPFLAGS     := -I$(VML_INCLUDE_DIR)
LDFLAGS      := -z noexecstack -z relro -z now -pie -lm
#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################

#-------------- Main entries -----------------#
cbin = $(addsuffix .bin, $(C_TEST_CASES))
cppbin = $(addsuffix .bin, $(CPP_TEST_CASES))

$(cbin): 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(shell echo $@|awk -F '.' '{ print $$1 }').c -o $@ $(LDFLAGS)

$(cppbin):
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(shell echo $@|awk -F '.' '{ print $$1 }').cpp -o $@ $(LDFLAGS)

.DEFAULT_GOAL := all

all : $(cppbin) $(cbin)
	mkdir -p bin
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		mv $(cpp_test_case).bin bin; \
	)
	$(foreach c_test_case, $(C_TEST_CASES), \
		mv $(c_test_case).bin bin; \
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
