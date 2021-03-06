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

struct tabela_de_rotas{
    int no_atual;
    int destino;
    int custo;
    
};

struct NO{
    int no;
    int porta;
    char ip[100];
};


union tabela 
{ 
    struct tabela_de_rotas tabela_rotas[6];
 };


struct datagrama {
    
    int tam_buffer;
    int  no_envio;
    char buffer[100];
    int checksum;
    int controle;
    int offset;
    int id;
    int no_vizinho;
    int no_inicio;
    int no_prox;
    int frag;
    union tabela dados;
};


//Struct No -- Armazena as informações dos nos

//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..



struct getInfo{
    int no_de_inicio;
    char arg[100];
};

 




extern struct datagrama data_env, data_rcv;
extern struct datagrama buffer_env,buffer_rcv,buffer_rede_trans_env,buffer_rede_trans_rcv;
extern struct datagrama buffer_rede_enlace_env,buffer_rede_enlace_rcv;
extern struct getInfo info;






//Funçao teste que printa a matriz
void print_matriz(int,int);

//Funçao teste que printa a matriz mtu
void print_mtu(int,int);

//Funcoes Importantes


//retorna 1 caso haja ligacao, 0 caso nao.
int tem_ligacao(int, int);

//retorna o MTU, passando dois nos como parametro, caso nao haja ligacao entre os nós, retorna 0.
int getMtu(int,int);


////matriz -- Matriz adjacente que armazena os enlaces, se matriz[no1][no2] = 1 os NOS SAO VIZINHOS, caso 0 nao SAO VIZINHOS.
extern int matriz[10][10];

//mtu --  Matriz adjacente armazena os MTU dos enlaces.
extern int mtu[10][10];

extern int no_inicio;

extern struct tabela_de_rotas tabela_rotas[6];


extern struct NO nos[6];
//Threads

void *envia_Datagrama(void *);
void *recebe_Datagrama(void *);

int recebeEnlace();
int enviaEnlace();


void error(char *);


//Mutex Controle Externo
extern pthread_mutex_t controle_tabela;
extern pthread_mutex_t controle_rede_rcv;
extern pthread_mutex_t controle_rede_env;
extern pthread_mutex_t controle_randomico;
extern pthread_mutex_t controle_rede_enlace_env;
extern pthread_mutex_t controle_rede_enlace_rcv;

//Mutexes enlace
extern pthread_mutex_t rede_enlace_env1;
extern pthread_mutex_t rede_enlace_env2;
extern pthread_mutex_t rede_enlace_rcv1;
extern pthread_mutex_t rede_enlace_rcv2;


//Mutexes Redes

extern pthread_mutex_t rede_atualiza1;
extern pthread_mutex_t rede_atualiza2;

extern pthread_mutex_t rede_env1;
extern pthread_mutex_t rede_env2;
extern pthread_mutex_t rede_rcv1; 
extern pthread_mutex_t rede_rcv2;

extern pthread_mutex_t env_tabela1;
extern pthread_mutex_t env_tabela2;
extern pthread_mutex_t rcv_tabela1;
extern pthread_mutex_t rcv_tabela2;


extern pthread_mutex_t trans_rede_env1;
extern pthread_mutex_t trans_rede_env2;
extern pthread_mutex_t trans_rede_rcv1;
extern pthread_mutex_t trans_rede_rcv2;


extern pthread_mutex_t buffer_rede_env;
extern pthread_mutex_t buffer_rede_rcv;


//Mutexes Buffer

extern pthread_mutex_t buffer_rede_env;
extern pthread_mutex_t buffer_rede_rcv;

/*

void colocarArquivoStruct(FILE * fp, struct ligacoes * ligacao);
void retirarEspaco(char * string);
void montarFrame(struct frame *datagram);
void montarDatagrama(struct frame datagram);
void *enviarFrames(void *param);
void *receberFrames(void *param);
int checkSum(struct datagrama datagram);*/
