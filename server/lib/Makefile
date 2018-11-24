CC=gcc
LIB=libmyfuncs.so.1.0
OBJS=func1.o func2.o
CFLAGS=-Wall
POINTER=libmyfuncs.so libmyfuncs.so.1

$(LIB): $(OBJS)
        $(CC) -fPIC -shared -Wl,-soname=libmyfuncs.so.1 $(OBJS) -o $@ -lc
        ln -s libmyfuncs.so.1.0 libmyfuncs.so
        ln -s libmyfuncs.so.1.0 libmyfuncs.so.1

%.o: %.c
        $(CC) -fPIC -c $(CFLAGS) -I../include  $< -o $@

clean:
        rm -f $(OBJS) $(LIB) $(POINTER)

