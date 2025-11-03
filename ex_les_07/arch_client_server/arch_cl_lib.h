    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MSG_KEY 1234
#define MSG_MTEXT_MAX 256

#define MSG_TYPE_REQUEST 1   // Tipo per le richieste standard
#define MSG_TYPE_TERMINATE 99 

typedef struct msgbuf {
    long mtype;
    char mtext[MSG_MTEXT_MAX];
}Message;

