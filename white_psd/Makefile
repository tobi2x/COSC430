CC      = gcc
CFLAGS  = -Wall -fPIC
BUILD   = libpkg1.so libpkg2.so libpkg3.so f12_any_pkg

all: $(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o lib*so core a.out

libpkg1.so: pkg1.o
	$(CC) -shared -o libpkg1.so pkg1.o

libpkg2.so: pkg2.o
	$(CC) -shared -o libpkg2.so pkg2.o

libpkg3.so: pkg3.o
	$(CC) -shared -o libpkg3.so pkg3.o

f12_any_pkg: f12_any_pkg.o f12.o lookup.o
	$(CC) -o f12_any_pkg f12_any_pkg.o f12.o lookup.o

lookup.o: lookup.h

f12.o: f12.h lookup.h
