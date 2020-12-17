# include ../Makefile.common
include Makefile.tc.list

#################### Configuration area #####################
#------------ Compiling options --------------#
VML_INCLUDE_DIR := ../
CFLAGS       := -m64 -O2 -fPIC -Wall -ffast-math -ftree-loop-vectorize
CXXFLAGS     := -m64 -O2 -fPIC -std=c++11 -Wall
CPPFLAGS     := -I$(VML_INCLUDE_DIR)
LDFLAGS      := -lm
#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################

#-------------- Main entries -----------------#
all : cppbin cbin
	mkdir -p bin
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		mv $(cpp_test_case).bin bin; \
	)
	$(foreach c_test_case, $(C_TEST_CASES), \
		mv $(c_test_case).bin bin; \
	)

cppbin :
	$(foreach cpp_test_case, $(CPP_TEST_CASES), \
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(cpp_test_case).cpp -o $(cpp_test_case).bin $(LDFLAGS); \
	)
	
cbin :
	$(foreach c_test_case, $(C_TEST_CASES), \
		$(CC) $(CFLAGS) $(CPPFLAGS) $(c_test_case).c -o $(c_test_case).bin $(LDFLAGS); \
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
