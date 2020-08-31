include ../Makefile.common

export CKL_SRC_DIR=$(CURDIR)

#################### Configuration area #####################
#------------ Compiling options --------------#
CFLAGS       += -ffast-math -ftree-loop-vectorize 
CFLAGS_AVX512 += -march=skylake-avx512 -ffast-math -ftree-loop-vectorize
CFLAGS_AVX2 += -march=haswell -ffast-math -ftree-loop-vectorize
CFLAGS_AVX += -march=ivybridge -ffast-math -ftree-loop-vectorize
CFLAGS_SSE += -march=westmere -ffast-math -ftree-loop-vectorize
CXXFLAGS     += 
CPPFLAGS     += -I$(CKL_INCLUDE_DIR) -I./
LDFLAGS      += -lm
#---------------------------------------------#

#--------------- Source list -----------------#
SOURCE       := cpu.c
MATH_SRC = $(wildcard math/*.c)
AVX512_SRC = $(wildcard math/avx512/*.c)
AVX2_SRC = $(wildcard math/avx2/*.c)
AVX_SRC = $(wildcard math/avx/*.c)
SSE_SRC = $(wildcard math/sse/*.c)
#---------------------------------------------#
#--------------- Object list -----------------#

#---------------------------------------------#
#############################################################

##################### DON'T TOUCH area ######################
#--------------- Object list -----------------#
MATH_OBJ = $(MATH_SRC:.c=.o)
AVX512_OBJ = $(AVX512_SRC:.c=.o)
AVX2_OBJ = $(AVX2_SRC:.c=.o)
AVX_OBJ = $(AVX_SRC:.c=.o)
SSE_OBJ = $(SSE_SRC:.c=.o)
OBJS         := cpu.o $(MATH_OBJ) $(AVX512_OBJ) $(AVX2_OBJ) $(AVX_OBJ) $(SSE_OBJ) 
#---------------------------------------------#
#------------- Default rules -----------------#
.SUFFIXES: .c .o

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c

math/%.o : math/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) -lm

math/avx512/%.o : math/avx512/%.c
	$(CC) -o $@ -c $< $(CFLAGS_AVX512) $(CPPFLAGS) -lm

math/avx2/%.o : math/avx2/%.c
	$(CC) -o $@ -c $< $(CFLAGS_AVX2) $(CPPFLAGS) -lm

math/avx/%.o : math/avx/%.c
	$(CC) -o $@ -c $< $(CFLAGS_AVX) $(CPPFLAGS) -lm

math/sse/%.o : math/sse/%.c
	$(CC) -o $@ -c $< $(CFLAGS_SSE) $(CPPFLAGS) -lm

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
	-rm -f $(CKL_LIB_DIR)/*
#---------------------------------------------#
#############################################################
