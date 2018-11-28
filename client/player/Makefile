CC = gcc
CFLAGS = -Wall
OUTPUT = client
OBJFILES = client.o

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(OUTPUT) -L../lib -lclientfuncs

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I../include

clean:
	rm *.o $(OUTPUT)
