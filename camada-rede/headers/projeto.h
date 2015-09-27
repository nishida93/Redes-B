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
    int no_atual;
    int destino;
    int custo;
    
};

struct NO{
    int no;
    int porta;
    char ip[100];
};


struct datagrama {
    
    int tam_buffer;
    int  no_envio;
    char buffer[100];
    int checksum;
};

struct getInfo{
    int no_de_inicio;
    char arg[100];
};


struct datagrama data_env, data_rcv;
struct getInfo info;
pthread_mutex_t env1, env2;
pthread_mutex_t rcv1, rcv2;

////matriz -- Matriz adjacente que armazena os enlaces, se matriz[no1][no2] = 1 os NOS SAO VIZINHOS, caso 0 nao SAO VIZINHOS.
int matriz[10][10];

//mtu --  Matriz adjacente armazena os MTU dos enlaces.
int mtu[10][10];

int no_inicio;

struct tabela_rotas tabela_rotas[6];

struct NO nos[6];

void iniciaEnlace(int, char []);
void iniciaRede();

//Mutex

pthread_mutex_t mutex_rede_enlace_env1, mutex_rede_enlace_env2;
pthread_mutex_t mutex_rede_enlace_rcv1, mutex_rede_enlace_rcv2;
pthread_mutex_t mutex_rede_rede_atualizei1, mutex_rede_rede_atualizei2;
pthread_mutex_t mutex_rede_rede_receberotas2;
pthread_mutex_t mutex_rede_rede_env1, mutex_rede_rede_env2;
pthread_mutex_t mutex_rede_rede_rcv1, mutex_rede_rede_rcv2;
pthread_mutex_t mutex_trans_rede_env1, mutex_trans_rede_env2;
pthread_mutex_t mutex_trans_rede_rcv1, mutex_trans_rede_rcv2;

pthread_mutex_t env_tabela1;
pthread_mutex_t env_tabela2;

//void *iniciaEnlace();
//void *iniciaTeste();