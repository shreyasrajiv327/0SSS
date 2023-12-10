#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>    // for sleep()
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>

// Compilation of this file
// gcc -o msgq ses8_msgq_threads.c -lrt -lpthread
// Note here that you need to include both the real-time (rt) and pthread libraries

#define MSG_TYPE_LEN 16
#define MSG_VAL_LEN  16

typedef struct{
char msg_type[MSG_TYPE_LEN];
char msg_val[MSG_VAL_LEN];
} my_msg_t;

static my_msg_t rx_msg;

#define RX_QUEUE_NAME   "/my_msgq_thread_rx"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE sizeof(my_msg_t)
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE * MAX_MESSAGES) 

void *thread_function(void *);

int main (int argc, char **argv) {
    mqd_t qd_rx;   // Rx Msg queue descriptor
    int num = 1;

    // Client thread related
    int res;
    char *t_stat;
    pthread_t thread;

    printf ("MsgQ Rx: Welcome!!!\n");

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_rx = mq_open (RX_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS,
                           &attr)) == -1) {
        perror ("MsgQ Rx: mq_open (rx_msgq)");
        exit (1);
    }

    if( (res = pthread_create(&thread, NULL, &thread_function, "Client Thread")) ) {
      printf("Server: Client Thread creation failed: %d\n", res);
      exit(1);
    }    
    
    my_msg_t in_msg;

    while (1) {
        // ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
        if (mq_receive (qd_rx,(char *) &in_msg, MAX_MSG_SIZE, NULL) == -1) {
            perror ("Rx Msg Q: mq_receive");
            exit (1);
        }

	printf ("%d: Rx MsgQ: message received.\n", num);
	printf("Rx msg type = %s\n", in_msg.msg_type);
	printf("Rx msg val = %s\n", in_msg.msg_val);
	num++;
    }  // end of while()
    
}  // end of main()

void *thread_function(void *pThreadName)
{
    mqd_t qd_tx;   // Rx Msg queue descriptor
    int num = 1;

    if ((qd_tx = mq_open (RX_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Msq Tx: mq_open (qd_tx)");
        exit (1);
    }
    static my_msg_t out_msg;
    strcpy(out_msg.msg_type, "Thread msg");   // strcpy(destPtr, srcPtr)
    sprintf (out_msg.msg_val, "%d", num);         
		
    printf ("I am going to keep sending messages to the /my_msgq_rx queue ...\n");

    while (1) {
        // send message to my_msgq_rx queue
        // int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
        if (mq_send (qd_tx, (char *) &out_msg, sizeof(out_msg), 0) == -1) {
            perror ("MsgQ Tx: Not able to send message to the queue /my_msgq_rx");
            continue;
        }

        printf ("MsgQ Tx: Message sent successfully\n");

        sleep(5);  // sleep for 5 seconds
        num++;
	sprintf (out_msg.msg_val, "%d", num);        
    };


}  // end of thread_function()





