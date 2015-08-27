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

////Constantes

#define SIZE 1024


/*
 * Cliente UDP
 */

////matriz -- Matriz adjacente que armazena os enlaces, se matriz[no1][no2] = 1 os NOS SAO VIZINHOS, caso 0 nao SAO VIZINHOS.
int matriz[10][10];

//mtu --  Matriz adjacente armazena os MTU dos enlaces.
int mtu[10][10];

//Funçao teste que printa a matriz
void print_matriz(int,int);

//Funçao teste que printa a matriz mtu
void print_mtu(int,int);

//Funcoes Importantes


//retorna 1 caso haja ligacao, 0 caso nao.
int tem_ligacao(int, int);

//retorna o MTU, passando dois nos como parametro, caso nao haja ligacao entre os nós, retorna 0.
int getMtu(int,int);

//Struc No -- Armazena as informações dos nos

struct NO{

    int no;
    int porta;
    char ip[6];
    
};



struct NO nos[6];

//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..

//Threads

void *envia(void *);
void *recebe(void *);

struct threadsParam{
    int no;
    char data[1024];
    
};

int recebeEnlace();

int no_do_enlace; // Numero do nó iniciado;

int iniciaEnlace(int no, char *argv){

   
  
  no_do_enlace = no;
 

  int node=0;     
  int number; 
  int elem1;
  int elem2;
  int elem3;
  int elem4; 
  int porta;

 
 
  char str[50];
  FILE *arq;
  
  int ret=6;

    
  arq = fopen(argv, "r");
    
    
  if(arq == NULL)
      printf("Erro, nao foi possivel abrir o arquivo\n");
  else{

        
      
       fscanf(arq,"%s",str);

    
          do{
             
              
            ret = fscanf(arq,"%d: IP = %d.%d.%d.%d, Porta = %d;", &number,&elem1,&elem2,&elem3,&elem4,&porta);
            
            if(ret >= 6){
              printf("%d\n%d.%d.%d.%d\n%d\n", number,elem1,elem2,elem3,elem4,porta);

            
             nos[node].no = number;
             nos[node].porta = porta;

             sprintf(nos[node].ip,"%d.%d.%d.%d",elem1,elem2,elem3,elem4);
            //printf("\nFRI:%s\n\n", fri);
             node++;
          }
          }while(ret >= 6);

        ret=3;
        fscanf(arq,"%s",str);

        do{
            ret = fscanf(arq,"%d -> %d, MTU = %d;", &number,&elem1,&elem2);
            
            if(ret >= 3){
             // printf("%d -> %d, MTU = %d;\n", number,elem1,elem2);
              matriz[number-1][elem1-1]=1;
              matriz[elem1-1][number-1]=1;
              mtu[number-1][elem1-1]=elem2;
              mtu[elem1-1][number-1]=elem2;
            }
          }while(ret >= 3);

        
        printf("\n");
  

        
}


//Testando funcoes

  /*printf("%d: IP:::::::::%s,PORTA = %d\n",nos[0].no,nos[0].ip,nos[0].porta );
  printf("%d: IP:::::::::%s,PORTA = %d\n",nos[1].no,nos[1].ip,nos[1].porta );
  printf("%d: IP:::::::::%s,PORTA = %d\n",nos[2].no,nos[2].ip,nos[2].porta );
  printf("%d: IP:::::::::%s,PORTA = %d\n",nos[3].no,nos[3].ip,nos[3].porta );
  fclose(arq);

  printf("\n");
  print_matriz(4,4);
  printf("\n");
  print_mtu(4,4);
  printf("\n");
  
  printf("\ntem ligacao:%d\n\n", tem_ligacao(1,2));

  printf("\nMTU:%d\n\n", getMtu(1,2));

////UDP
    
    
    
  */
    
    recebeEnlace();
  return 0;
}


//Threads  -------------

void error(char *msg){
 perror(msg);
    
 exit(0);
    
}

int v[10];
void *envia(void *thread){
  struct threadsParam *readParams = thread;
 // char *dado = datagram;  

    
    int teste;
    printf("\nEnvia executando...\n");
    printf("\n%d ::: %s\n",readParams->no, readParams->data);
    int sock,length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *hp;
    
    char buffer[256];
    
    sock = socket(AF_INET, SOCK_DGRAM,0);
    
    if(sock < 0){
        error("socket");
        
    }
    
    server.sin_family = AF_INET;
    hp = gethostbyname("localhost"); //Localhost
    
    if(hp == 0){
        error("Uknown host");
        
    }
    
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    
    server.sin_port = htons(atoi("5000")); //5000
    length=sizeof(struct sockaddr_in);
    
    
    
    bzero(buffer, 256);
    fgets(buffer,255,stdin);
    
    //scanf("%d",&teste);
    
    strcpy(buffer,readParams->data);
    
    
    
    if(tem_ligacao(no_do_enlace,readParams->no)){
    n=sendto(sock,buffer,strlen(buffer),0,&server,length);
    
    if(n < 0 ){
        error("Sendto");
    }
    //RECEBE GOT YOUR MESSAGE
    n=recvfrom(sock,buffer,256,0,&from,&length);

    if(n < 0){
        error("recvfrom");
    }
    
        write(1,"\nGot an ack: ",14);
        write(1,buffer,n);
    }
    else{
        
        fprintf(stdout,"\nNós não são vizinhos\n");
        
    }
    
    
    
}



