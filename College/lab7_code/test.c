//All essential include files are assumed to be here.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *threadFn(void *arg);
int main(){
void *thread_result;
pthread_t id1;
pthread_t id2;
pthread_create(&id1, NULL, threadFn, NULL);
pthread_create(&id2, NULL, threadFn, NULL);
pthread_join(id1, &thread_result);
pthread_join(id2, &thread_result);
printf("I am here ...\n");
while(1);
}
void * threadFn(void *arg){
printf("Thread is created.\n");
sleep(2);
printf("I am going to exit.\n");
pthread_exit(NULL);
}