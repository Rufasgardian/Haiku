#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

int msg_id_generator();

int counter = 0;

// message buffer
struct message_buffer { 
    long message_type; 
    int message_signal_type[1]; 
};

struct message_buffer message;

int main(int argc, char const *argv[])
{
    
    return 0;
}

int msg_id_generator(){
    int msg_id;
    key_t key;
    key = ftok("/etc/passwd", 'F');
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