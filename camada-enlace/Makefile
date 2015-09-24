#executar projeto.c enlace.c teste.c
#gcc -c teste.c -o teste.o
#gcc -c enlace.c -o enlace.o
#gcc -c projeto.c -o projeto.o
#gcc projeto.o teste.o enlace.o -o projeto.exe

all: frag gera
	

frag:
	gcc -c rede.c -o rede.o
	gcc -c enlace.c -o enlace.o
	gcc -c projeto.c -o projeto.o
	gcc -c garbler.c -o garbler.o

gera:
	gcc projeto.o rede.o enlace.o garbler.o -o projeto.exe -lpthread
