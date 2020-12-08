
CC:= gcc
SRC:= main.c subset_string.c subset_node.c
PROG:= subset
OBJS:= main.o subset_string.o subset_node.o subset.o
FLAGS:=-g

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)	-g

main.o:	main.c
	$(CC) -o $@ -c main.c	$(FLAGS)

subset_string.o: subset_string.c
	$(CC) -o $@ -c subset_string.c	$(FLAGS)

subset_node.o: subset_node.c
	$(CC) -o $@ -c subset_node.c	$(FLAGS)

subset.o: subset.c
	$(CC) -o $@ -c subset.c		$(FLAGS)

clean:
	rm -rf $(PROG) $(OBJS)
