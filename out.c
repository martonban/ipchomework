#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>



struct mesg_buffer {
    long mesg_type;
    char szo[2][5][100];

}message;


int main()
{

	char finishString[7][5][100];

    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok(".", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);



    // msgrcv to receive message
    for(int i=0; i<2; i++){
        for(int j=0; j<5; j++){
            msgrcv(msgid,  &message, sizeof(message.szo[i][j]), 1, 0);
            //strcpy(finishString[i][j],message.szo[i][j]);
            printf("Data Received is : %s \n", message.szo[i][j]);  
        }
    }


/*
    for(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            msgrcv(msgid, &message, sizeof(message.szo[i][j]), 1, 0);
            printf("Data Received is : %s \n", message.szo[i][j]);  
        }
    }


*/




    //msgctl(msgid, IPC_RMID, NULL);

    return 0;




/*

    FILE *fp;
    fp = fopen("output.txt", "w+");

    int i;

    int a[] = {1,2,5,6,7};


    for(i=0; i<5; i++){
        fprintf(fp,"%d\n", a[i]);
    }

    fclose(fp);

*/

}
