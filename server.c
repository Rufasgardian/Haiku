#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#define SIZE 1024
// #include <bits/msq.h>
// #include <mqueue.h>

// message buffer
struct message_buffer { 
    long message_type; 
    char message_text[SIZE]; 
    int message_id;
}message; 

int counter = 0;

int msg_id_generator(int msg_id){
    key_t key;
    key = ftok("progfile", 121);

    msg_id = msgget(key, 0666 | IPC_CREAT);

     if(msg_id == -1){
        perror("msgget error");
        exit(1);
    }

    return msg_id;
}


int main(int argc, char const *argv[]){
    int msgid;
    // msgid = msg_id_generator(msgid);


    key_t key;
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

     if(msgid == -1){
        perror("msgget error");
        exit(1);
    }

    printf("msg id = %d\n", msgid);
    // msgctl(msgid, IPC_RMID, NULL);
    while(counter < 5){
        if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if(message.message_type == 1){
            printf("Jap\n");
        }
        if(message.message_type == 2){
            printf("West\n");
        }
        counter += 1;
    }
    
    msgctl(msgid, IPC_RMID, NULL);
    
    
    return 0;
}
