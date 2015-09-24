


#include "headers/enlace.h"

////Constantes

#define SIZE 1024


/*
 * Cliente UDP
 */



//nos[0] guarda as informacoes do no 1.
//nos[1] guarda as informacoes do no 2.
//etc..
 
int checkSum(void *);



int checksum; 

int no_do_enlace; // Numero do nó iniciado;

void iniciaEnlace(){

  no_do_enlace = info.no_de_inicio;
 

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

    printf("\n%s\n",info.arg);
  arq = fopen(info.arg, "r");
    
    
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
                
            
             node++;
            }
          }
        }while(ret >= 6);

        ret=3;
        fscanf(arq,"%s",str);

        do{
            ret = fscanf(arq,"%d -> %d, MTU = %d;", &number,&elem1,&elem2);
            
            if(ret >= 3){
             
              matriz[number-1][elem1-1]=1;
              matriz[elem1-1][number-1]=1;
              mtu[number-1][elem1-1]=elem2;
              mtu[elem1-1][number-1]=elem2;
            }
          }while(ret >= 3);

        
        
  

        
}


//Testando funcoes

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
    
    
  
  
  iniciaThreads();
 
}


//Threads Produtor e Consumidor  -------------

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
    char aux[1024];
   
    
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
    
    
    
    while(1){
      
        //Mutex
         pthread_mutex_lock(&rcv1);
         fromlen = sizeof(struct sockaddr_in);
         
        printf("\nSize:%d\n",sizeof(data_rcv));
       
        n = recvfrom(sock,&data_rcv, sizeof(data_rcv),0,(struct sockaddr *)&from,&fromlen);
        
        if(n < 0){
         error("recvfrom");   
        }
        
        write(1,"Datagrama Recebido: ",20);
        
        //write(1, data_rcv.buffer, n);
        
        printf("DATA: %s\n\n", data_rcv.buffer);
        
       /* n = recvfrom(sock,aux,1024,0,(struct sockaddr *)&from,&fromlen);
        
        if(n < 0){
         error("recvfrom");   
        }*/
        
        
        printf("DATA 2: %d\n\n", data_rcv.tam_buffer);
        printf("DATA 2: %d\n\n", data_rcv.checksum);
        //int  no_envio;
        //checksum = atoi(aux);
        
        
        
        
       // strcpy(data_rcv.buffer,"");
        //strcpy(data_rcv.buffer,buf);///<---------------------------Atribui valores para a struct de recebimento
       // data_rcv.tam_buffer = strlen(buf);
        //data_rcv.no_envio = no_do_enlace;
        
        printf("DATA 3: %d\n\n", data_rcv.no_envio);
        //RECALCULA CHECKSUM
        int checksum2 = data_rcv.checksum;
        
        printf("\nTam Buffer:%d",data_rcv.tam_buffer);
        printf("\nNo de Envio:%d",data_rcv.no_envio);
        printf("\nBuffer:%s",data_rcv.buffer);
        printf("\nChecksum:%d\n",data_rcv.checksum);
        printf("\nChecksum:%d\n",sizeof(data_rcv));
        int check = checkSum(&data_rcv.buffer);

        printf("\nCheck %d:::::%d::::::%d",check, data_rcv.checksum, checksum2);

        
        
        if (data_rcv.checksum == check){
            printf("Datagrama sem erro\n");
        }
        else {
            printf("Datagrama com erro\n");
        
        }
        
        
        printf("Buffer:::%s",data_rcv.buffer);
        
   
        
        
         pthread_mutex_unlock(&rcv2);
        
    }
    
 
   
}

//Envia Datagrama
void *Cons_enlace(void *thread){
    int id=*(int *)thread;
 

    
    int teste;
    
    //printf("\n%d ::: %s\n",data_env->no, data_env->data);
    while(1){
    
    int sock,length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *hp;
    
    int mtu=0;
    
    
    char buffer[1024];
    char check_aux[1024];
        
    pthread_mutex_lock(&env2);

    sock = socket(AF_INET, SOCK_DGRAM,0);
    
    if(data_env.tam_buffer != 0){    
        
    if(tem_ligacao(no_do_enlace,data_env.no_envio)){
    
        
        mtu = getMtu(no_do_enlace,data_env.no_envio);
        
        //printf("ENVIA::::IP:::::%s PORTA::::%d",nos[data_env.no_envio-1].ip,nos[data_env.no_envio-1].porta);
        //printf("Mtu:::%d\n\n",mtu);
        
    if(sock < 0){
        error("socket");
        
    }
    
    //Limpa Buffer
        
    strcpy(buffer,"");
        
    server.sin_family = AF_INET;
    hp = gethostbyname(nos[data_env.no_envio-1].ip); //Localhost
    
    if(hp == 0){
        error("Uknown host");
        
    }
       
     
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    server.sin_port = htons(nos[data_env.no_envio-1].porta); //5000
    length=sizeof(struct sockaddr_in);
    
    
    
    bzero(buffer, 1024);
    fgets(buffer,1024,stdin);
    
    
    strcpy(buffer,data_env.buffer);    
    
    //TESTA MTU
    
    if(strlen(data_env.buffer) > mtu){
        error("MTU Error-> Nao foi possivel enviar o pacote");
        
        
    }
        
    //CHECKSUM
        
    data_env.tam_buffer = strlen(data_env.buffer);
        
    
    checksum = checkSum(4);
    printf("check::: %d\n\n",checksum);
        

    sprintf(check_aux,"%d",checksum);   
    
    data_env.checksum = checksum;
    //Garbler
        
    printf("Tam Buffer:%d\n",data_env.tam_buffer);
    printf("No de Envio:%d\n",data_env.no_envio);
    printf("Buffer:%s\n",data_env.buffer);
    printf("Checksum:%d\n",data_env.checksum);
    printf("sizeof:%d\n",sizeof(data_env));
           
           

    set_garbler(0, 0, 0);
        
        
    
    n=sendto_garbled(sock,&data_env,sizeof(data_env),0,(struct sockaddr *)&server,length);
    
    if(n < 0 ){
        error("Sendto_garbled");
        
    }
        
        
        
        
        
        /*sleep(10);
        
        n=sendto_garbled(sock,check_aux,strlen(check_aux),0,&server,length);
    
    if(n < 0 ){
        error("Sendto");
        
    }*/
      
         printf("Datagrama Enviado\n");
        
    }
    else{
        
        fprintf(stdout,"\nNós não são vizinhos\n");
        
    }
   
    pthread_mutex_unlock(&env1);
        
    }
 }//Fecha While
}




int iniciaThreads(){

    pthread_t t1;
    
    int a1 = 1;

    
    
    //Recebe
    
    
    pthread_create(&t1, NULL, Prod_enlace, (void *)(&a1));
    
    pthread_t t2;
    
    int a2 = 2;
    //Envia
    pthread_create(&t2, NULL, Cons_enlace, (void *)(&a2));
    
    

    
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
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

int checkSum(void *sum)
 {
     int i;
     int check=0;
     unsigned char *data;
 
     data = sum;
     
     data += 2;    
 
   
     for (i=2; i < sizeof(struct datagrama); i++) {
         check += *data++;
         printf("Check:::IIII::%d::%d\n\n",i,check);
     }
     return check;
 } 