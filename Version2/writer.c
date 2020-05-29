#include "message.h"


// message_buffer object
struct message_buffer message_jap;
struct message_buffer message_western;

// functions
void haiku_to_arr(struct message_buffer *message, int type);
int msg_id_generator();




int main(int argc, char const *argv[])
{
    int msgid = msg_id_generator();
    printf("msg id is %d\n", msgid);


    haiku_to_arr(&message_jap, 1);
    haiku_to_arr(&message_western, 2);

    // for (int i = 0; i < JAP_HAIKU; i++)
    // {
    //     printf("%s\n", message_jap.haiku_array[i]);
    //     printf("-----------------\n");
    // }

    // printf("\n\n");
    
    // for (int i = 0; i < WEST_HAIKU; i++)
    // {
    //     printf("%s\n", message_western.haiku_array[i]);
    //     printf("-----------------\n");
    // }


    if(msgsnd(msgid, &message_jap, sizeof(message_jap), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        printf("SENT JAPANESE\n");
    }

    if(msgsnd(msgid, &message_western, sizeof(message_western), 0) == -1){
        perror("msgsnd");
        exit(1);
    }else{
        printf("SENT WESTERN\n");
    }

    return 0;
}


void haiku_to_arr(struct message_buffer *message, int type){

    FILE *filePtr;
    char fileName[10];
    char filepath[15];
    char *haikuType;
    int haikuAmount;
    message->message_type = type;
    if (type == 1)
    {
        haikuType = "japanese/";
        haikuAmount = JAP_HAIKU;
    }
    else if (type == 2)
    {
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
            // arr[i-1] = (char*)calloc(size, sizeof(char)); //allocates memory
            fread(message->haiku_array[i-1], 1, size, filePtr); //puts text into heap
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