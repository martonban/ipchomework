#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


//Létrhozzuk, a szükséges struktúrát
struct mesg_buffer {
    long mesg_type;
    char szo[100][5][10];

}message;


int main()
{


	int i;

	// Kivesszük, az input.tx-ből az első számot , hogy tudjuk meddig kell menni 

    FILE * fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("Problem with the input file!");
        exit(1);
    }

    char needIndex[5];

	
	// Egyenlővé teszük az index váltózóval
    fscanf(fp, "%[^\n]", needIndex);
    int index = atoi(needIndex);

    fclose(fp);




	// Létrehozzuk azt a tömböt, amibe majd be másolunk mindent amit ki kell majd írnunk a fileban.
	char finishString[index][5][10];

	//Létrehozzuk, a szükséges változókat, az IPC-hez
    key_t key;
    int msgid;

    // Az ftokkal létrehozunk a kucsot amely szükséges lesz ahhoz, hogy kommunikáljuk a másik processel
    key = ftok(".", 65);

    // msgget létrehozza a message queue-t
    msgid = msgget(key, 0666 | IPC_CREAT);



    // A msgrcv megfeelő paraméterezésével elküldjük az adatokat
	// A kapott adatokat átmásoljuk a finishString tömben, hogy kiirhasuk a fileba
	//stdout-ra kiirjuka  a kapott adatokat soronként
	 
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
