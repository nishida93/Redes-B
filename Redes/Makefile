#executar projeto.c enlace.c teste.c
#gcc -c teste.c -o teste.o
#gcc -c enlace.c -o enlace.o
#gcc -c projeto.c -o projeto.o
#gcc projeto.o teste.o enlace.o -o projeto.exe

all: frag gera
	

frag:
	gcc -c teste.c -o teste.o
	gcc -c enlace.c -o enlace.o
	gcc -c projeto.c -o projeto.o

gera:
	gcc projeto.o teste.o enlace.o -o projeto.exe
