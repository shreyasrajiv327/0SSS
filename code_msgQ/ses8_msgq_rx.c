// Lab11 MsgQ Rx process
// Compilation of this file
// gcc -o msgqrx lab11_msgq_rx.c -lrt
// Note here that you need to include the real-time (rt) library

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MSG_TYPE_LEN 16
#define MSG_VAL_LEN  16

typedef struct{
char msg_type[MSG_TYPE_LEN];
char msg_val[MSG_VAL_LEN];
} my_msg_t;

static my_msg_t rx_msg;

#define RX_QUEUE_NAME   "/my_msgq_rx"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE sizeof(my_msg_t)
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE * MAX_MESSAGES) 

int main (int argc, char **argv)
{
    mqd_t qd_rx;   // Rx Msg queue descriptor
    int num = 1;

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
    }
}
