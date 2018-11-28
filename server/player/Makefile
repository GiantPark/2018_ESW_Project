EXEC=server
CC=gcc
CFLAGS=-Wall

$(EXEC): server.o
	$(CC) -o server server.o -L../lib -lserverfuncs

%.o: %.c
	$(CC) -c $(CFLAGS) -I../include  $< -o $@ -lpthread

clean:
	rm server.o server
