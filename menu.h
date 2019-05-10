#include <stdio.h>
#include <stdlib.h>


void menu_principal(){
	FILE *fl = fopen("logo_software.txt","r");
	if(fl == NULL){
		printf("Infelizmente houve um erro ao carregar o arqui do logotipo!");
		exit(1);
	}
	while(!feof(fl)){
		putchar(fgetc(fl));
	}
	printf("\n\t\t1 => Exercitar por um arquivo de texto");
	printf("\n\t\t2 => Inserir o texto a exercitar");
	printf("\n\t\t0 => Sair\n");
}
