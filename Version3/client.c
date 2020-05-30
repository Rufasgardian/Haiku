#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>


int msg_id_generator2();
void sig_handler(int sig);

// number of signals
int counter = 0;

// message buffer
// message buffer
struct sig_message_buffer {  
    int message_signal_type; 
};

struct sig_message_buffer message;

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handler); /*    CTRL + C    */
    signal(SIGQUIT, sig_handler); /*     CTRL + \     */
    while(counter < 1);
    
    return 0;
}


void sig_handler(int sig){

    if(sig == 2){ /*     CTRL + C    */
        message.message_signal_type = SIGINT;
    }else if(sig == 3){ /*    CTRL + \     */
        message.message_signal_type = SIGQUIT;
    }

    int msgid = msg_id_generator2();

    if(msgsnd(msgid, &message, sizeof(message), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        if(sig == 2){
            printf("Japanese sent with signal %d\n", sig);
        }
        else if(sig == 3){
            printf("Western sent with signal %d\n", sig);
        }        
    }
    counter += 1;
}

int msg_id_generator2(){
    int msg_id;
    key_t key;
    key = ftok("japanese/3.txt", 'F');
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