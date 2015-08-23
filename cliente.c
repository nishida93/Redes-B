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
main(argc, argv)
int argc;
char **argv;

{
   struct cadastro cad;        
  
   int opcao=1;    

   char erro[50];
       
   int s;
   unsigned short port;
   int sockint, namelen, client_address_size, server_address_size;
   struct sockaddr_in client, server;

   server_address_size = sizeof(server);    

   int i = 0;

   /* 
    * O primeiro argumento (argv[1]) é o endereço IP do servidor.
    * O segundo argumento (argv[2]) é a porta do servidor.
    */
   if(argc != 3)
   {
      printf("Use: %s enderecoIP porta\n",argv[0]);
      exit(1);
   }
  port = htons(atoi(argv[2]));

   /*
    * Cria um socket UDP (dgram).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /* Define o endereço IP e a porta do servidor */
   server.sin_family      = AF_INET;            /* Tipo do endereço         */
   server.sin_port        = port;               /* Porta do servidor        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Endereço IP do servidor  */

    int j=0;    

    while(1==1)
   {        
       printf("Opcoes: \n");
       printf("1 - Cadastrar mensagem \n");
       printf("2 - Ler mensagens \n");
       printf("3 - Sair da aplicacao \n");
       scanf("%d",&opcao);
   
       switch(opcao)
       {
        case 1:
        {
                
             printf("\nUsuario: ");
                  __fpurge(stdin);
                  fscanf(stdin, " %10[^\n]", cad.user);
                  printf("Mensagem: ");
                  __fpurge(stdin);
              fscanf(stdin, " %50[^\n]", cad.mens);
            printf("\n");
            
            cad.op=1;

            if (sendto(s, &cad, sizeof(cad), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
                  {
                      perror("sendto()");
                      exit(2);
                  }

            if(recvfrom(s, &erro, sizeof(erro), 0, (struct sockaddr *) &server,
                    &server_address_size) <0)
               {
                       perror("recvfrom()");
                       exit(1);
               }                

            printf("%s\n", erro);
    
            break;        
        }

        case 2:
        {
            int z;
            
            cad.op = 2;

                if (sendto(s, &cad, sizeof(cad), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
                  {
                      perror("sendto()");
                      exit(2);
                  }

            if(recvfrom(s, &z, sizeof(int), 0, (struct sockaddr *) &server,
                    &server_address_size) <0)
               {
                       perror("recvfrom()");
                       exit(1);
               }                

            printf("Quantidade de mensagens: %d\n", z);    
            
            for(i=0; i<z; i++)
            {
                if(recvfrom(s, &cad, sizeof(cad), 0, (struct sockaddr *) &server,
                         (unsigned int *)&server_address_size) <0)
                    {
                          perror("recvfrom()");
                          exit(1);
                    }
                

                printf("Usuario: %s         ", cad.user);
                printf("Mensagem: %s\n", cad.mens);
            }
            
            break;
        }

        case 3:
            exit(1);                        

    }                
   }
   
   /* Fecha o socket */
   close(s);
}
