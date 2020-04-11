#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = fopen("output.txt", "w+");

    int i;

    int a[] = {1,2,5,6,7};


    for(i=0; i<5; i++){
        fprintf(fp,"%d\n", a[i]);
    }

    fclose(fp);

}
