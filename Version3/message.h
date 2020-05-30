#ifndef MESSAHE_H
#define MESSAHE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
// const variables
#define SIZE 1024
#define JAP_HAIKU 6  // number of haikus from japanese category, type 1
#define WEST_HAIKU 9 // number of haikus from western category, type 2


// message buffer
struct message_buffer{
    long message_type; 
    char haiku_array[WEST_HAIKU][SIZE]; // taking the greatest number of haikus from the categories
};

int msg_id_generator();

#endif