#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
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

void sig_handler(int sig)
{
    message.message_type = sig;
    int msgid = msg_id_generator();
    if(msgsnd(msgid, &message, sizeof(message), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        if (sig == 2)
        {
            printf("Japanese sent %d (message type = %ld) \n", sig, message.message_type);
        }
        else if (sig == 3)
        {
            printf("Western sent %d (message type = %ld) \n", sig, message.message_type);
        }        
    }
    counter += 1;
}

int main(int argc, char const *argv[]){
    
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    while(counter < 5);

    return 0;
}
