//
//  enlace.h
//
//  Guilherme Sividal - 09054512 
//  Vitor Rodrigo Vezani - 10159861
//
//  Created by Vitor Vezani on 19/03/13.
//  Copyright (c) 2013 Vitor Vezani. All rights reserved.
//

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

struct datagrama {
    
    int tam_buffer;
    int  no_envio;
    char buffer[100];
    int checksum;
};

//Struct No -- Armazena as informações dos nos

//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..
struct NO{
    int no;
    int porta;
    char ip[100];
    
};


struct getInfo{
    int no_de_inicio;
    char arg[100];
};

 




extern struct datagrama data_env, data_rcv;
extern struct getInfo info;
pthread_mutex_t env1, env2;
pthread_mutex_t rcv1, rcv2;






//Funçao teste que printa a matriz
void print_matriz(int,int);

//Funçao teste que printa a matriz mtu
void print_mtu(int,int);

//Funcoes Importantes


//retorna 1 caso haja ligacao, 0 caso nao.
int tem_ligacao(int, int);

//retorna o MTU, passando dois nos como parametro, caso nao haja ligacao entre os nós, retorna 0.
int getMtu(int,int);



//Threads

void *envia(void *);
void *recebe(void *);

int recebeEnlace();
int enviaEnlace();

/*

void colocarArquivoStruct(FILE * fp, struct ligacoes * ligacao);
void retirarEspaco(char * string);
void montarFrame(struct frame *datagram);
void montarDatagrama(struct frame datagram);
void *enviarFrames(void *param);
void *receberFrames(void *param);
int checkSum(struct datagrama datagram);*/