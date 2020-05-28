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


// functions
void haiku_to_arr(char *arr[], int type);
int msg_id_generator();




int main(int argc, char const *argv[]){

    int msgid = msg_id_generator();

    haiku_to_arr(message.jap_array, 1);
    haiku_to_arr(message.west_array, 2);

    // for (int i = 0; i < JAP_HAIKU; i++)
    // {
    //     printf("%s\n", message.jap_array[i]);
    //     printf("-----------------\n");
    // }

    // printf("\n\n");
    
    // for (int i = 0; i < WEST_HAIKU; i++)
    // {
    //     printf("%s\n", message.west_array[i]);
    //     printf("-----------------\n");
    // }

    if(msgsnd(msgid, &message, sizeof(message), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        printf("SENT\n");
    }


    
    
    return 0;
}


void haiku_to_arr(char *arr[], int type){

    FILE *filePtr;
    char fileName[10];
    char filepath[15];
    char *haikuType;
    int haikuAmount;
    if (type == 1)
    {
        message.message_type = 1;
        haikuType = "japanese/";
        haikuAmount = JAP_HAIKU;
    }
    else if (type == 2)
    {
        message.message_type = 2;
        haikuType = "western/";
        haikuAmount = WEST_HAIKU;
    }
    else
    {
        printf("Please respect function\n");
        exit(1);
    }
    
    for (int i = 1; i <= haikuAmount; i++)
    {
        
        sprintf(filepath, "%s", haikuType);
        sprintf(fileName, "%d", i);
        strcat(fileName, ".txt");
        strcat(filepath, fileName);
        // puts(filepath);

        if ((filePtr=fopen(filepath, "r"))==NULL)
        {
            perror("filePtr");
            exit(1);
        }
        else
        {
            fseek(filePtr, 0, SEEK_END);//puts pointer to the end of file
            int size = ftell(filePtr);  //finds size of file
            fseek(filePtr, 0, SEEK_SET); //puts pointer to the beginnig of file
            arr[i-1] = (char*)calloc(size, sizeof(char)); //allocates memory
            fread(arr[i-1], 1, size, filePtr); //puts text into heap
            // printf("%s\n", arr[i-1]);
        }
        fclose(filePtr);
        filePtr=NULL;
    }
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