#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



/*
 * Cliente UDP
 */
/*int main( int argc,char *argv[])
{
    int i;

    for(i=0; i < argc; i++){
      printf("argv[%d] = %s\n", i , argv[i]);

    }

    
    
    return 0;
}*/
//Carregar arq de config
//Escutar na porta





int iniciaEnlace(int no){

	//Se o pacote maior que MTU retorna erro  ... MTU: quanto a camada de cima pode enviar.

	//Nao deve fragmentar

	//Se tiver menor processa


	//Verifica se o no é vizinho, se nao for, retorn mensagem pra camada de cima

	//Apenas verifica se o pacote esta certo, caso contrario joga fora, camada de transporte que deve se preucupar com isso


	//dispara THREADS de envio e recebimento 

	//Carrega arquivo de  Configuracao.

 printf("No do enlace: %d\n\n", no);
	
  /*int i,count;
  
  int ids_barbers[NUM_CLIENTS];
  int ids_clients[NUM_CLIENTS];
  int tb,tc;
   
  pthread_mutex_init(&exc_aces,NULL);
 
  for(count=0;count < NUM_OF_CHINDREN;count++)
  {
    
    
    if(count < NUM_BARBERS){
      
     ids_barbers[count]=count;
    
     tb=pthread_create(&barbeiros[count],NULL,barbeiro,(void*)&ids_barbers[count]); 
 
        if(tb){
          fprintf(stderr,"ERRO!Thread Barbeiro não criada");
          exit(-1);
        }
    
    }
    
    if(count < NUM_CLIENTS){
      
    ids_clients[count]=count;
    
    tc=pthread_create(&clientes[count],NULL,cliente,(void *)&ids_clients[count]); 
    
      	if(tc){
      	fprintf(stderr,"ERRO!Thread Cliente não criada");
      	 exit(-1);
        }
    }
    else{
    //  printf("contC=%d\n",contC);
      break;//pthread_join(clientes[count],NULL);
    }
    //Inicia a thread que escuta a porta e quando recebe ela abre outra que faz a conta de verificacao e envia para teste.c


  }
  //////////////////////////////////////////////////////////////////////////////Em cima esta a criação.
   
 for(i=0;i < NUM_CLIENTS;i++){
      
    //pthread_join(clientes[count],NULL);
     pthread_join(clientes[i],NULL);
  } 
 
 for(i=0;i < NUM_BARBERS;i++){
    tb=pthread_kill(barbeiros[i],0);
    
    
 
    if(tb){
      fprintf(stderr,"ERRO!Thread Barbeiro não finalizada");
      exit(-1);
    }
  
  }

  
  pthread_mutex_destroy(&exc_aces);
  

  exit(1);
  
  
//QUando a thread crianda aqui reecebe de thread de enviaenlace, cria-se outra thread que faz o calculo de verificacao e envia para a camada de teste.
*/


    return 0;
}


int enviaEnlace(int No, char datagrama[], int tamanho){


  //dispara uma thrread que envia para um nó. da thread crriada em inicia enlace
	return 0;
}