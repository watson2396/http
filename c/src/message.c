#include "message.h"

Message *message_create(char *recv_buf, int recv_buflen) {
  int ret_result;

  Message *self = (Message *)malloc(sizeof(Message));

  self->message_buflen = recv_buflen;
  self->message_headers = chtbl_create(10, match);
  self->message_body = NULL;
  self->message_buf = (char *)malloc(recv_buflen * sizeof(char));

  if (strncpy(self->message_buf, recv_buf, self->message_buflen))
    return 1;
  return 0;
}

// RFC for HTTP: https://datatracker.ietf.org/doc/html/rfc2616
/// https://datatracker.ietf.org/doc/html/rfc2616#section-4.2
int message_parse(Message *message) {
  message_parse_headers(message);

  message_parse_body(message);

  return 0;
};

int message_parse_headers(Message *message) {
  int ret_result;
  int header_count;
  int header_start, header_end, pos = 0;

  char header_name_buf[50];
  int header_name_buf_idx;

  char header_value_buf[50];
  int header_value_buf_idx;

  // 1. check current buf ahead to next header name
  //      find indexes for start and end
  //      copy current buf contents to holding buf
  // 2. find header value
  //      find indexes for start and end
  //      copy current buf contents to holding buf
  // 3. pass holding bufs to htbl to be set
  // 4. reset holding bufs

  // the length of the recieved buffer is known

  // find the length to header portion first
  do {
    while (!end_of_header(message, pos)) {
      pos++;
    }

    header_start = header_end;
    header_end = pos;

  } while (!end_of_header(message, pos));
};

int message_parse_body(Message *message) { return 0; };


