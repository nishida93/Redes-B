


#include "headers/rede.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()

void *iniciaRede(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr,tet,trt, trs,tes;
    pthread_t te_rede, tr_rede, te_tabela_rotas,tr_tabela_rotas,tr_segmento,te_segmento;

    criarTabelaDeRotas();
    
    
    trs = pthread_create(&tr_segmento, NULL, recebe_Segmento, NULL);

    if (trs) {
        printf("ERRO: impossivel criar a thread : receberSegmento\n");
        exit(-1);
    }
    
    
    tr = pthread_create(&tr_rede, NULL,recebe_DatagramaRede, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }

    trt = pthread_create(&tr_tabela_rotas, NULL,recebe_Tabela, NULL);

    if (tr) {
        printf("ERRO: impossivel criar a thread : receberDatagramas\n");
        exit(-1);
    }
    
    
    
    tes = pthread_create(&te_segmento, NULL, envia_Segmento, NULL);

    if (tes) {
        printf("ERRO: impossivel criar a thread : enviarSegmento\n");
        exit(-1);
    }
    
    te = pthread_create(&te_rede, NULL, envia_DatagramaRede, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    
    
    tet = pthread_create(&te_tabela_rotas, NULL,envia_Tabela, NULL);

    if (te) {
        printf("ERRO: impossivel criar a thread");
        exit(-1);
    }

    
    

    
    

    
    //Aguarda o termino das threads
    
    pthread_join(te_rede, NULL);
    
    pthread_join(tr_rede, NULL);
    
    pthread_join(te_tabela_rotas,NULL);
    
    pthread_join(tr_tabela_rotas, NULL);
    
    
    


}

void *recebe_Segmento() {

    while (1) {

        //struct datagrama datagrama_env;

        /* Consumir buffer_trans_rede_env */
       
        pthread_mutex_lock(&trans_rede_env2);

        //retirarSegmentoBufferTransRedeEnv(&datagrama_env);
        //printf("data_env ::%s",data_env.buffer);
        /* Consumir buffer_trans_rede_env */
        pthread_mutex_unlock(&trans_rede_env1);

        /* Produzir buffer_rede_rede_env */
        pthread_mutex_lock(&rede_env1);

      //  colocarDatagramaBufferRedeRedeEnv(datagrama_env);

        /* Produzir buffer_rede_rede_env */
        pthread_mutex_unlock(&rede_env2);
    }
}

///Produtor e Consumidor
void *envia_Segmento() {
    
    while (1) {

        //struct datagrama datagrama_rcv;

        /* Consumir buffer_rede_rede_rcv */
        pthread_mutex_lock(&rede_rcv2);

        //retirarDatagramaBufferRedeRedeRcv(&datagrama_rcv);

        /* Consumir buffer_rede_rede_rcv */
        pthread_mutex_unlock(&rede_rcv1);

        /* Produzir buffer_trans_rede_rcv */
        pthread_mutex_lock(&trans_rede_rcv1);

        //colocarDatagramaBufferTransRedeRcv(datagrama_rcv);

        /* Produzir buffer_trans_rede_rcv */
        pthread_mutex_unlock(&trans_rede_rcv2);

    }
}


//Envia Datagrama
void *envia_DatagramaRede()
{    
    
    
    while(1){
        
    //pthread_mutex_lock(&rede_env2);
        
        
/////teste
    pthread_mutex_lock(&rede_env2);
    
      //  retira
        
    pthread_mutex_unlock(&rede_env1);    
        
        
    pthread_mutex_unlock(&rede_enlace_env1);

    //colocarDatagramaBufferRedeEnlaceEnv(datagrama_env);

        /* Produzir buffer_rede_enlace_env */
    //printf("desbloqueando");
    pthread_mutex_unlock(&rede_enlace_env2);//enlace.c -->lock

        /* Consome resposta da camada de enlace */
    //pthread_mutex_lock(&rede_enlace_env1);//enlace --> unlock
      
    pthread_mutex_lock(&rede_enlace_env1);
        
        //retorno enlace
        
    pthread_mutex_unlock(&rede_enlace_env1);
        
    }
}


//Recebe Datagrama
void *recebe_DatagramaRede()
{
    
     int i = 0;
    int index;

    while (1) {

       // struct datagrama datagrama_rcv;

        /* Consumir buffer_rede_enlace_rcv */
        pthread_mutex_lock(&rede_enlace_rcv2);

        /* Retira datagrama do buffer */
        //retirarDatagramaBufferRedeEnlaceRcv(&datagrama_rcv);

        /* Consumir buffer_rede_enlace_rcv */
        pthread_mutex_unlock(&rede_enlace_rcv1);

        /* Datagrama é para mim? */
        if (data_rcv.no_envio == no_inicio) {

           
                    pthread_mutex_lock(&rede_rcv1);

                    /* É um datagrama unico? */
                   

                       // colocarDatagramaBufferRedeRedeRcv(buffers_fragmentacao[index]);
                        //resetarBuffer(&buffers_fragmentacao[index]);
                    

                    /* Produzir buffer_rede_rede_rcv */
                    pthread_mutex_unlock(&rede_rcv2);
                

                /* É um datagrama de roteamento? */
          

                /* Produzir buffer_rede_rede_rcv */
               // pthread_mutex_lock(&mutex_rede_rede_rcv1);

               // colocarDatagramaBufferRedeRedeRcv(datagrama_rcv);

                /* Produzir buffer_rede_rede_rcv */
                //pthread_mutex_unlock(&mutex_rede_rede_receberotas2);

            
        }// Datagrama não é para mim, repassar datagrama
        else {

            /* Produzir buffer_rede_rede_env */
            pthread_mutex_lock(&rede_env1);

            //printf("Repassando datagrama ao nó '%d'!\n", datagrama_rcv.env_no);

           // colocarDatagramaBufferRedeRedeEnv(datagrama_rcv);

            /* Produzir buffer_rede_rede_env */
            
            pthread_mutex_unlock(&rede_env2);
        }
    }

      
        
}



void *envia_Tabela(){
    
    
    enviaTabelaParaOsNosVizinhos(); 
    while(1){
        
        
        pthread_mutex_lock(&rede_atualiza2);

        //montarDatagramaTabelaRotas(&datagrama_env); //talvez seja necessario

        pthread_mutex_unlock(&rede_atualiza1);

        enviaTabelaParaOsNosVizinhos(); 
        
        
        
    }
}


void enviaTabelaParaOsNosVizinhos(){
    int teste;
    int i=0;  
    int sock,length, n;
    int mtu;
      
   for (i = 0; i < 6; i++) {
   // pthread_mutex_lock(&env2);

    if(tem_ligacao(no_inicio,i)){
    
    pthread_mutex_lock(&rede_env1);   
    
    mtu = getMtu(no_inicio,i);
            
            memcpy(&(data_env.dados.tabela_rotas), &tabela_rotas, sizeof (tabela_rotas));

            /* Seta variaveis para envio */
            data_env.no_envio = i;
            //data_env.num_no = no_inicio;

            printf("Rede : Enviei Tabela de Rotas para o nó '%d'\n", i);

            //colocarDatagramaBufferRedeRedeEnv(*datagram);
            pthread_mutex_lock(&buffer_rede_env);

            memcpy(&buffer_env, &data_env, sizeof (data_env));

        /* Unlock buffer_rede_env acesso exclusivo */
            pthread_mutex_unlock(&buffer_rede_env);
    //Limpa Buffer
    //server.sin_port = htons(nos[i-1].porta); //5000
    
    //printf("Tabela Enviada para o nó:%d\n",i);
    
    pthread_mutex_unlock(&rede_env2);
    
    }
   }
}

void *recebe_Tabela(){
    
        printf("Thread recebeTabela criada\n");
    
    
    
        
    
        while(1){

        /* Consumir buffer_rede_rede_rcv */
        pthread_mutex_lock(&rcv_tabela2);

        /* Lock buffer_rede_rcv acesso exclusivo */
        pthread_mutex_lock(&buffer_rede_rcv);

        memcpy(&data_rcv, &buffer_rcv, sizeof (buffer_rcv));

        /* Unlock buffer_rede_rcv acesso exclusivo */
        pthread_mutex_unlock(&buffer_rede_rcv);

        /* Consumir buffer_rede_rede_rcv */
        pthread_mutex_unlock(&rede_rcv1);

        /* Travar e Desbloquear a threadEnviarTabelaRotas */
        pthread_mutex_lock(&rede_atualiza1);

        //atualizarTabelaRotas(datagrama_rcv);
        atualizaTabela();
        pthread_mutex_unlock(&rede_atualiza2);
       
        //pthread_mutex_lock(&mutex_rede_rede_atualizei1);
       
        //pthread_mutex_unlock(&mutex_rede_rede_atualizei2);
        }
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








        /*for(i = 0; i < 6 ; i++){
        
    
         printf("\n%d",data_rcv.dados.tabela_rotas[i].no_atual);  
         printf("\n%d",data_rcv.dados.tabela_rotas[i].destino);
         printf("\n%d\n",data_rcv.dados.tabela_rotas[i].custo);
    
        }*/
      
  

void criarTabelaDeRotas(){
    
    int i,j;
    
 /* printf("\n");
  print_matriz(4,4);
  printf("\n");
  print_mtu(4,4);
  printf("\n");*/
    
    for(i = 0; i < 6; i++){
        tabela_rotas[i].no_atual = i + 1;
        
    }
    
    
    for(i = 0; i < 6;i++){
     
        
     if(tem_ligacao(no_inicio,i+1)){
        tabela_rotas[i].destino = i+1;
        tabela_rotas[i].custo = 1;
         
    }
    
    if(!tem_ligacao(no_inicio,i+1)){   
        //printf("\nI + 1 = %d ", i+1);
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
        
    
     //printf("\n%d",tabela_rotas[i].no_atual);  
     //printf("\n%d",tabela_rotas[i].destino);
     //printf("\n%d\n",tabela_rotas[i].custo);
    
    }
}







