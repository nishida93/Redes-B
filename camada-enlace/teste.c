


#include "headers/teste.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

int iniciaTeste(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr;
    pthread_t te_teste, tr_teste;

    
    
   

    te = pthread_create(&te_teste, NULL, Prod_teste, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    tr = pthread_create(&tr_teste, NULL,Cons_teste, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }

    
    //Aguarda o termino das threads
    
    pthread_join(te_teste, NULL);
    
    pthread_join(tr_teste, NULL);
    
    
    
    

	return 0;

}

///Produtor e Consumidor


//Envia Datagrama
void *Prod_teste()
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

    
    data_env.tam_buffer = strlen(data_env.buffer);
    data_env.no_envio = no;
    
    //Chama envia enlace;
    
        
    pthread_mutex_unlock(&env2);
    //pthread_mutex_unlock(&env1);
    }
}


//Recebe Datagrama
void *Cons_teste()
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













