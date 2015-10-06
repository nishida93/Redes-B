#include "headers/projeto.h"


int retorno_rede; // para camada rede

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
    
    
    
    
    //Mutexes enlace
if(pthread_mutex_init(&rede_enlace_env1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_enlace_env2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_enlace_rcv1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_enlace_rcv2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }


//Mutexes Redes

if(pthread_mutex_init(&rede_atualiza1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_atualiza2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }

if(pthread_mutex_init(&rede_env1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_env2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rede_rcv1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    } 
if(pthread_mutex_init(&rede_rcv2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }

if(pthread_mutex_init(&env_tabela1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&env_tabela2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rcv_tabela1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&rcv_tabela2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }


if(pthread_mutex_init(&trans_rede_env1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&trans_rede_env2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&trans_rede_rcv1, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
if(pthread_mutex_init(&trans_rede_rcv2, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }

    if(pthread_mutex_init(&buffer_rede_env, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&buffer_rede_rcv, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }

//Mutexes buffer

    if(pthread_mutex_init(&buffer_rede_env, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    if(pthread_mutex_init(&buffer_rede_rcv, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
//Mutex Controle Externo
    
    
    if(pthread_mutex_init(&controle_tabela, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&controle_rede_rcv, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
     if(pthread_mutex_init(&controle_rede_env, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&controle_randomico, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&controle_randomico, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&controle_rede_enlace_env, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    if(pthread_mutex_init(&controle_rede_enlace_rcv, NULL) != 0 ){
        printf("\n mutex init failed\n");
        return 1;
        
    }
    
    
    //Inicializar mutexs

	//pthread_mutex_lock(&mutex_rd_enlc_cons);	//Travou aqui
    pthread_mutex_lock(&rede_enlace_rcv1);
    
	//pthread_mutex_lock(&mutex_enlc_rd_cons);
    pthread_mutex_lock(&rede_enlace_rcv2);//Travou aqui

	
	//pthread_mutex_lock(&mutex_trns_rd_cons);	//Travou aqui
	pthread_mutex_lock(&trans_rede_rcv2);

	//pthread_mutex_lock(&mutex_rd_trns_cons);	//Travou aqui
    pthread_mutex_lock(&trans_rede_rcv1);
	
	//pthread_mutex_lock(&mutex_retorno_enlace_cons);	//Travou aqui
     pthread_mutex_lock(&controle_rede_enlace_env);
	
	//pthread_mutex_lock(&mutex_retorno_rede_cons);
     pthread_mutex_lock(&controle_rede_rcv);
    
    /*
    pthread_mutex_lock(&rcv_tabela2);
    pthread_mutex_lock(&rede_atualiza2);
    pthread_mutex_lock(&rede_enlace_rcv2);
    pthread_mutex_lock(&rede_enlace_env2);
    pthread_mutex_lock(&rede_rcv2);
    pthread_mutex_lock(&rede_env2);
    pthread_mutex_lock(&trans_rede_env2);
    pthread_mutex_lock(&trans_rede_rcv2);*/
    

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



