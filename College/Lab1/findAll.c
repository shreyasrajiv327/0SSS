#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int findSum(int numParams, char * argv[]);
int findMax(int numParams, char * argv[]);
int findAvg(int numParams, char * argv[]);
int findMin(int numParams, char * argv[]);

int main(int argc, char *argv[])
{
    printf("Find the sum of numbers entered by the user!!!\n");

    if(argc < 2){
        printf("Error: Insufficient parameters!!!\n");
        printf("Give at least one or more valid integer numbers as parameters.\n");
        return -1;
    }

    int numParams = argc -1;
    int sum =0;
    int max = 0;
    int min = 0;
    int Avg = 0;


    for(int i = 0; i < argc; i++){
        printf(" argv[%d] = %s\n", i, argv[i]);
    }
    char *operation=argv[1];
    if (strcmp(operation,"SUM")==0)
        {
            sum = findSum(numParams, argv);

    printf("The sum of numbers given is: %d\n", sum);
        }
    else if (strcmp(operation, "MIN") == 0) {
        min = findMin(numParams, argv);
        printf("\n The Min of numbers given is: %d\n", min);

    } else if (strcmp(operation, "MAX") == 0) {
         max = findMax(numParams, argv);
        printf("\n The Max of numbers given is: %d\n", max);
    } else if (strcmp(operation, "AVG") == 0) {
        Avg = findAvg(numParams, argv);

    printf("The Avg of numbers given is: %d\n", Avg);
    } else {
        printf("Unknown operation: %s\n", operation);
        return 1;
    }
   

   

    return 0;
}

int findMax(int numParams, char * argv[]){

   char *pParam;
   int max = 0;
   int num;

   pParam = argv[2];

   for(int i = 2; i <= numParams; i++ ){
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
int findMin(int numParams, char * argv[]){

   char *pParam;
   int min = 0;
   int num;

   pParam = argv[2];

   for(int i = 2; i <= numParams; i++ ){
     pParam = argv[i];
     num = atoi(pParam);
     if(i==2)
     {
        min = num;
     }
     else if (min>num)
     {
        min = num;
     }
    printf("\nThe minimum number is %d",min);
   }

    return min;
}


int findAvg(int numParams, char * argv[]){

   char *pParam;
   int sum = 0;
   int num,i,no;

   pParam = argv[2];

   for(i = 1; i <= numParams; i++ ){
     pParam = argv[i];  
     num = atoi(pParam);
     sum += num;
     no=i;
   }
   int avg=sum/no;

    return avg;
}

int findSum(int numParams, char * argv[]){

   char *pParam;
   int sum = 0;
   int num;

   pParam = argv[2];

   for(int i = 2; i <= numParams; i++ ){
     pParam = argv[i];  // Copy the pointer to the first parameter passed
     num = atoi(pParam);
     sum += num;
     printf("pParam = %s, sum = %d\n", pParam, sum);
   }

    return sum;
}