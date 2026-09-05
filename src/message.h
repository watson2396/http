#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define HEADER_BUFLEN 512
#define DEFAULT_BUFLEN 512

typedef struct {
  ht_hash_table*    headers;
  char*             body;
  int               bodylen;
} Message;

typedef struct {
    char*   recvbuf; 
    int     recvbuf_len;
    char*   current;
    char*   header_start;
    char*   header_sep;
} Scanner;

typedef enum {
    HEADER_END, HEADER_SEP, HEADER_END_END, HEADER_NA
} HeaderTokens;

Message *message_create();

int message_parse(Message *message, char* recvbuf, int recvbuf_len);

int parse_headers(Message *message, Scanner *scanner);

int parse_body(Message *message, Scanner *scanner);

int parse_values(char *buf, int start, int end, int sep);

int parse_match(char *buf, int pos);

char advance(Scanner *scanner);

char peek(Scanner *scanner);

