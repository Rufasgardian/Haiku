#ifndef MESSAGE_H
#define MESSAGE_H
#define SIZE 1024

// message buffer
struct message_buffer { 
    long message_type; 
    char message_text[SIZE]; 
};


#endif