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
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>

struct tabela_rotas{
    int quem_enviou;
    int destino;
    int custo;
    int saida;
};


struct datagrama {
    
    int tam_buffer;
    int  no_envio;
    char buffer[100];
    int checksum;
};

//Struct No -- Armazena as informações dos nos


struct NO{
    int no;
    int porta;
    char ip[100];
    
};

struct getInfo{
    int no_de_inicio;
    char arg[100];
};



//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..
 
////matriz -- Matriz adjacente que armazena os enlaces, se matriz[no1][no2] = 1 os NOS SAO VIZINHOS, caso 0 nao SAO VIZINHOS.
extern int matriz[10][10];

//mtu --  Matriz adjacente armazena os MTU dos enlaces.
extern int mtu[10][10];




extern struct NO nos[6];



extern struct datagrama data_env, data_rcv;
extern struct getInfo info;
pthread_mutex_t env1, env2;
pthread_mutex_t rcv1, rcv2;

////Threads

void *Prod_rede();
void *Cons_rede();
void *Envia_tabela();
void *Recebe_tabela();
