EXEC=main
CC=gcc
CFLAGS=-Wall

$(EXEC): main.o
        $(CC) -o main main.o -L../lib -lmyfuncs

%.o: %.c
        $(CC) -c $(CFLAGS) -I../include  $< -o $@

clean:
        rm main.o main
