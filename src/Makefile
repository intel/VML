include ../Makefile.common

export CKL_SRC_DIR=$(CURDIR)

#################### Configuration area #####################
#------------ Compiling options --------------#
CFLAGS       += -march=skylake-avx512 -ffast-math -ftree-loop-vectorize 
CXXFLAGS     += 
CPPFLAGS     += -I$(CKL_INCLUDE_DIR) -I./
LDFLAGS      += -lm
#---------------------------------------------#

#--------------- Source list -----------------#
SOURCE       := ckl.c
#---------------------------------------------#
#--------------- Object list -----------------#

#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################
#--------------- Object list -----------------#
OBJS         := $(SOURCE:.c=.o)
#---------------------------------------------#
#------------- Default rules -----------------#
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<
#---------------------------------------------#

#-------------- Main entries -----------------#
.PHONY: lib clean all LIB_S LIB_D

all: lib

lib: LIB_D

LIB_D : $(OBJS)
	$(CC) $(CFLAGS) -shared -Wl,-soname,$(CKL_LIBSOM) -o $(CKL_LIB_DIR)/$(CKL_LIBSOV) $(OBJS) $(LDFLAGS)
	pushd $(CKL_LIB_DIR); rm -f $(CKL_LIBSO); rm -f $(CKL_LIBSOM); ln -s $(CKL_LIBSOV) $(CKL_LIBSO); ln -s $(CKL_LIBSOV) $(CKL_LIBSOM); popd

clean:
	-rm -f $(OBJS)
#---------------------------------------------#
#############################################################
