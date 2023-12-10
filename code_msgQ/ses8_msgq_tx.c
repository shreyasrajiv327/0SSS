// Lab11 MsgQ Tx process
// Compilation of this file
// gcc -o msgqtx lab11_msgq_tx.c -lrt
// Note here that you need to include the real-time (rt) library
// Remember to run this code only after the msgqrx is run first, 
// so that the Rx Msg Q is created
// before this process tries to access it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

#define MSG_TYPE_LEN 16
#define MSG_VAL_LEN  16

typedef struct{
char msg_type[MSG_TYPE_LEN];
char msg_val[MSG_VAL_LEN];
} my_msg_t;

static my_msg_t tx_msg;

#define RX_QUEUE_NAME   "/my_msgq_rx"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE sizeof(my_msg_t)
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE * MAX_MESSAGES) 


int main (int argc, char **argv)
{
    mqd_t qd_rx;   // Rx Msg queue descriptor
    int num = 1;

    if ((qd_rx = mq_open (RX_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Msq Tx: mq_open (qd_rx)");
        exit (1);
    }

    my_msg_t out_msg;
    strcpy(out_msg.msg_type, "Proc msg");   // strcpy(destPtr, srcPtr)
	sprintf (out_msg.msg_val, "%d", num);         

    printf ("I am going to send keep sending messages to the /my_msgq_rx queue ...\n");


    while (1) {

        // send message to my_msgq_rx queue
        // int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
        if (mq_send (qd_rx, (char *) &out_msg, sizeof(out_msg), 0) == -1) {
            perror ("MsgQ Tx: Not able to send message to the queue /my_msgq_rx");
            continue;
        }

        printf ("%d: MsgQ Tx: Message sent successfully\n", num);

        sleep(5);  // sleep for 5 seconds
        num++;
	sprintf (out_msg.msg_val, "%d", num);                 
    }


    if (mq_close (qd_rx) == -1) {
        perror ("MsgQ Tx: mq_close");
        exit (1);
    }

    if (mq_unlink (RX_QUEUE_NAME) == -1) {
        perror ("MsgQ Tx: mq_unlink");
        exit (1);
    }
    printf ("MsgQ Tx: bye\n");

    exit (0);
}
