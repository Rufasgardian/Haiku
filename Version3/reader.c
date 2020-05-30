#include "reader.h"
#include "message.h"


void read_haiku(int category){
    // message_buffer object
    struct message_buffer message_jap;
    struct message_buffer message_western;

    int msgid = msg_id_generator();
    printf("msg id is %d\n", msgid);
    srand(time(0));
    int random_numbers[3];
    int rNumber;

    if (category == 1)
    {   
        if(msgrcv(msgid, &message_jap, sizeof(message_jap), 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }else if(message_jap.message_type == 1){
            printf("japanese received\n\n");
        }
        else
        {
            printf("Confusion on receiving japanese haikus. Exiting...\n");
            exit(1);
        }


        int index = 0;
        for (int i = 0; i < 3; i++){
            random_numbers[i] = generate_random_number(JAP_HAIKU-1);
            rNumber = random_numbers[i];

            for(int j=0; j < i; j++){
                if(random_numbers[j] == rNumber){
                    i -= 1;
                    break;
                }
            }
        }

        for(int i=0; i < 3; i++){
            index = random_numbers[i];
            printf("%s", message_jap.haiku_array[index]);
            printf("\n--------------\n");
        }
        
    }
    else if (category == 2)
    {
        if(msgrcv(msgid, &message_western, sizeof(message_western), 2, 0) == -1){
            perror("msgrcv");
            exit(1);
        }else if(message_western.message_type == 2){
            printf("western received\n\n");
        }
        else
        {
            printf("Confusion on receiving western haikus. Exiting...\n");
            exit(1);
        }


        int index = 0;
            for (int i = 0; i < 3; i++){
            random_numbers[i] = generate_random_number(JAP_HAIKU-1);
            rNumber = random_numbers[i];

            for(int j=0; j < i; j++){
                if(random_numbers[j] == rNumber){
                    i -= 1;
                    break;
                }
            }
        }

        for(int i=0; i < 3; i++){
            index = random_numbers[i];
            printf("%s", message_western.haiku_array[index]);
            printf("\n--------------\n");
        }        
    }
    else
    {
        printf("Category is out of range. Exiting...\n");
    }
    
}

int generate_random_number(int upper){
    int rand_numb;
    rand_numb = (rand() % (upper + 1)) + 0;

    return rand_numb;
}