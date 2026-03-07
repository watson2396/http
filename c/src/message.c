#include "message.h"

// RFC for HTTP: https://datatracker.ietf.org/doc/html/rfc2616
Message* message_create(char* recv_buf, int recv_buflen)
{
    int ret_result;

    Message* self = (Message*)malloc(sizeof(Message));

    self->message_buflen = recv_buflen;
    self->message_headers = chtbl_create(10, match);
    self->message_body = NULL;
    self->message_buf = (char *)malloc(recv_buflen * sizeof(char));
    
    if (strncpy(self->message_buf, recv_buf, self->message_buflen)) return 1;
    return 0;
}


// https://datatracker.ietf.org/doc/html/rfc2616#section-4.2
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

int message_parse_headers(Message* message)
{
    int ret_result;
    int headers;
    int i = 0;
    int pos = 0;
    int end_of_header = 0;

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
    
    while (!end_of_header)
    {
        message->message_buf[i]

        i++;
    }



};

int end_of_header(char* arr, int i) 
{
    int j;
    char header_end[2] = "\r\n";
    for (j = 0; j < i; j++)
    {
        if (header_end[j] != arr[i]) return 1;
        i++;
    }

    return 0;
};


int message_parse_body(Message* message)
{
    return 0;
};

int message_parse(Message* message) 
{
    message_parse_headers(&message);

    message_parse_body(&message);

    return 0;
};


int match (const void* key1, const void* key2) 
{
    char* k1 = (char*)key1;
    char* k2 = (char*)key2;

    int i;
    while (k1[i] == k2[i]) {
        if (k1[i] != k2[i]); return 1;
        i++;
    }; 

    return 0;
};