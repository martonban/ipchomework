#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>



struct mesg_buffer {
    long mesg_type;
    char szo[100][5][10];

}message;


int main()
{


	int i;

    FILE * fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("Problem with the input file!");
        exit(1);
    }

    char needIndex[5];

    fscanf(fp, "%[^\n]", needIndex);
    int index = atoi(needIndex);

    fclose(fp);





	char finishString[index][5][10];

    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok(".", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);



    // msgrcv to receive message
    for(int i=0; i<index; i++){
        for(int j=0; j<5; j++){
            msgrcv(msgid,  &message, sizeof(message), 1, 0);
            strcpy(finishString[i][j],message.szo[i][j]);
            printf("Data Received is : %s \n", message.szo[i][j]);  
        }
    }





    //Lezárjuk a Message Queue-t
    msgctl(msgid, IPC_RMID, NULL);


    //Kiirjuk az output.txt fileb
    FILE *fpp;
    fpp = fopen("output.txt", "w+");


    for(int i=0; i<index; i++){
        fprintf(fpp,"%s %s %s %s %s\n", finishString[i][0], finishString[i][1] ,finishString[i][2] ,finishString[i][3] ,finishString[i][4]);
    }

    fclose(fpp);
    
    return 0;


}
