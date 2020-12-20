OBJS:= main.o window.o
PROG:= window
CC:= gcc
CFLAGS:= -g

$(PROG):	$(OBJS)
	$(CC) -o $@ $^


clean:
	rm $(OBJS)
	rm $(PROG)
