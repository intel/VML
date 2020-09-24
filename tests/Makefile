# include ../Makefile.common
include Makefile.tc.list

#################### Configuration area #####################
#------------ Compiling options --------------#
CKL_INCLUDE_DIR := ../math
CFLAGS       += -march=westmere -ffast-math -ftree-loop-vectorize
CXXFLAGS     +=
CPPFLAGS     += -I$(CKL_INCLUDE_DIR)
LDFLAGS      += -lm
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
