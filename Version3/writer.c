#include "writer.h"
#include "message.h"

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
