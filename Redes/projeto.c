#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

   struct cadastro
{
    char user[10];
    char mens[50];    
    int op;
};

/*
 * Cliente UDP
 */
int main(int argc, char *argv[])
{

    printf("NOME DO ARQUIVO :::::%s",argv[2]);
    int no_inicio =0;
    
    no_inicio = atoi(argv[2]);
    
    while(no_inicio > 4 || no_inicio < 1){
        
     printf("Inicie um nó de 1 a 4\nNó:");
     scanf("%d", &no_inicio);
    }
    
    iniciaEnlace(no_inicio, argv[1]);
    iniciaTeste();

    


	//Compilar o negocio estranho, fundi teste e enlace
	return 0;
}



