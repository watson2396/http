CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

http: src/main.c
	$(CC) $(CFLAGS) -o build/http src/main.c

clean:
	rm -f build/http