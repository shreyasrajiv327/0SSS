#include <stdio.h>
#include <stdlib.h>

int findSum(int numParams, char * argv[]);
int findMax(int numParams, char * argv[]);

int main(int argc, char *argv[])
{
    printf("Find the sum of numbers entered by the user!!!\n");

    if(argc < 2){
        printf("Error: Insufficient parameters!!!\n");
        printf("Give at least one or more valid integer numbers as parameters.\n");
        return -1;
    }

    int numParams = argc -1;
    int max = 0;


    for(int i = 0; i < argc; i++){
        printf(" argv[%d] = %s\n", i, argv[i]);
    }

    max = findMax(numParams, argv);

    printf("\n The Max of numbers given is: %d\n", max);

    return 0;
}

int findMax(int numParams, char * argv[]){

   char *pParam;
   int max = 0;
   int num;

   pParam = argv[1];

   for(int i = 1; i <= numParams; i++ ){
     pParam = argv[i];  // Copy the pointer to the first parameter passed
     num = atoi(pParam);
     if(i==1)
     {
        max = 1;
     }
     else if (max<num)
     {
        max = num;
     }
    printf("\nThe maximum number is %d",max);
   }

    return max;
}