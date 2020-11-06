HEADER_PATH = ../
bin = use_sin
CFLAGS = -m64 -g -O2 -fPIC -Wall -ffast-math -ftree-loop-vectorize -I$(HEADER_PATH)
LDFLAGS = -lm
CC = gcc

$(bin):
	$(CC) $(CFLAGS) -o $(bin) use_sin.c $(LDFLAGS)

.PHONY:clean
clean:
	rm -rf $(bin) *.o

