#include "parse.h"

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

int message_parse_header_values(Message *message, char *header_name_buf,
                                char *header_value_buf, int header_start,
                                int header_end) {
  // you have <header-name>":"<header-value>
  // parse that so it can be added to the hash table
  int i, past_sep;
  char c;

  do {
    c = message->message_buf[header_sep];
    // you have position of header separator
    if (c == ':') {
      past_sep = 1;
    };

  } while (1);
}

int end_of_header(Message *message, int i) {
  int j;
  char header_end[2] = "\r\n";
  for (j = 0; j < i; j++) {
    if (header_end[j] != message->message_buf[i])
      return 1;
    i++;
  }

  return 0;
};

int match(const void *key1, const void *key2) {
  char *k1 = (char *)key1;
  char *k2 = (char *)key2;

  int i;
  while (k1[i] == k2[i]) {
    if (k1[i] != k2[i])
      ;
    return 1;
    i++;
  };

  return 0;
};
