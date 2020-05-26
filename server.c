#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "message.h"

int counter = 0;

struct message_buffer message;

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


int main(int argc, char const *argv[]){
    int msgid;
    msgid = msg_id_generator();

    printf("msg id = %d\n", msgid);
    // msgctl(msgid, IPC_RMID, NULL);
    while(counter < 5){
        if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if(message.message_type == 2){
            printf("Jap\n");
        }
        else if(message.message_type == 3){
            printf("West\n");
        }
        counter += 1;
    }
    
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}
