#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define KEY 1234 // Unique key for the message queue

struct msg_buffer {
    long mtype;       // Message type (must be > 0)
    char mtext[100];  // Message data
};