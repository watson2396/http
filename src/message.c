#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "message.h"

Message *create() {
  Message *self = (Message *)malloc(sizeof(Message));

  self->headers = ht_new();
  self->body = NULL;
  self->bodylen = NULL;

  return 0;
}


// RFC for HTTP: https://datatracker.ietf.org/doc/html/rfc2616
/// https://datatracker.ietf.org/doc/html/rfc2616#section-4.2
int parse(Message *message, char *recv_buf, int recv_buf_len) {
    Scanner scanner = {
        scanner.recvbuf = recv_buf,
        scanner.recvbuf_len = recv_buf_len,
        scanner.current = recv_buf,
        scanner.header_start = recv_buf,
        scanner.header_sep = recv_buf,
    };

    if (parse_headers(message, &scanner) != 0) {
    printf("shit went sideways parsing the headers"); 
    };

    if (parse_body(message, &scanner) != 0) {
    printf("shit went sideways parsing the body"); 
    };

    return 0;
};

int parse_body(Message *message) { return 0; };

int parse_headers(Message *message, Scanner *scanner) {
    int ret_result;
    int header_count;

    bool prev_header = false;
    bool end_of_headers = false;
    do {
        char c = advance(scanner);

        switch (c) {
            case ':': {
                scanner->header_sep = scanner->current;
                if (prev_header)
                    prev_header = false;
                continue;
            }
            case '\r': {
                if (isHeaderEnd(scanner)) {
                    if (prev_header) {
                        end_of_headers = true;
                        break;
                    }
                    prev_header = true;
                    break;
                }  
            }
            default: {
                if (prev_header)
                    prev_header = false;
                continue;
            }
        }

        if (parse_header_values(message, scanner) != 0) {printf("header poop");}

    } while (!end_of_headers);
};

int parse_header_values(Message *message, Scanner *scanner) {
    // you are at end of a header

    int header_name_len = (int)(scanner->header_start - scanner->header_sep);
    // remove ':' and '\r'
    scanner->header_sep++;
    int header_value_len = ((int)(scanner->header_start - scanner->current) - 1);

    // add space for \0 null byte
    header_name_len++;
    header_value_len++;

    char *header_name_buf = malloc(sizeof(char) * header_name_len);
    char *header_value_buf = malloc(sizeof(char) * header_value_len);

    strncpy(header_name_buf, scanner->header_start, header_name_len);

    strncpy(header_value_buf, scanner->header_sep, header_value_len);

    ht_insert(message->body, header_name_buf, header_value_buf);
}

bool match(Scanner *scanner, char expected) {
    if (isAtEnd(scanner))
        return false;
    if (scanner->current == expected)
        return true;
    
    return 0;
}

bool isHeaderEnd(Scanner *scanner) {
    if (scanner->current[-1] != '\r')
        return false;
    if (scanner->current[0] == "\n") {
        return true;
    }

    return false;
}


char advance(Scanner *scanner) {
    scanner->current++;
    return scanner->current[-1];
}

char peek(Scanner *scanner) {
    return scanner->current[0];
}


//    message-header = field-name ":" [ field-value ]
//    field-name     = token
//    field-value    = *( field-content | LWS )
//    field-content  = <the OCTETs making up the field-value
//                     and consisting of either *TEXT or combinations
//                     of token, separators, and quoted-string>

// gonna keep the implementation stupid simple for now
//      message-header = field-name ":" [field-value]
//      field-name     = CRLF + token + CRLF
//      field-value    = CRLF + token + CRLF
//      token          = 1*<any CHAR except CTLs or separators>
