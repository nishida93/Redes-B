


#include "headers/enlace.h"

////Constantes

#define SIZE 1024


/*
 * Cliente UDP
 */

////matriz -- Matriz adjacente que armazena os enlaces, se matriz[no1][no2] = 1 os NOS SAO VIZINHOS, caso 0 nao SAO VIZINHOS.
int matriz[10][10];

//mtu --  Matriz adjacente armazena os MTU dos enlaces.
int mtu[10][10];




struct NO nos[6];

//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..
 


struct threadsParam{
    int no;
    int tam;
    char data[1024];
    
};



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

    char aux[10]="";
          do{
             
              
            ret = fscanf(arq,"%d: IP = %d.%d.%d.%d, Porta = %d;", &number,&elem1,&elem2,&elem3,&elem4,&porta);
            
            if(ret >= 6){
                
            if(node != 4){    
              
            
             nos[node].no = number;
             nos[node].porta = porta;
            fflush(stdout);
                 fflush(stdin);
             sprintf(nos[node].ip,"%d.%d.%d.%d",elem1,elem2,elem3,elem4);
               fflush(stdin);
                 fflush(stdout);
                
            //printf("\nFRI:%s\n\n", nos[3].ip);
                //strcpy(nos[node].ip,nos[node].ip);
             node++;
            }
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

        
        
  

        
}


//Testando funcoes
/*
  printf("%d: IP:::::::::%s,PORTA = %d\n",nos[0].no,nos[0].ip,nos[0].porta );
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
    printf("\nFRI:%s\n\n", nos[2].ip);
    
    
  
  */  
  recebeEnlace();
  return 0;
}


//Threads Produtor e Consumido  -------------

void error(char *msg){
 perror(msg);
    
 exit(0);
    
}

int v[10];

//Recebe Datagrama
void *Prod_enlace(void *thread)
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
    
    
    server.sin_addr.s_addr = inet_addr(nos[no_do_enlace-1].ip);
    server.sin_port = htons(nos[no_do_enlace-1].porta);
    
    if(bind(sock,(struct sockaddr *)&server,length) < 0){
        error("binding");
    }
    
    fromlen = sizeof(struct sockaddr_in);
    
    while(1){
        
         pthread_mutex_lock(&rcv1);
         
         /*printf("\nRecebe executando...e esperando\n");
         printf("\nFRI:%s\n\n", nos[1].ip);
         printf("RECEBE:::::IP:::::%s PORTA::::%d",nos[no_do_enlace-1].ip,nos[no_do_enlace-1].porta);
        */
        /*
        

    while (TRUE) {

        struct frame frame_rcv;
        int sum = 0;

        from_address_size = sizeof (from);
        if (recvfrom(s, &frame_rcv, sizeof (frame_rcv), 0, (struct sockaddr *) &from, &from_address_size) < 0) {
            perror("recvfrom()");
            exit(1);
        }
        
        */
        
        
        n = recvfrom(sock,&data_rcv,1024,0,(struct sockaddr *)&from,&fromlen);
        
        if(n < 0){
         error("recvfrom");   
        }
        
        write(1,"Received a datagram: ",21);
        
        write(1, buf, n);
        
        
        //strcpy(data_rcv.buffer,buf);///<---------------------------
        //data_rcv.tam_buffer = strlen(buf);
        
        
        //RECALCULA CHECKSUM
        
        
        //Mensagem Confirmando Recebimento
        /*n=sendto(sock,"Got your message\n",17,0,(struct sockaddr *)&from,fromlen);
        
        if(n < 0){
            
           error("sendTo"); 
        }*/
         pthread_mutex_unlock(&rcv2);
        
    }
    
    
   
    //FUNCAO PARA CHAMAR RECEBE DO TESTE ou loop infinito??
    
   
   
}

