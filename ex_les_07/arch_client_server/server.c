#include "arch_cl_lib.h"

int main(){

    int msqid;
    long mtype = 0;

    msqid = msgget(MSG_KEY, 0666 | IPC_CREAT);

    Message message;

    pid_t pid;

    while(1){

        printf("In attesa di messaggi dal client\n");

        // msgrcv bloccante (msgtype=0 per ricevere qualsiasi tipo)
        if(msgrcv(msqid, &message, sizeof(message.mtext), mtype, 0) == -1){
            
            // Gestione errori che potrebbero interrompere msgrcv
            if (errno == EINTR || errno == EIDRM) break; 
            perror("msgrcv padre failed");
            continue;
            
        }

        // Controlla il tipo di messaggio ricevuto
        if (message.mtype == MSG_TYPE_TERMINATE) {
            printf("Server: Ricevuto messaggio di terminazione.\n");
            // Dealloca la coda e termina il server padre
            msgctl(msqid, IPC_RMID, NULL);
            exit(EXIT_SUCCESS); 
        }

        printf("Message of type %ld received.\n", message.mtype);
        printf("Message received by pid: %s\n", message.mtext);
        printf("\n");

        pid = fork();

        if(pid < 0){ // errore fork
            perror("fork error");
            exit(EXIT_FAILURE);

        }else if(pid == 0){ // codice figlio

            Message msg_response;
            msg_response.mtype = atol(message.mtext);
            sprintf(msg_response.mtext, "Risposta da server figlio");

            ssize_t response_size = strlen(msg_response.mtext) + 1;

            if(msgsnd(msqid, &msg_response, response_size, 0) == -1){

                perror("msgsend failed in child\n");
            }
            
            exit(EXIT_SUCCESS);
        }else{
            // il padre torna al while()
        }

    } // while

    return 0;
}