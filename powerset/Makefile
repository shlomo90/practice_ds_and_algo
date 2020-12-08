CC:= gcc
PROG:= powerset
OBJS:= main.o powerset.o
SRCS:= main.c powerset.c
CFLAGS:=-g

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)	-g

clean:
	rm -rf $(PROG) $(OBJS)
