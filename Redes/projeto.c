



#include "headers/projeto.h"



/*
 * Cliente UDP
 */
int main(int argc, char *argv[])
{

    
    if (argc != 3) {
        printf("Entry: %s fileName.conf Numero_No\n", argv[0]);
        exit(1);
    }
    
    
    printf("NOME DO ARQUIVO :::::%s",argv[1]);
    int no_inicio =0;
    
    no_inicio = atoi(argv[2]);
    
    
    
    while(no_inicio > 4 || no_inicio < 1){
        
     printf("Inicie um nó de 1 a 4\nNó:");
     scanf("%d", &no_inicio);
    }
    
    //Inicia os Mutexes
    
    if (pthread_mutex_init(&env1, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&env2, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&rcv1, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&rcv2, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
    }
    
    
    iniciaEnlace(no_inicio, argv[1]);
    iniciaTeste();

    


	//Compilar o negocio estranho, fundi teste e enlace
	return 0;
}



