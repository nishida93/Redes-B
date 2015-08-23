#include <stdio.h>    /* for printf()*/ 
#include <stdlib.h>   /* for exit(1);*/
#include <errno.h>              /* errno and error codes */
#include <sys/time.h>           /* for gettimeofday() */
#include <stdio.h>              /* for printf() */
#include <unistd.h>             /* for fork() */
#include <sys/types.h>          /* for wait() */
#include <sys/wait.h>           /* for wait() */
#include <signal.h>             /* for kill(), sigsuspend(), others */
#include <sys/ipc.h>            /* for all IPC function calls */
#include <sys/shm.h>            /* for shmget(), shmat(), shmctl() */
#include <sys/sem.h>            /* for semget(), semop(), semctl() */
#include <string.h>
#include <sys/msg.h>    /* for msgget(), msgctl() */     
#include <sys/types.h>    /* for wait(), msgget(), msgctl() */   


int matriz[10][10];
int mtu[10][10];


void print_matriz(int,int);

void print_mtu(int,int);

int tem_ligacao(int, int);

int getMtu(int,int);


struct NO{

    int no;
    int porta;
    char ip[6];

};

struct NO nos[6];




int main(void)
{
   
  char url[]="arq.config",
       nome[20];

  int node=0;     
  int number; 
  int elem1;
  int elem2;
  int elem3;
  int elem4; 
  int porta;

 
 
  char *s;
  FILE *arq;
  
  int ret=6;
  arq = fopen(url, "r");
  if(arq == NULL)
      printf("Erro, nao foi possivel abrir o arquivo\n");
  else{

    
        fscanf(arq,"%s",s);

        
          do{
            ret = fscanf(arq,"%d: IP = %d.%d.%d.%d, Porta = %d;", &number,&elem1,&elem2,&elem3,&elem4,&porta);
            
            if(ret >= 6){
              printf("%d\n%d.%d.%d.%d\n%d\n", number,elem1,elem2,elem3,elem4,porta);

            ///OLHE AQUI SENHOR NISHIDA, DA FALHA DE SEGMENTACAO AQUI.
             nos[node].no = number;
             //nos[no].porta = porta;

             sprintf(nos[node].ip,"%d.%d.%d.%d",elem1,elem2,elem3,elem4);
            //printf("\nFRI:%s\n\n", fri);
             node++;
          }
          }while(ret >= 6);

        ret=3;
        fscanf(arq,"%s",s);

        do{
            ret = fscanf(arq,"%d -> %d, MTU = %d;", &number,&elem1,&elem2);
            
            if(ret >= 3){
              printf("%d -> %d, MTU = %d;\n", number,elem1,elem2);
              matriz[number-1][elem1-1]=1;
              matriz[elem1-1][number-1]=1;
              mtu[number-1][elem1-1]=elem2;
              mtu[elem1-1][number-1]=elem2;
            }
          }while(ret >= 3);

        
        printf("\n");
  

 
}




  printf("IP:::::::::%s\n",nos[0].ip );
  printf("IP:::::::::%s\n",nos[2].ip );
  fclose(arq);

  
  print_matriz(4,4);
  print_mtu(4,4);
  printf("\n");
  
  printf("\ntem ligacao:%d\n\n", tem_ligacao(1,2));

  printf("\nMTU:%d\n\n", getMtu(1,2));

  return 0;
}




void print_matriz(int lin, int col){


    for(int x=0;x<lin;x++)
    {
        for(int y=0;y<col;y++)
        {
            printf("%d ", matriz[x][y]);
        }

        printf("\n");
    }


}

void print_mtu(int lin, int col){


  for(int x=0;x<lin;x++)
    {
        for(int y=0;y<col;y++)
        {
            printf("%d ", mtu[x][y]);
        }

        printf("\n");
    }

}

int tem_ligacao(int no1,int no2){

    if(matriz[no1][no2])
      return 1;
    return 0;

}

int getMtu(int no1, int no2){

    if(!tem_ligacao(no1,no2))
      return 0;
    return mtu[no1][no2];

}
