#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include "writer.h"
#include "reader.h"
#include "message.h"

int msg_id_generator2();

int counter = 0;

// signal message buffer
struct sig_message_buffer {  
    int message_signal_type; 
};

struct sig_message_buffer message;


int main(int argc, char const *argv[])
{
    // haiku message buffer object
    struct message_buffer message_jap;
    struct message_buffer message_western;

    int msgid_sig = msg_id_generator2();
    int msgid_mes = msg_id_generator();

    printf("%d aaa\n", msgid_mes);
    printf("%d aaa\n", msgid_sig);

    int haiku_category[2][2];
    haiku_category[0][0] = SIGINT;
    haiku_category[0][1] = 1; // japanese 
    haiku_category[1][0] = SIGQUIT;
    haiku_category[1][1] = 2; //  western

    haiku_to_arr(&message_jap, 1);
    haiku_to_arr(&message_western, 2);

    if(msgsnd(msgid_mes, &message_jap, sizeof(struct message_buffer), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        printf("SENT JAPANESE\n");
    }

    if(msgsnd(msgid_mes, &message_western, sizeof(struct message_buffer), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        printf("SENT WESTERN\n");
    }

    while(counter < 8){
        if(msgrcv(msgid_sig, &message, sizeof(message), 0, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        else if(message.message_signal_type == haiku_category[0][0]){ // japanese
            printf("Japanese\n");
            // TODO
            read_haiku(haiku_category[0][1]);
        }
        else if(message.message_signal_type == haiku_category[1][0]){ // western
            printf("Western\n");
            // TODO
            read_haiku(haiku_category[1][1]); 
        }

        counter += 1;
    }
    

    msgctl(msgid_mes, IPC_RMID, NULL);    
    msgctl(msgid_sig, IPC_RMID, NULL);          
    return 0;
}

int msg_id_generator2(){
    int msg_id;
    key_t key;
    key = ftok("japanese/3.txt", 'F');
    if(key == -1){
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