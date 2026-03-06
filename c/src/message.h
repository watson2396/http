#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"

#define HEADER_BUFLEN 512
#define DEFAULT_BUFLEN 512

typedef struct 
{
    char*       message_buf;
    int         message_buflen;
    CHTbl*      message_headers;
    char*       message_body;
} Message;

Message* message_create(char* recv_buf, int recv_buflen);

int message_parse(Message* message);

int message_parse_headers(Message* message);

int message_parse_body(Message* message);

int match (const void* key1, const void* key2);

