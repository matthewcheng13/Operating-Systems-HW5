CC     = gcc
INC    = -I.
CFLAGS = $(INC) -Wall -Wextra -Werror
LFLAGS = -pthread
CFILES = $(wildcard *.c)
OBJS   = $(patsubst %.c, %.o,$(CFILES))
BIN    = test

%.o:%.c
	$(info Compiling $<)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BIN):$(OBJS)
	$(CC) -o $@ $(LFLAGS) $^

exec:$(BIN)
	./test

clean:
	@rm -f $(BIN) $(OBJS) *~
