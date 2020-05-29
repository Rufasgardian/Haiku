#include "message.h"

// message_buffer object
struct message_buffer message_jap;
struct message_buffer message_western;


int msg_id_generator();
void read_haiku(int category);

int main(int argc, char const *argv[]){
    
    int msgid = msg_id_generator();
    printf("msg id is %d\n", msgid);


    if(msgrcv(msgid, &message_jap, sizeof(message_jap), 0, 0) == -1){
        perror("msgrcv");
        exit(1);
    }else if(message_jap.message_type == 1){
        printf("japanese received\n");
    }
    else
    {
        printf("Confusion on receiving japanese haikus. Exiting...\n");
        exit(1);
    }
    

    if(msgrcv(msgid, &message_western, sizeof(message_western), 0, 0) == -1){
        perror("msgrcv");
        exit(1);
    }else if(message_western.message_type == 2){
        printf("western received\n");
    }
    else
    {
        printf("Confusion on receiving western haikus. Exiting...\n");
        exit(1);
    }

    read_haiku(1);
    read_haiku(2);

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

void read_haiku(int category){
    FILE *filePtr;
    srand(time(0));
    
    if (category == 1)
    {   // creates file named japanese.txt and checks if it is not null
        if((filePtr=fopen("japanese.txt", "w"))== NULL)
        {
            perror("fopen");
            exit(1);
        }
        else
        {
            int index = 0;
            for (int i = 0; i < 3; i++)
            {
                index = rand()%JAP_HAIKU;  // RUFAT ASSIGN "INDEX" TO YOUR RANDOM NUMBER
                //writes into this file
                fprintf(filePtr, message_jap.haiku_array[index]);
                fprintf(filePtr, "\n--------------\n");
            }
        }
        fclose(filePtr);
        filePtr=NULL;

    }
    else if (category == 2)
    {
        // creates file named western.txt and checks if it is not null
        if((filePtr=fopen("western.txt", "w"))== NULL)
        {
            perror("fopen");
            exit(1);
        }
        else
        {
            int index = 0;
            for (int i = 0; i < 3; i++)
            {
                index = rand()%WEST_HAIKU; // RUFAT ASSIGN "INDEX" TO YOUR RANDOM NUMBER
                //writes into this file
                fprintf(filePtr, message_western.haiku_array[index]);
                fprintf(filePtr, "\n--------------\n");
            }
        }
        
        fclose(filePtr);
        filePtr=NULL;
    }
    else
    {
        printf("Category is out of range. Exiting...\n");
    }
    
}