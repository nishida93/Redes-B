#include <stdio.h>    /* for printf()*/ 
#include <stdlib.h>   /* for exit(1);*/
#include <sys/socket.h>
#include <netinet/in.h>
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
#include <arpa/inet.h>
#include <pthread.h>
#include <netdb.h>


void error(char *msg){
 perror(msg);
    
 exit(0);
    
}

int main(int argc, char *argv[])
{

int sock,length, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    struct hostent *hp;
    
    char buffer[256];
    
    sock = socket(AF_INET, SOCK_DGRAM,0);
    
    if(sock < 0){
        error("socket");
        
    }
    
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]); //Localhost
    
    if(hp == 0){
        error("Uknown host");
        
    }
    
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr,hp->h_length);
    
    server.sin_port = htons(atoi(argv[2])); //5000
    length=sizeof(struct sockaddr_in);
    
    printf("Please enter a message: ");
    
    bzero(buffer, 256);
    fgets(buffer,255,stdin);
    
    scanf("%d",&teste);
    
    strcpy(buffer,"EAI");
    
    n=sendto(sock,buffer,strlen(buffer),0,&server,length);
    
    if(n < 0 ){
        error("Sendto");
    }
    
    n=recvfrom(sock,buffer,256,0,&from,&length);

    if(n < 0){
        error("recvfrom");
    }
    
    write(1,"Got an ack: ",12);
    write(1,buffer,n);
    
    
    
    
}



