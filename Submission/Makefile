CC       = gcc
INC      = -I.
CFLAGS   = $(INC) -Wall -Wextra #-Werror
LFLAGS   = -pthread
CPPFLAGS = -O3
CFILES   = $(wildcard *.c)
CFILE1   = main_CAS.c
CFILE2   = main.c
OBJS1    = $(patsubst %.c, %.o,$(CFILE1))
OBJS2    = $(patsubst %.c, %.o,$(CFILE2))
OBJS     = $(patsubst %.c, %.o,$(CFILES))
BIN1      = testCAS
BIN2	  = testMUTEX

clean:
	@rm -f $(BIN1) $(BIN2) $(OBJS) *~

lock-free:
	$(info Compiling $(CFILE1))
	@$(CC) $(CFLAGS) -o $(OBJS1) -c $(CFILE1)
	$(CC) $(CPPFLAGS) -o $(BIN1) $(LFLAGS) $(OBJS1)

thread-safe:
	$(info Compiling $(CFILE2))
	@$(CC) $(CFLAGS) -o $(OBJS2) -c $(CFILE2)
	$(CC) -o $(BIN2) $(LFLAGS) $(OBJS2)