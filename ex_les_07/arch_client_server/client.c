#include "arch_cl_lib.h"

int main(int argc, char *argv[]){

    // leggi N dalla riga di comando
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <numero_client_figli>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    size_t num_children = atoi(argv[1]);
    
    if (num_children <= 0) {
        fprintf(stderr, "Inserire un numero positivo di client.\n");
        exit(EXIT_FAILURE);
    }

    // mi collego alla coda esistente
    int msqid = msgget(MSG_KEY, 0600);


    // genero N processi
    for(size_t i = 0; i < num_children; i++){

        pid_t pid = fork();

        if(pid < 0){

            perror("fork error");
            exit(EXIT_FAILURE);
        }else if(pid == 0){
            // codice figlio-client
            Message request;

            request.mtype = MSG_TYPE_REQUEST;
            sprintf(request.mtext, "%d", getpid());
            
            size_t request_size = strlen(request.mtext) + 1;

            if(msgsnd(msqid, &request, request_size, 0) == -1){
                perror("msgsnd client failed");
                exit(EXIT_FAILURE);
            }
            
            printf("Client Figlio %d: Inviata richiesta (mtype %ld).\n", getpid(), request.mtype);

            Message response;

            if(msgrcv(msqid, &response, sizeof(response.mtext), getpid(), 0) == -1){
                perror("msgrcv client failed");
                exit(EXIT_FAILURE);
            }

            printf("Client Figlio %d: Ricevuta risposta: \"%s\"\n", getpid(), response.mtext);
            exit(EXIT_SUCCESS); // Il figlio termina qui
        }

    }

    // codice padre-client

    // aspetto la terminazione dei figli
    for(size_t i = 0; i < num_children; i++){
        wait(NULL);
    }

    printf("Padre Client: Tutti i figli sono terminati.\n");

    // 7. Quando tutti i figli sono terminati, invia il messaggio di fine al server
    Message terminate_msg;
    terminate_msg.mtype = MSG_TYPE_TERMINATE; // Tipo 99: Fine
    // Il payload non è necessario per questo messaggio, ma lo impostiamo vuoto
    sprintf(terminate_msg.mtext, " "); 

    if (msgsnd(msqid, &terminate_msg, 0, 0) == -1) { // Dimensione dati 0
        perror("msgsnd terminate failed");
        exit(EXIT_FAILURE);
    }
    printf("Padre Client: Inviato messaggio di terminazione al server.\n");

    return 0;
}