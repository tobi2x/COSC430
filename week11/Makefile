CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -L. -lprocess
TARGET = main
LIB = libprocess.so

all: $(LIB) $(TARGET)

#Build shared library
$(LIB): process_lib.o
	$(CC) -shared -o $(LIB) process_lib.o

$(TARGET): main.o $(LIB)
	$(CC) main.o $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.so main
