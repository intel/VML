#include ../Makefile.common
include Makefile.tc.list

#################### Configuration area #####################
#------------ Compiling options --------------#
CKL_INCLUDE_DIR := ../
CFLAGS       := -m64 -g -O2 -fPIC -Wall -march=skylake-avx512 -ffast-math -ftree-loop-vectorize
CXXFLAGS     := -m64 -g -O2 -fPIC -std=c++11 -Wall
CPPFLAGS     := -m64 -g -O2 -fPIC -Wall -I$(CKL_INCLUDE_DIR)
LDFLAGS      := -lm
#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################

#-------------- Main entries -----------------#
all : cppbin cbin refbench
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

cppbin :
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(cpp_test_case).cpp -o $(cpp_test_case).bin $(LDFLAGS); \
	)
	
cbin :
	$(foreach c_test_case, $(C_TEST_CASES), \
		$(CC) $(CPPFLAGS) -ffast-math -ftree-loop-vectorize $(c_test_case).c -o $(c_test_case).bin $(LDFLAGS); \
	)

refbench :
	$(foreach refc_test_case, $(REF_TEST_CASES), \
		$(CC) $(CFLAGS) $(CPPFLAGS) $(refc_test_case).c -o $(refc_test_case)_vec.bin $(LDFLAGS); \
		$(CC) $(CPPFLAGS) $(refc_test_case).c -o $(refc_test_case).bin -lm; \
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

.PHONY: all clean runtest cppbin cbin
#---------------------------------------------#
#############################################################
