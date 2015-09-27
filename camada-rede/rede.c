


#include "headers/rede.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

void iniciaRede(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr,tet,trt;
    pthread_t te_rede, tr_rede, te_tabela_rotas,tr_tabela_rotas;

    
    
    criarTabelaDeRotas();

    te = pthread_create(&te_rede, NULL, prod_Rede, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    tr = pthread_create(&tr_rede, NULL,cons_Rede, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }
    
    tet = pthread_create(&te_tabela_rotas, NULL, enviaTabela, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    trt = pthread_create(&tr_tabela_rotas, NULL,recebeTabela, NULL);

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
void *prod_Rede()
{    
    
    
    while (1) {
   
    //Mutex
        
    pthread_mutex_lock(&env_tabela1);
        
    int no=10;
    char *datagrama;
    
    
    
    printf("Deseja enviar para qual nó?\n");
    scanf("%d", &no); 
    
    printf("Escreva uma mensagem para enviar:\n");
  
   
    
    strcpy(data_env.buffer,"");
    scanf("%s",data_env.buffer);

    printf("Matriz:%d\n",matriz[1][1]);
    data_env.tam_buffer = strlen(data_env.buffer);
    data_env.no_envio = no;
    
    //Chama envia enlace;
    
        
    pthread_mutex_unlock(&env_tabela2);
    //pthread_mutex_unlock(&env1);
    }
}


//Recebe Datagrama
void *cons_Rede()
{
    
     while (1) {

        //Trava mutex de sincronismo
        pthread_mutex_lock(&rcv2);

        

        if (data_rcv.tam_buffer != 0) {

        printf("\n\nTeste-> Tam_buffer: %d Bytes, Buffer: %s\n", data_rcv.tam_buffer, data_rcv.buffer);
        
        pthread_mutex_unlock(&rcv1);

       }
       
        
    }
        
        
}

void *enviaTabela(){
    
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
    server.sin_port = htons(nos[data_env.no_envio-1].porta); //5000
    length=sizeof(struct sockaddr_in);
    
    
    
    set_garbler(0, 0, 0);
        
        printf("\nEnviando::: %s\n");
    
    n=sendto_garbled(sock,&tabela_rotas,sizeof(tabela_rotas),0,(struct sockaddr *)&server,length);
    
    if(n < 0 ){
       // error("Sendto_garbled");
        
    }
        
        
    printf("Tabela Enviada para i\n");
        
    }
   
   
    pthread_mutex_unlock(&env1);
        
    }
    
}

void *recebeTabela(){
    
    
}

void *atualizarTabela(){
    
    
    
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











