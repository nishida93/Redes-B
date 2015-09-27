


#include "headers/rede.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

void *iniciaRede(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr,tet,trt;
    pthread_t te_rede, tr_rede, te_tabela_rotas,tr_tabela_rotas;

    
    
    criarTabelaDeRotas();

    te = pthread_create(&te_rede, NULL, envia_DatagramaRede, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    tr = pthread_create(&tr_rede, NULL,recebe_DatagramaRede, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }
    
    tet = pthread_create(&te_tabela_rotas, NULL,envia_Tabela, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    trt = pthread_create(&tr_tabela_rotas, NULL,recebe_Tabela, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }

    
    //Aguarda o termino das threads
    
    pthread_join(te_rede, NULL);
    
    pthread_join(tr_rede, NULL);
    
    pthread_join(te_tabela_rotas,NULL);
    
    pthread_join(tr_tabela_rotas, NULL);
    
    
    



}

///Produtor e Consumidor


//Envia Datagrama
void *envia_DatagramaRede()
{    
    
    
    
}


//Recebe Datagrama
void *recebe_DatagramaRede()
{
    
     

        
        
}



void *enviaTabela(){
    
}

void *recebeTabela(){
    
    
        recebeTabelaDosNos();
       
        //pthread_mutex_lock(&mutex_rede_rede_atualizei1);

        atualizaTabela();

        //pthread_mutex_unlock(&mutex_rede_rede_atualizei2);
    
}

void atualizaTabela(){
    
   /* int i;

    /* Salva quem enviou para não enviar para esse nó*/
    /*tabela_rotas[1].quem_enviou = datagram.num_no;

    printf("Recebi tabela de rotas do nó '%d'\n", tabela_rotas[1].quem_enviou);

    for (i = 0; i < 6; i++) {

        /* Se nó destino -1 */
        /*if (tabela_rotas[i].destino == -1 && datagram.data.tabela_rotas[i].destino != -1)
        {
            tabela_rotas[i].destino = datagram.data.tabela_rotas[i].destino;
            tabela_rotas[i].custo = datagram.data.tabela_rotas[i].custo + 1;
            tabela_rotas[i].saida = datagram.num_no;
        }

        /* atualiza custos */
        /*if (tabela_rotas[i].custo + 1 > datagram.data.tabela_rotas[i].custo) {
            tabela_rotas[i].custo = datagram.data.tabela_rotas[i].custo + 1;
            tabela_rotas[i].saida = datagram.num_no;
        }
    }*/
    
}

void criarTabelaDeRotas(){
    
    int i,j;
    
  printf("\n");
  print_matriz(4,4);
  printf("\n");
  print_mtu(4,4);
  printf("\n");
    
    for(i = 0; i < 6; i++){
        tabela_rotas[i].no_atual = i + 1;
        
    }
    
    
    for(i = 0; i < 6;i++){
     
        
     if(tem_ligacao(no_inicio,i+1)){
        tabela_rotas[i].destino = i+1;
        tabela_rotas[i].custo = 1;
         
    }
    
    if(!tem_ligacao(no_inicio,i+1)){   
        printf("\nI + 1 = %d ", i+1);
        tabela_rotas[i].destino = -1; 
        tabela_rotas[i].custo = -1;
    }
        
    if(no_inicio == i + 1){
      tabela_rotas[no_inicio-1].destino = no_inicio;  
       tabela_rotas[no_inicio-1].custo = 0; 
     }
    
    
}


    printf("Tem Ligacao:%d",tem_ligacao(no_inicio,2));
    
    for(i = 0; i < 6 ; i++){
        
    
     printf("\n%d",tabela_rotas[i].no_atual);  
     printf("\n%d",tabela_rotas[i].destino);
     printf("\n%d\n",tabela_rotas[i].custo);
    
    }
}


void enviaTabelaParaOsNosVizinhos(){
    int teste;
    
  
    int i=0;  
    while(1){
    
    int sock,length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *hp;
    int mtu;
      
    if(i == 6){
        
     sleep(10);
     i=0;
    }
        
    i++;
        
   // pthread_mutex_lock(&env2);

    sock = socket(AF_INET, SOCK_DGRAM,0);
    
       
        
    if(tem_ligacao(no_inicio,i)){
    
        
    mtu = getMtu(no_inicio,i);
        
        
        
    if(sock < 0){
        error("socket");
        
    }
    
    //Limpa Buffer
        

        
    server.sin_family = AF_INET;
    hp = gethostbyname(nos[i-1].ip); //Localhost
    
    if(hp == 0){
        error("Uknown host");
        
    }
       
     
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    server.sin_port = htons(nos[i-1].porta); //5000
    length=sizeof(struct sockaddr_in);
    
    
    
    set_garbler(0, 0, 0);
        
    printf("\nEnviando: Tabela de Rotas:: %s\n");
    
    n=sendto_garbled(sock,&tabela_rotas,sizeof(tabela_rotas),0,(struct sockaddr *)&server,length);
    
    if(n < 0 ){
       // error("Sendto_garbled");
        
    }
        
        
    printf("Tabela Enviada para o nó:%d\n",i);
        
    }
   
   
    
        
    }   
    
    
}


void recebeTabelaDosNos(){
 
    
    
    int sock,length,fromlen, n;
    
    struct tabela_rotas rotas[6];
    
    struct sockaddr_in server;
    struct sockaddr_in from;
    int i=0;
    
    


      
    if(i == 6){
        
     sleep(10);
     i=0;
    }
        
    i++;
        
   // pthread_mutex_lock(&env2);

    sock = socket(AF_INET, SOCK_DGRAM,0);
    
       
        
    if(tem_ligacao(no_inicio,i)){
        
        
    if(sock < 0){
        error("Opening socket");
    }

    length = sizeof(server);
    
    bzero(&server, length);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(nos[i-1].ip);
    server.sin_port = htons(nos[i-1].porta);
    
    if(bind(sock,(struct sockaddr *)&server,length) < 0){
        error("binding");
    }
    
    
    
    while(1){
      
        //Mutex
        pthread_mutex_lock(&rcv1);
        fromlen = sizeof(struct sockaddr_in);
         
       fprintf(stdout,"\nAguardando tabela de rotas\n");
       
        n = recvfrom(sock,&rotas, sizeof(tabela_rotas),0,(struct sockaddr *)&from,&fromlen);
        
        if(n < 0){
         error("recvfrom");   
        }
        
        fprintf(stdout,"\nRecebi tabela de rotas\n");
        
        for(i = 0; i < 6 ; i++){
        
    
         printf("\n%d",rotas[i].no_atual);  
         printf("\n%d",rotas[i].destino);
         printf("\n%d\n",rotas[i].custo);
    
        }
      
        
        
    }
    
    
    
}

    
}


void error(char *msg){
 perror(msg);
    
 exit(0);
    
}




