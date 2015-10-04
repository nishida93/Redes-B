


#include "headers/transporte.h"


char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

int *iniciaTransporte(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr;
    pthread_t te_trans, tr_trans;

    
    
   

    te = pthread_create(&te_trans, NULL, prod_Transporte, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    tr = pthread_create(&tr_trans, NULL,cons_Transporte, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }

    
    //Aguarda o termino das threads
    
    pthread_join(te_trans, NULL);
    
    pthread_join(tr_trans, NULL);
    
    
    
    

	return 0;

}

///Produtor e Consumidor


//Envia Datagrama
void *prod_Transporte()
{    
    
    
    while (1) {
   
    //Mutex
        
    pthread_mutex_lock(&trans_rede_env1);
        
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
    
        
    pthread_mutex_unlock(&trans_rede_env2);
    //pthread_mutex_unlock(&env1);
    }
}


//Recebe Datagrama
void *cons_Transporte()
{
    
     while (1) {

        //Trava mutex de sincronismo
        pthread_mutex_lock(&trans_rede_rcv2);

        

        if (data_rcv.tam_buffer != 0) {

        printf("\n\nTeste-> Tam_buffer: %d Bytes, Buffer: %s\n", data_rcv.tam_buffer, data_rcv.buffer);
        data_rcv.tam_buffer = 0;
        data_rcv.no_envio = 0;
        pthread_mutex_unlock(&trans_rede_rcv1);

       }
       
        
    }
        
        
}