void *recebe(void *thread)
{
  int id=*(int *)thread;
    
    int sock,length,fromlen, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    
    
    char buf[1024];
    
    sock=socket(AF_INET, SOCK_DGRAM,0);
    
    if(sock < 0){
        error("Opening socket");
    }

    length = sizeof(server);
    
    bzero(&server, length);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi("5000"));
    
    if(bind(sock,(struct sockaddr *)&server,length) < 0){
        error("binding");
    }
    
    fromlen = sizeof(struct sockaddr_in);
    
    while(1){
         //printf("\nRecebe executando...e esperando\n");
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        
        if(n < 0){
         error("recvfrom");   
        }
        
        write(1,"Received a datagram: ",21);
        
        write(1, buf, n);
        
        n=sendto(sock,"Got your message\n",17,0,(struct sockaddr *)&from,fromlen);
        
        if(n < 0){
            
           error("sendTo"); 
        }
        
        
    }
    
   
   
}

int enviaEnlace(int no, char datagrama[], int tamanho){


  //dispara uma thrread que envia para um nó. da thread crriada em inicia enlace
    
    pthread_t t1;
    struct threadsParam readParams;
    printf("CHEGOU o %s",datagrama);
    
    
    readParams.no = no;
    strcpy(readParams.data,datagrama);
    
    
    pthread_create(&t1, NULL, envia, (void *)(&readParams));
    pthread_join(t1, NULL);
    //printf("No : %d Datagrama : %s Tamanho : %d\n\n", no, datagrama, tamanho);
    
   
    printf("\n\n");
	return 0;
}

int recebeEnlace(){
    
    //dispara thread recv
    
    pthread_t t2;
    
    int a2 = 2;
    
    
    pthread_create(&t2, NULL, recebe, (void *)(&a2));
    
    //pthread_join(t2, NULL);
    return 0;   
}


  /*int idC;
  printf("Barbeiro #%d iniciou...\n", id);
  usleep(1000);
  
  while (1 == 1) {
      
        // down(&customers);
	
	
        
	idC=clienteID;
	
	//down(&exc_aces);
	pthread_mutex_lock(&exc_aces); 

	waiting=waiting-1;
	
	//up(&exc_aces);
	pthread_mutex_unlock(&exc_aces); 
	
	cut_hair(id,idC);
	//up(barbers);
	
	
	
  }*/
  
   
 




    
 /* printf("Cliente #%d iniciou...\n", id);
  usleep(1000);
  
        //down(&exc_aces);	
	pthread_mutex_lock(&exc_aces); 
		       
        if( waiting < NUM_CHAIRS)
	{
		gettimeofday(&start_time[id], NULL );	  
			
		waiting=waiting+1;
		       
		clienteID=id;
		       
		
		//up(&custumers);
		pthread_mutex_unlock(&exc_aces); 
		//up(&exc_aces);
		
		//down(&barbers);
		       
		pthread_mutex_lock(&apreciate); 
		//apreciate_hair(id);
		pthread_mutex_unlock(&apreciate);
			
        }
        else{
		 //up(&exc_aces);
		pthread_mutex_unlock(&exc_aces); 
		
		fflush(stdout);
		fprintf(stdout,"\nCliente %d não foi atendido.\n\n",id);
		fflush(stdout);
		pthread_exit(NULL);
                         
	}
  
  //sleep(15);
 // printf("Terminando cliente:%d\n",id);

  pthread_exit(NULL);*/






//Funções Auxiliares 


void print_matriz(int lin, int col){


    for(int x=0;x<lin;x++)
    {
        for(int y=0;y<col;y++)
        {
            printf("%d ", matriz[x][y]);
        }

        printf("\n");
    }


}

void print_mtu(int lin, int col){


  for(int x=0;x<lin;x++)
    {
        for(int y=0;y<col;y++)
        {
            printf("%d ", mtu[x][y]);
        }

        printf("\n");
    }

}

int tem_ligacao(int no1,int no2){

    if(matriz[no1][no2])
      return 1;
    return 0;

}

int getMtu(int no1, int no2){

    if(!tem_ligacao(no1,no2))
      return 0;
    return mtu[no1][no2];

}

