#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct mesg_buffer {
    int mesg_type;
    char szo[10];
} message;


int main()
{


     key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok(".", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // msgrcv to receive message
    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            msgrcv(msgid, &message, sizeof(finishString[i][j]), 1, 0);
        }

    }


        for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            printf("Data Received is : %d \n", finishString[i][j]);
        }

    }







    FILE *fp;
    fp = fopen("output.txt", "w+");

    int i;

    int a[] = {1,2,5,6,7};


    for(i=0; i<5; i++){
        fprintf(fp,"%d\n", a[i]);
    }

    fclose(fp);

}
