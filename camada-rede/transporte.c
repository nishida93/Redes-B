


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
    
    
    int retorno_trans;
	struct datagrama aux;
	aux.no_inicio = no_inicio;
    
    while (1) {
   
    //Mutex
        
    
        
    int no=10;
    char *datagrama;
    
    
    
    printf("Deseja enviar para qual nó?\n");
    scanf("%d", &aux.no_envio); 
    
    printf("Escreva uma mensagem para enviar:\n");
    scanf("%s",aux.buffer);
    
        aux.tam_buffer = strlen(aux.buffer);
        //pthread_mutex_lock(&mutex_trns_rd_prod);	//Fecha produtor Transporte->Rede
		pthread_mutex_lock(&trans_rede_env2);	//Fecha produtor Transporte->Rede
        
		buffer_rede_trans_env.no_inicio = aux.no_inicio;
		buffer_rede_trans_env.no_envio = aux.no_envio;
		buffer_rede_trans_env.tam_buffer = aux.tam_buffer;
		memcpy(buffer_rede_trans_env.buffer, aux.buffer, aux.tam_buffer);
        
		//pthread_mutex_unlock(&mutex_trns_rd_cons);
        pthread_mutex_unlock(&trans_rede_rcv2);//Abre consumidor Transporte->Rede
		//verificar retorno
		//pthread_mutex_lock(&mutex_retorno_rede_cons);
        pthread_mutex_unlock(&controle_rede_rcv);
		retorno_trans = retorno_rede;
        
		//pthread_mutex_unlock(&mutex_retorno_rede_prod);
        pthread_mutex_unlock(&controle_rede_env);
		if(retorno_trans == 1) printf("Teste: Rede respondeu que nao sabe caminho\n");
    
    
     
   
    }
}


//Recebe Datagrama
void *cons_Transporte()
{
    
    struct datagrama aux;
    
     while (1) {

         
        // pthread_mutex_lock(&mutex_rd_trns_cons);	
         pthread_mutex_lock(&trans_rede_rcv1);//Fecha consumidor Rede->Transporte
		aux.no_inicio = buffer_rede_trans_rcv.no_inicio;
		aux.no_envio = buffer_rede_trans_rcv.no_envio;
		aux.tam_buffer = buffer_rede_trans_rcv.tam_buffer;
         
		memcpy(aux.buffer, buffer_rede_trans_rcv.buffer, buffer_rede_trans_rcv.tam_buffer);
        aux.buffer[buffer_rede_trans_rcv.tam_buffer]='\0';
         
		//pthread_mutex_unlock(&mutex_rd_trns_prod);
        pthread_mutex_unlock(&trans_rede_env1);//Abre produtor Rede->Transporte
		printf("\n\nTeste-> Tam_buffer: %d Bytes, Buffer: %s\n", aux.tam_buffer, aux.buffer);
        
        

        /*if (data_rcv.tam_buffer != 0) {

        
        data_rcv.tam_buffer = 0;
        data_rcv.no_envio = 0;
        pthread_mutex_unlock(&trans_rede_rcv1);

       }*/
       
        
    }
        
        
}













