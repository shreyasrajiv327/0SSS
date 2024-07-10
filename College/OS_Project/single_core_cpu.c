#define _GNU_SOURCE     
#include <stdio.h>
#include <unistd.h>     
#include <pthread.h>
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)

#include <assert.h>
#include <stdbool.h> 

#include <sched.h> 
#include <time.h>

#define MAX_NUM_CHILD_THREADS 3
#define MAX_ARRAY_SIZE 1000

int childNumArr[MAX_NUM_CHILD_THREADS] = {1, 2, 3};

void swap(double *x, double *y){
    double temp = *x;
    *x = *y;
    *y= temp;
}

void dataProcessing(void){

    double dArr[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
    for(int i = 0; i < MAX_ARRAY_SIZE; i++){
        for(int j = 0; j < MAX_ARRAY_SIZE; j++){
           dArr[i][j] = i+j;
        }
    }

    //Tranposing the matrix
   for(int i=0; i<MAX_ARRAY_SIZE; i++){
     for(int j=i+1; j<MAX_ARRAY_SIZE; j++)
         swap(&dArr[i][j], &dArr[j][i]);
    }

   //Reversing each row of the dArrrix
   for(int i=0; i<MAX_ARRAY_SIZE; i++){
     for(int j=0; j<MAX_ARRAY_SIZE/2; j++){
        swap(&dArr[i][j], &dArr[i][MAX_ARRAY_SIZE-j-1]);
     }
   }



}



void *childThreadFn(void *param){

    int childNum = *(int *)param;

    cpu_set_t coreID;
    unsigned int cpuNum;
    unsigned int nodeNum;
    CPU_SET(0x01, &coreID);  

    if (sched_setaffinity(0,sizeof(cpu_set_t), &coreID) == -1) {
        perror("Sched_setaffinity()");
        assert(false);
    }
    getcpu(&cpuNum, &nodeNum);
    printf("Child num = %d, running on CPU ID = %d\n",
            childNum, cpuNum);
    printf("Child %d: Rotating a matrix by 90 degree\n",childNum);
    for(int i = 0; i < 10000; i++){
        dataProcessing();   
    }

    pthread_exit(NULL);
}


int main()
{

    pthread_t childThreadIds[MAX_NUM_CHILD_THREADS];
    int ret; 

    time_t startTime = 0;
    time_t endTime = 0;
    double diffTime = 0.0;

    printf("Multiple threads running on a single core.\n\n");

    cpu_set_t coreID;
    CPU_SET(0x00, &coreID);  

    if (sched_setaffinity(0, sizeof(cpu_set_t), &coreID) == -1) {
        perror("Sched_setaffinity()");
        assert(false);
    }


    time(&startTime);

    for(int i = 0; i < MAX_NUM_CHILD_THREADS; i++){ 

        ret = pthread_create(&childThreadIds[i],NULL, childThreadFn, (void *) &childNumArr[i]); 

        if(ret == 0){
            continue;
        }
        else{
            printf("Child %u Thread was not created.\n", childNumArr[i]);
            return 0;
        }

    }
    printf("Child 1,2,3 created \n");

    for(int i = 0; i < MAX_NUM_CHILD_THREADS; i++){
        pthread_join(childThreadIds[i], NULL);
        printf("Child %u has exited.\n", (i+1));
    }

    time(&endTime); // get time in seconds
    diffTime = difftime(endTime, startTime);
    printf("The total time taken for processing is: %f seconds\n", diffTime);

    printf("\nAll child threads have exited. The parent process is going to end now.\n");

    return 0; // main parent process exits
}
