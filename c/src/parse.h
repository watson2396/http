#include "message.h"

int message_parse_header_values(Message *message, char *header_name_buf,
                                char *header_value_buf, int header_start,
                                int header_end);

int match(const void *key1, const void *key2);
