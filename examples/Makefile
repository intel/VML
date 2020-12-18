HEADER_PATH = ../
bin = use_sin
CFLAGS = -m64 -O2 -fPIC -Wall -ffast-math -ftree-loop-vectorize -I$(HEADER_PATH) -fstack-protector-strong -fPIE -fPIC -D_FORTIFY_SOURCE=2 -Werror=format-security
LDFLAGS = -z noexecstack -z relro -z now -pie -lm
CC = gcc

$(bin):
	$(CC) $(CFLAGS) -o $(bin) use_sin.c $(LDFLAGS)

.PHONY:clean
clean:
	rm -rf $(bin) *.o

