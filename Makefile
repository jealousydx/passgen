CC = gcc
CFLAGS = -O2 -Wall

passgen: main.c
	$(CC) $(CFLAGS) -o passgen main.c

.PHONY: clean install

install:
	install -m 755 passgen /usr/local/bin/

clean:
	rm -f passgen