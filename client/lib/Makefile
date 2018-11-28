CC = gcc
CFLAGS = -Wall
OBJS = client_tcp_connect.o
LIB = libclientfuncs.so.1.0
POINTER = libclientfuncs.so libclientfuncs.so.1

$(LIB): $(OBJS)
	$(CC) -fPIC -shared -Wl,-soname=libclientfuncs.so.1 *.o -o $(LIB) -lc
	ln -s $(LIB) libclientfuncs.so
	ln -s $(LIB) libclientfuncs.so.1

%.o: %.c
	$(CC) -fPIC $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(LIB) $(POINTER)
