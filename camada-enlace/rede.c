


#include "headers/rede.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

void iniciaRede(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr,tet,trt;
    pthread_t te_rede, tr_rede, te_tabela_rotas,tr_tabela_rotas;

    
    
   

    te = pthread_create(&te_rede, NULL, Prod_rede, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    tr = pthread_create(&tr_rede, NULL,Cons_rede, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }
    
    tet = pthread_create(&te_tabela_rotas, NULL, Envia_tabela, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    trt = pthread_create(&tr_tabela_rotas, NULL,Recebe_tabela, NULL);

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
void *Prod_rede()
{    
    
    
    while (1) {
   
    //Mutex
        
    pthread_mutex_lock(&env1);
        
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
    
        
    pthread_mutex_unlock(&env2);
    //pthread_mutex_unlock(&env1);
    }
}


//Recebe Datagrama
void *Cons_rede()
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

void *Envia_tabela(){
    
    
    
}

void *Recebe_tabela(){
    
    
}

void *Atualizar_tabela(){
    
    
    
}












