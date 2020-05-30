#include "message.h"

int msg_id_generator();
void sig_handler(int sig);

// number of signals
int counter = 0;

struct message_buffer message;



int main(int argc, char const *argv[]){
    
    signal(SIGINT, sig_handler); /*    CTRL + C    */
    signal(SIGQUIT, sig_handler); /*     CTRL + \     */
    while(counter < 100);

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

void sig_handler(int sig){

    if(sig == 2){ /*     CTRL + C    */
        message.message_signal_type = SIGINT;
    }else if(sig == 3){ /*    CTRL + \     */
        message.message_signal_type = SIGQUIT;
    }

    int msgid = msg_id_generator();

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