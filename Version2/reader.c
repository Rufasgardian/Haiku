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
    char *jap_array[JAP_HAIKU];
    char *west_array[WEST_HAIKU];
};


// message_buffer object
struct message_buffer message;


int msg_id_generator();

int main(int argc, char const *argv[]){
    
    int msgid = msg_id_generator();


    if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
        perror("msgrcv");
        exit(1);
    }else{
        printf("received\n");
    }

  
    printf("WORK HERE SHIRIN\n");

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}


int msg_id_generator(){
    int msg_id;
    key_t key;
    key = ftok("/etc/passwd", 'F');
    if (key == -1){
        perror("Key");
        exit(1);
    } 

    msg_id = msgget(key, 0666 | IPC_CREAT);

     if(msg_id == -1){
        perror("msgget");
        exit(1);
    }

    return msg_id;
}