


#include "headers/rede.h"



char buffer_teste[40];


//Chama a funcao do enlace: enviaEnlace()
int random_id;
void printTabelaRotas();
void *iniciaRede(){

	//Troca de mensagens ou fila, serve para simular a camada de rede.
	
    int te, tr,tet,trt, trs,tes;
    pthread_t te_rede, tr_rede, te_tabela_rotas,tr_tabela_rotas,tr_segmento,te_segmento;
    random_id = 0;
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

void *envia_Tabela(){
    
    
    int i=0;
	int id;

	while(1)
	{
		  i++;
          if(i > 6){
           
            i=0;  
          }
			
			if(tem_ligacao(no_inicio,i))
			{
                
				sleep(5);
                
                pthread_mutex_lock(&controle_randomico);
				id = random_id;
				random_id = (random_id+1)%65535;
				
                pthread_mutex_unlock(&controle_randomico);
                
				
                pthread_mutex_lock(&rede_enlace_env1);
                
				pthread_mutex_lock(&controle_tabela);		
				buffer_rede_enlace_env.no_inicio = no_inicio;
				buffer_rede_enlace_env.no_envio = nos[i-1].no;
				buffer_rede_enlace_env.tam_buffer = sizeof(tabela_rotas);
				buffer_rede_enlace_env.id = id;
				buffer_rede_enlace_env.controle = 0; 
				buffer_rede_enlace_env.no_vizinho = no_inicio;
				buffer_rede_enlace_env.no_prox = nos[i-1].no;
				buffer_rede_enlace_env.offset = 0;
				buffer_rede_enlace_env.frag = sizeof(tabela_rotas);
                
				memcpy(&buffer_rede_enlace_env.dados, tabela_rotas, sizeof(tabela_rotas));
               
				pthread_mutex_unlock(&controle_tabela);		
				
                pthread_mutex_unlock(&rede_enlace_rcv1);
               
			}	
		
	}
}





//Envia Datagrama
void *envia_DatagramaRede()
{    
    
    
    struct datagrama aux; 
	int offset;
    int frag;
	int id;
	int prox_no,j;
	int retorno;
    
    
	while(1)
	{
		
        pthread_mutex_lock(&trans_rede_rcv2);
        
		aux.no_inicio = buffer_rede_trans_rcv.no_inicio;
       
		aux.no_envio = buffer_rede_trans_env.no_envio;
		aux.tam_buffer = buffer_rede_trans_env.tam_buffer;
		memcpy(aux.buffer, buffer_rede_trans_env.buffer, buffer_rede_trans_env.tam_buffer);
		
        pthread_mutex_unlock(&trans_rede_env2);
        
        printf("\n\naux_no_envio: %d %s",aux.no_envio, aux.buffer);
        for(j=0; j<6; j++)
		{
			if(tabela_rotas[j].no_atual == aux.no_envio) break;
		} 
        
        
		prox_no = tabela_rotas[j].destino;

		if(prox_no == -1)
		{
			
            pthread_mutex_lock(&controle_rede_env);
			retorno_rede = 1;
			
            pthread_mutex_unlock(&controle_rede_rcv);
			continue;
		}
        
        
        if (aux.no_inicio == no_inicio){
            
            pthread_mutex_lock(&controle_rede_env);
            retorno_rede = 0;
            
            pthread_mutex_unlock(&controle_rede_rcv);
        }


		offset = 0;
		frag = aux.tam_buffer;

		
		pthread_mutex_lock(&controle_randomico);
		id = random_id;
		random_id = (random_id+1)%65535;
		pthread_mutex_unlock(&controle_randomico);

		do{
			
            pthread_mutex_lock(&rede_enlace_env1);
            
			buffer_rede_enlace_env.no_inicio = aux.no_inicio;
			buffer_rede_enlace_env.no_envio = aux.no_envio;
			buffer_rede_enlace_env.tam_buffer = aux.tam_buffer;
			buffer_rede_enlace_env.id = id;
			buffer_rede_enlace_env.controle = 1;
			buffer_rede_enlace_env.offset = offset;
			buffer_rede_enlace_env.no_vizinho = aux.no_inicio;
			buffer_rede_enlace_env.no_prox = prox_no;
			buffer_rede_enlace_env.frag = frag;
            memcpy(&buffer_rede_enlace_env.buffer, aux.buffer, aux.tam_buffer);
			memcpy(&buffer_rede_enlace_env.dados, aux.buffer+offset, frag);
            
			
            pthread_mutex_unlock(&rede_enlace_rcv1);
			
            pthread_mutex_lock(&controle_rede_enlace_rcv);
			retorno = retorno_enlace;
			
            pthread_mutex_unlock(&controle_rede_enlace_env);
            
            printf("\n\nTamanho do pacote %lu \n\n",(sizeof(buffer_rede_enlace_env)-100+buffer_rede_enlace_env.frag));
            
			if(retorno == 0) offset = offset + frag;
			else
			{
				frag = retorno -(sizeof(buffer_rede_enlace_env) - 100) ;
                printf("Passi por aqui\n");
			}
			
		}while(offset < aux.tam_buffer);
	}

}


//Recebe Datagrama
void *recebe_DatagramaRede()
{
    
    struct datagrama aux;
	struct tabela_de_rotas* table;
	int i;

	while(1)
	{
		
        pthread_mutex_lock(&rede_enlace_rcv2);
        
        
		aux.no_inicio = buffer_rede_enlace_rcv.no_inicio;
		aux.no_envio = buffer_rede_enlace_rcv.no_envio;
		aux.tam_buffer = buffer_rede_enlace_rcv.tam_buffer;
		aux.id = buffer_rede_enlace_rcv.id;
		aux.controle = buffer_rede_enlace_rcv.controle;
		aux.no_vizinho = buffer_rede_enlace_rcv.no_vizinho;
		aux.no_prox = buffer_rede_enlace_rcv.no_prox;
		aux.offset = buffer_rede_enlace_rcv.offset;
		aux.frag = buffer_rede_enlace_rcv.frag;
		memcpy(&aux.dados, &buffer_rede_enlace_rcv.dados, buffer_rede_enlace_env.frag);
        memcpy(&aux.buffer, &buffer_rede_enlace_rcv.buffer, buffer_rede_enlace_rcv.tam_buffer);
        printf("BUFFER:%s\n",aux.buffer);
		
        pthread_mutex_unlock(&rede_enlace_env2);
		
		if(aux.no_envio == no_inicio) 
		{

				if(aux.controle == 0) 
				{
					table = (struct tabela_de_rotas*)&aux.dados;
					pthread_mutex_lock(&controle_tabela);		
					for(i=0; i<6; i++)
					{
						if(table->destino != -1) 
						{
							if(tabela_rotas[i].destino == -1) 
							{
								
								tabela_rotas[i].destino = aux.no_vizinho; 
								tabela_rotas[i].custo = table->custo+1;
							}
							else if(table->custo+1 < tabela_rotas[i].custo)
                            {
									
									tabela_rotas[i].destino = aux.no_vizinho; 
									tabela_rotas[i].custo = table->custo+1;
                            }
								
						}
                        
						table++;
                        
					}
                    
                    
					pthread_mutex_unlock(&controle_tabela);		
				}
				else 
				{
                  
                    
                    pthread_mutex_lock(&trans_rede_env1);
                    
                    
                    buffer_rede_trans_env.no_inicio = aux.no_inicio;
                    buffer_rede_trans_env.no_envio = aux.no_envio;
                    buffer_rede_trans_env.tam_buffer = aux.tam_buffer;
                    
                    memcpy(&buffer_rede_trans_env.buffer,&aux.buffer, buffer_rede_trans_env.tam_buffer);
                    memcpy(&buffer_rede_trans_env.dados,&aux.dados, buffer_rede_enlace_rcv.frag);
                    
                    pthread_mutex_unlock(&trans_rede_rcv1);
				}
		}
		else 
		{      
           
            pthread_mutex_lock(&trans_rede_env2);
            buffer_rede_trans_rcv.no_inicio = aux.no_inicio;
            buffer_rede_trans_rcv.no_envio = aux.no_envio;
            buffer_rede_trans_rcv.tam_buffer = aux.tam_buffer;

            memcpy(buffer_rede_trans_rcv.buffer,&aux.dados,aux.frag);
            
            pthread_mutex_lock(&trans_rede_rcv2);
		}
	}

      
        
}



void *recebe_Segmento() {

   
}

///Produtor e Consumidor
void *envia_Segmento() {
    
    while (1) {

       
    }
}


void enviaTabelaParaOsNosVizinhos(){
    
}

void *recebe_Tabela(){
    
        
    
    
    
        
    
        
}

void atualizaTabela(){
    
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
    
    
        
    printTabelaRotas();

    
}

void printTabelaRotas(){
    
     
        
    
     printf("\n\n%d  %d %d %d %d %d ",tabela_rotas[0].no_atual,tabela_rotas[1].no_atual,tabela_rotas[2].no_atual,tabela_rotas[3].no_atual,tabela_rotas[4].no_atual,tabela_rotas[5].no_atual);  
     printf("\n%d %d %d %d %d %d",tabela_rotas[0].destino,tabela_rotas[1].destino,tabela_rotas[2].destino,tabela_rotas[3].destino,tabela_rotas[4].destino,tabela_rotas[5].destino);
     printf("\n%d %d %d %d %d %d\n",tabela_rotas[0].custo,tabela_rotas[1].custo,tabela_rotas[2].custo,tabela_rotas[3].custo,tabela_rotas[4].custo,tabela_rotas[5].custo);
    
      
    
}