//Envia Datagrama
void *Cons_enlace(void *thread){
  struct threadsParam *readParams = thread;
 // char *dado = datagram;  

    
    int teste;
    printf("\nEnvia executando...\n");
    //printf("\n%d ::: %s\n",readParams->no, readParams->data);
    int sock,length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *hp;
    
    int mtu=0;
    
    
    char buffer[256];
    
    pthread_mutex_lock(&env2);
    
    sock = socket(AF_INET, SOCK_DGRAM,0);
    
    if(tem_ligacao(no_do_enlace,readParams->no)){
    
        
        mtu = getMtu(no_do_enlace,readParams->no);
        
        //printf("ENVIA::::IP:::::%s PORTA::::%d",nos[readParams->no-1].ip,nos[readParams->no-1].porta);
        //printf("Mtu:::%d\n\n",mtu);
        
    if(sock < 0){
        error("socket");
        
    }
    
        
        
    server.sin_family = AF_INET;
    hp = gethostbyname(nos[readParams->no-1].ip); //Localhost
    
    if(hp == 0){
        error("Uknown host");
        
    }
        
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    server.sin_port = htons(nos[readParams->no-1].porta); //5000
    length=sizeof(struct sockaddr_in);
    
    //TESTA MTU
    
    bzero(buffer, 256);
    fgets(buffer,255,stdin);
    
    //scanf("%d",&teste);
    //Passando para a struct
    strcpy(data_env.buffer,readParams->data);
    data_env.tam_buffer = readParams->tam;
    data_env.no_envio = readParams->no;
    
    
    //CHECKSUM
    
        
    //Garbler
        
    set_garbler(0, 0, 0);
        
    n=sendto_garbled(sock,&data_env,strlen(buffer),0,&server,length);
    
    if(n < 0 ){
        error("Sendto");
        
    }
        
        printf("Datagrama Enviado\n");
    //RECEBE GOT YOUR MESSAGE
    /*n=recvfrom(sock,buffer,256,0,&from,&length);

    if(n < 0){
        error("recvfrom");
    }
    
        write(1,"\nGot an ack: ",14);
        write(1,buffer,n);*/
    }
    else{
        
        fprintf(stdout,"\nNós não são vizinhos\n");
        
    }
    
    pthread_mutex_unlock(&env1);
    
}




//Cria a thread Cons_Enlace
int enviaEnlace(int no, char datagrama[], int tamanho){


  //dispara uma thrread que envia para um nó. da thread crriada em inicia enlace
    
    pthread_t t1;
    struct threadsParam readParams;
    
    //printf("CHEGOU o %s",datagrama);
    
    
    readParams.no = no;
    strcpy(readParams.data,datagrama);
    readParams.tam = tamanho;
    
    pthread_create(&t1, NULL, Cons_enlace, (void *)(&readParams));
    pthread_join(t1, NULL);
    //printf("No : %d Datagrama : %s Tamanho : %d\n\n", no, datagrama, tamanho);
    
   
    printf("\n\n");
	return 0;
}


//Cria a thread Prod_Enlace
int recebeEnlace(){
    
    //dispara thread recv
    
    pthread_t t2;
    
    int a2 = 2;
    printf("recebe\n\n");
    
    pthread_create(&t2, NULL, Prod_enlace, (void *)(&a2));
    
    //pthread_join(t2, NULL);
    return 0;   
}




//Funções Auxiliares 


void print_matriz(int lin, int col){

     int x,y;
    
    for(x=0;x<lin;x++)
    {
        for(y=0;y<col;y++)
        {
            printf("%d ", matriz[x][y]);
        }

        printf("\n");
    }


}

void print_mtu(int lin, int col){
    int x,y;

  for(x=0;x<lin;x++)
    {
        for(y=0;y<col;y++)
        {
            printf("%d ", mtu[x][y]);
        }

        printf("\n");
    }

}

int tem_ligacao(int no1,int no2){

    if(matriz[no1-1][no2-1])
      return 1;
    return 0;

}

int getMtu(int no1, int no2){

    if(!tem_ligacao(no1,no2))
      return 0;
    return mtu[no1-1][no2-1];

}

