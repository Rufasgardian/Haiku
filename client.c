#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#define SIZE 1024


// message buffer
struct message_buffer { 
    long message_type; 
    char message_text[SIZE]; 
    int message_id;
    int category;
}; 


int counter = 0;

struct message_buffer message;

int msg_id_generator(int msg_id){
    key_t key;
    key = ftok("progfile", 65);

    msg_id = msgget(key, 0666 | IPC_CREAT);

     if(msg_id == -1){
        perror("msgget error");
        exit(1);
    }

    return msg_id;
}


void sig_japanese(int sign){
    message.message_type = 1;
    int msgid = message.message_id;
    // message.message_text
    if(msgsnd(msgid, &message, sizeof(message), 1) == -1){
        perror("msgsnd japanese");
        exit(1);
    }else{
        printf("Japanese sent %d (message tye = %ld)\n", sign, message.message_type);
    }
    
    counter += 1;
}

void sig_western(int sign){

    message.message_type = 2;
    int msgid = message.message_id;
    if(msgsnd(msgid, &message, sizeof(message), 2) == -1){
        perror("msgsnd japanese");
        exit(1);
    }else{
        printf("Western sent %d (message type = %ld) \n", sign, message.message_type);
    }

    counter += 1;
}

int main(int argc, char const *argv[]){
    // key_t key;
    int message_id;

    message.message_id = msg_id_generator(message.message_id);
    printf("message id = %d\n", message.message_id);
    while(counter < 5){
        signal(SIGINT, sig_japanese);
        signal(SIGQUIT, sig_western);
    } 

    return 0;
}
