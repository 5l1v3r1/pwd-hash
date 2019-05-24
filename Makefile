# pwd-hash's Makefile
PROG = pwd-hash
VERSION = 2.0
CC = gcc -Wall
TAR = /bin/tar --owner 0 --group 0 --exclude ".svn"

default:
	$(CC) -c usage.c -o usage.o
	$(CC) -c schemes.c -o schemes.o
	$(CC) -c random_str.c -o random_str.o
	$(CC) -c echo.c -o echo.o
	$(CC) -c $(PROG).c -o $(PROG).o
	$(CC) -lcrypt usage.o schemes.o random_str.o echo.o $(PROG).o -o $(PROG)

clean:
	rm -f usage.o schemes.o random_str.o echo.o $(PROG).o $(PROG)

install:
	cp -f $(PROG) /bin/

public: clean 
	cd ../ && $(TAR) -czvf - $(PROG)-$(VERSION) | ssh -4x -p522 \
	devzero.fr "cat > ~/www/unix/$(PROG)-$(VERSION).tgz" 

tunnel: clean
	cd ../ && $(TAR) -czvf - $(PROG)-$(VERSION) | ssh -4x -p2223 \
	localhost "cat > ~/www/unix/$(PROG)-$(VERSION).tgz"

archive: clean
	cd ../ && $(TAR) -czvf $(PROG)-$(VERSION).tgz $(PROG)-$(VERSION)
