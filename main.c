#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



// Függvény deklarálása
int check (int,int,int);

// A Messege Queue-hez szükséges struktúra
struct mesg_buffer {
    long mesg_type;
    char szo[100][5][10];
}message;


int main(int argc, char* argv[])
{


    int i;
	
	//File megnyitása
    FILE * fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("Problem with the input file!");
        exit(1);
    }

    char needIndex[5];

	//Kiszedjük az első számot majd átalakítjuk számmá
    fscanf(fp, "%[^\n]", needIndex);
    int index = atoi(needIndex);

	// A szükséges váltózók és tömbök létrehozása 
    char line[256];
    int num[3];
    int j;
    int k = -1;
    int z;
    int num2;
    int numFinal[index][3];

	// Itt végigmegyünk az össze soron 
	// Kiszűri azokat a sorokat, amik nem felelnek meg (Az első sort)
	// Majd ezeket áralakítja int-é és brölt őket egy tömbe
    while(fgets(line, sizeof(line), fp)) {
        if (strlen(line)>2 && k<index){
            j = 0;
            for(i=0; i<strlen(line); i++){
                if(i==0 || i%2==0){
                    char* tmp = &line[i];
                    num2 = atoi(tmp);
                    numFinal[k][j] = num2;
                    j++;
                }
            }
        }

        k++;
    }



	//Ezek leszenk az eredmények String-jei
    char resString1[10];
    char resString2[10];
    char nope = '-';

	//Ezt a String tömböt fogom elküldeni
    char finishString[index][5][10];

	//Idéglenes változók létrehozása
    int a,b,c;


	// Kiszámoljuk az eredményeket
	// Először ellenörzi, hogy van e eredménye az egynletnek. Ha nincs akkor "-" lesz az eredmény jelezve, hogy nincs megoldás
	// Átalakítjja Stringé az eredményket és az alap adatokkal együtt betölti a egy String tömbe amit át fogunk küldeni.
    for(i=0; i<index; i++){

        double resr1,resr2 = 0;

        a = numFinal[i][0];
        b = numFinal[i][1];
        c = numFinal[i][2];

        if(check(a,b,c)== 0){
            resString1[0] = nope;
            resString1[1] = '\0';
            resString2[0] = nope;
            resString2[1] = '\0';
            strcpy(finishString[i][3], resString2);
            strcpy(finishString[i][4], resString1);
        }
        else{
            resr1 = sqrt((pow(b,2)-(4*a*c)));
            resr2 = ((-1)*b) - resr1;
            resr1 += (-1)*b;
            resr1 /= 2.0*a;
            resr2 /= 2.0*a;

            double* egy = &resr1;
            double* ketto = &resr2;


            sprintf(finishString[i][3], "%f", resr1);
            sprintf(finishString[i][4], "%f", resr2);
        }


        sprintf(finishString[i][0], "%d", numFinal[i][0]);
        sprintf(finishString[i][1], "%d", numFinal[i][1]);
        sprintf(finishString[i][2], "%d", numFinal[i][2]);
    }


    
	// A teljes tömböt áttölti a Struktúra tömbjébe 
    for(i=0; i<index; i++){
        for (j=0; j<5; j++){
            strcpy(message.szo[i][j],finishString[i][j]);
        }
    }


	// Lázáródik a file írás
    fclose(fp);

	// Létrehozzuk, a szükséges változókat, az IPC-hez
    key_t key;
    int msgid;
	
	// Az ftokkal létrehozunk a kucsot amely szükséges lesz ahhoz, hogy kommunikáljuk a másik processel
    key = ftok(".", 65);

	// msgget létrehozza a message queue-t
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

	// A msgsnd megfeelő paraméterezésével elküldjük az adatokat
	// Az stdout-ra kiiratjuk az általunk küldött adatokat
    for(i=0; i<index; i++){
        for (j=0; j<5; j++){
            msgsnd(msgid, (void *) &message, sizeof(message), 0);
            printf("%s ",message.szo[i][j]);
        }
        printf("\n");
    }



}

// Függvény definició
// Ez a függvény határozza meg azt, hogy az egyenletnek van e megoldása 
int check (int a,int b, int c){

    int pos = 0;

    int result = (pow(b,2)-(4*a*c));

    if(result>=0){
        pos = 1;
    }else{
        pos = 0;
    }

    return pos;

}