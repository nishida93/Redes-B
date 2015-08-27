#include <stdio.h>    /* for printf()*/ 
#include <stdlib.h>   /* for exit(1);*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>              /* errno and error codes */
#include <sys/time.h>           /* for gettimeofday() */
#include <stdio.h>              /* for printf() */
#include <unistd.h>             /* for fork() */
#include <sys/types.h>          /* for wait() */
#include <sys/wait.h>           /* for wait() */
#include <signal.h>             /* for kill(), sigsuspend(), others */
#include <sys/ipc.h>            /* for all IPC function calls */
#include <sys/shm.h>            /* for shmget(), shmat(), shmctl() */
#include <sys/sem.h>            /* for semget(), semop(), semctl() */
#include <string.h>
#include <sys/msg.h>    /* for msgget(), msgctl() */     
#include <sys/types.h>    /* for wait(), msgget(), msgctl() */   


/*
 * Cliente UDP
 */





//Chama a funcao do enlace: enviaEnlace()

int iniciaTeste(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int no=10;
    char *datagrama;
    
    
    
    fflush(stdout);
    printf("Deseja enviar para qual nó?\n");
    scanf("%d", &no); 
    
    printf("Escreva uma mensagem para enviar:\n");
  
    fflush(stdout);
    const int bufsize = 4096; /* Or a #define or whatever */
    char buffer[bufsize];
    fflush(stdout);
    //fgets(buffer, bufsize, stdin);
    
    scanf("%s",buffer);
    printf("%s\n\n",buffer);
    
    //Chama envia enlace;
    enviaEnlace(no,buffer, 3);
    

	return 0;

}


