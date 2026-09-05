CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

myapp: src/main.c
	$(CC) $(CFLAGS) -o build/http src/main.c

clean:
	rm -f build/http