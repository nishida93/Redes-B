#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

   struct cadastro
{
    char user[10];
    char mens[50];
    int op;    
};

/*
 * Servidor UDP
 */
main(argc,argv)


  int argc;
  char **argv;
  {
  struct cadastro cad[5];
 
  int i=0;    
  int sockint,s, namelen, client_address_size;
  struct sockaddr_in client, server;

  char erro[50];

   /*
    * Cria um socket UDP (dgram). 
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /*
    * Define a qual endereço IP e porta o servidor estará ligado.
    * Porta = 0 -> faz com que seja utilizada uma porta qualquer livre.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os endereços IP
    */
   server.sin_family      = AF_INET;   /* Tipo do endereço             */
   server.sin_port        = atoi(argv[1]);         /* Escolhe uma porta disponível */
   server.sin_addr.s_addr = INADDR_ANY;/* Endereço IP do servidor      */

   server.sin_port = htons(server.sin_port);

 

   /*
    * Liga o servidor à porta definida anteriormente.
    */
   if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
       perror("bind()");
       exit(1);
   }

   /* Consulta qual porta foi utilizada. */
   namelen = sizeof(server);
   if (getsockname(s, (struct sockaddr *) &server, &namelen) < 0)
   {
       perror("getsockname()");
       exit(1);
   }

   /* Imprime qual porta foi utilizada. */
   printf("Porta utilizada é %d\n", htons(server.sin_port));

   /*
    * Recebe uma mensagem do cliente.
    * O endereço do cliente será armazenado em "client".
    */
        
   while(1==1)
   {                  
       client_address_size = sizeof(client);

    if(recvfrom(s, &cad[i], sizeof(cad[i]), 0, (struct sockaddr *) &client, &client_address_size) <0)
       {
               perror("recvfrom()");
               exit(1);
       }

    if(cad[i].op == 3)
        exit(1);    

    if(cad[i].op == 1)
    {
        if(i<5)
        {    
            i++;
            strcpy(erro, "Mensagem cadastrada.");
        }
        else
            strcpy(erro, "Erro no cadastro.");

        if (sendto(s, &erro, (sizeof(erro)), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
            {
                  perror("sendto()");
                  exit(2);
            }
    }

    if(cad[i].op == 2)
    {
        int j;        
        
        if (sendto(s, &i, sizeof(int), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
              {
                      perror("sendto()");
                      exit(2);
              }

        for(j=0; j<i; j++)        
        {
            if (sendto(s, &cad[j], sizeof(cad[j]), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
                  {
                      perror("sendto()");
                      exit(2);
                  }
        }
    }
    }

   /*
    * Fecha o socket.
    */

   close(s);
}