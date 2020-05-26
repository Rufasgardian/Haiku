#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#define SIZE 1024
#define POEMSIZE 250

// message buffer
struct message_buffer { 
    long message_type; 
    char message_text[SIZE]; 
};


#endif