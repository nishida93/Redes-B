#include "headers/projeto.h"




int main(int argc, char *argv[])
{
    int te, tr,tt;
    pthread_t te_iniciaEnlace, tr_iniciaRede, tt_iniciaTransporte;
    
    if (argc != 3) {
        printf("Entry: %s fileName.conf Numero_No\n", argv[0]);
        exit(1);
    }
    
    
    //printf("NOME DO ARQUIVO :::::%s",argv[1]);
    
    
    no_inicio = atoi(argv[2]);
    
    
    
    while(no_inicio > 6 || no_inicio < 1){
        
     printf("Inicie um nó de 1 a 6\nNó:");
     scanf("%d", &no_inicio);
    }
    
    //GetInfo
    
    info.no_de_inicio = no_inicio;
    strcpy(info.arg,argv[1]);
    
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
    
    if(pthread_mutex_init(&env_tabela1, NULL) != 0){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    if(pthread_mutex_init(&env_tabela2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    

    data_env.tam_buffer = 0;
    data_env.no_envio = 0;

    data_rcv.tam_buffer = 0;
    data_rcv.no_envio = 0;
    
    
    
    te = pthread_create(&te_iniciaEnlace, NULL, iniciaEnlace, NULL);

    if (te) {
        printf("error: impossivel criar a thread do enlace\n");
        exit(-1);
    }
    
    sleep(1);
    
    tr = pthread_create(&tr_iniciaRede, NULL, iniciaRede , NULL);

    if (tt) {
        printf("error: impossivel criar a thread do teste \n");
        exit(-1);
    }
    
    sleep(1);
    
    tt = pthread_create(&tt_iniciaTransporte, NULL, iniciaTransporte , NULL);

    if (tt) {
        printf("error: impossivel criar a thread do teste \n");
        exit(-1);
    }
    
    
    

  

    
    

    //Espera as threads terminarem
    pthread_join(te_iniciaEnlace, NULL);
    pthread_join(tr_iniciaRede, NULL);
    pthread_join(tt_iniciaTransporte, NULL);
    
    
    ////Destruir Mutexes
    
    
    
    
	return 0;
}



