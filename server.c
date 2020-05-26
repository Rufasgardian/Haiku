#include "message.h"

int counter = 0;

struct message_buffer message;

struct poemList{
    char nationality[10];
    char poem[POEMSIZE];
    char author[POEMSIZE];
};

int generate_random_number(int upper){
    int rand_numb;
    rand_numb = (rand() % (upper + 1)) + 0;

    return rand_numb;
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


int main(int argc, char const *argv[]){

    int msgid, random_number;
    msgid = msg_id_generator();
    
    srand(time(0));
    

    /* JAPANESE POEMS*/
    struct poemList poemJap[6];

    strncpy(poemJap[0].nationality, "Japanese", 10);
    strncpy(poemJap[0].poem, "Autumn moonlight-\na worm digs silently\ninto the chestnut.", POEMSIZE);
    strncpy(poemJap[0].author, "Matsuo Basho(1644-1694)", POEMSIZE);


    strncpy(poemJap[1].nationality, "Japanese", 10);
    strncpy(poemJap[1].poem, "Old pond\na frog jumps\nthe sound of water.", POEMSIZE);
    strncpy(poemJap[1].author, "Matsuo Basho (1644-1694)", POEMSIZE);


    strncpy(poemJap[2].nationality, "Japanese", 10);
    strncpy(poemJap[2].poem, "Autumn wind -\nmountain's shadow\nwavers.", POEMSIZE);
    strncpy(poemJap[2].author, "Kobayashi Issa (1763-1828)", POEMSIZE);


    strncpy(poemJap[3].nationality, "Japanese", 10);
    strncpy(poemJap[3].poem, "Don't weep, insects-\nLovers, starts, themselves,\nMust part.", POEMSIZE);
    strncpy(poemJap[3].author, "Kobayashi Issa (1763-1828)", POEMSIZE);


    strncpy(poemJap[4].nationality, "Japanese", 10);
    strncpy(poemJap[4].poem, "In the coolness\nof the empty sixth-month sky...\nthe cuckoo's cry.", POEMSIZE);
    strncpy(poemJap[4].author, "Masaoka Shiki (1867-1902)", POEMSIZE);


    strncpy(poemJap[5].nationality, "Japanese", 10);
    strncpy(poemJap[5].poem, "the tree cut,\ndawn breaks early\nat my little window.", POEMSIZE);
    strncpy(poemJap[5].author, "Masaoka Shiki (1867-1902)", POEMSIZE);

    /* Japanese POEMS END HERE */


    /* WESTERN POEMS */
    struct poemList poemWest[9];

    strncpy(poemWest[0].nationality, "Western", 10);
    strncpy(poemWest[0].poem, "Snow in my shoe\nAbandoned\nSparrow's nest.", POEMSIZE);
    strncpy(poemWest[0].author, "Book of Haikus Jack Kerouac (1922-1969)", POEMSIZE);


    strncpy(poemWest[1].nationality, "Western", 10);
    strncpy(poemWest[1].poem, "Whitecaps on the bay:\nA broken signboard banging\nIn the April wind.", POEMSIZE);
    strncpy(poemWest[1].author, "Haiku: This Other World Richard Wright (1908-1960)", POEMSIZE);


    strncpy(poemWest[2].nationality, "Western", 10);
    strncpy(poemWest[2].poem, "Lily:\nout of the water\nout of itself.", POEMSIZE);
    strncpy(poemWest[2].author, "Nick Virgilio (1928-1989)", POEMSIZE);


    strncpy(poemWest[3].nationality, "Western", 10);
    strncpy(poemWest[3].poem, "Bass\npicking bugs\nof the moon.", POEMSIZE);
    strncpy(poemWest[3].author, "Nick Virgilio (1928-1989)", POEMSIZE);


    strncpy(poemWest[4].nationality, "Western", 10);
    strncpy(poemWest[4].poem, "quail excited\nin dirt turn up by a gopher.", POEMSIZE);
    strncpy(poemWest[4].author, "Don Eulert (1933-)", POEMSIZE);


    strncpy(poemWest[5].nationality, "Western", 10);
    strncpy(poemWest[5].poem, "ground squirrel\nbalancing its tomato\non the garden fence.", POEMSIZE);
    strncpy(poemWest[5].author, "Don Eulert (1933- )", POEMSIZE);


    strncpy(poemWest[6].nationality, "Western", 10);
    strncpy(poemWest[6].poem, "Just friends:\nhe watches my gauze dress\nblowing on the line.", POEMSIZE);
    strncpy(poemWest[6].author, "After an Affair Alexis Rotella", POEMSIZE);


    strncpy(poemWest[7].nationality, "Western", 10);
    strncpy(poemWest[7].poem, "A little boy sings\non a terrace, eyes aglow\nRidge spills upward.", POEMSIZE);
    strncpy(poemWest[7].author, "Robert Yehling (1959- )", POEMSIZE);


    strncpy(poemWest[8].nationality, "Western", 10);
    strncpy(poemWest[8].poem, "meteor shower\na gentle wave\nwets our sandals.", POEMSIZE);
    strncpy(poemWest[8].author, "Michael Dylan Welch (1962- )", POEMSIZE);

    while(counter < 100){
        if(msgrcv(msgid, &message, sizeof(message), 0, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if(message.message_type == 2){ // japanese

            printf("\nJapanese (message type = %ld)\n", message.message_type);
            random_number = generate_random_number(5);
            printf("Random number = %d\n\n", random_number);

            printf("This is %s poem\n\n", poemJap[random_number].nationality);
            printf("%s\n\n", poemJap[random_number].poem);
            printf("%s\n", poemJap[random_number].author);

        }
        else if(message.message_type == 3){ // western

            printf("\nWestern (message type = %ld)\n", message.message_type);
            random_number = generate_random_number(8);
            printf("Random number = %d\n\n", random_number);

            printf("This is %s poem\n\n", poemWest[random_number].nationality);
            printf("%s\n\n", poemWest[random_number].poem);
            printf("%s\n", poemWest[random_number].author);

        }

        printf("\n*********************************************************\n\n");
        counter += 1;
    }
    
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
