#include "menu.h"
#include <ctype.h>
#include <string.h>

#define MAX_LENGHT 90000
#define MAX_CHAR_TELA 30

int main(){
	
	int opcao;
	int pos_character = 0;
	int charac;
	long tamanho;
	int flag = -1;
	int certo = 0, errado = 0;
	char texto[MAX_LENGHT]; 
	int *diagnostico;

	fase1:
	menu_principal();
	opcao = getch();
	system("cls");
	switch(opcao){
		case '1': 
			printf("Insira o caminho do arquivo:\n");
			gets(texto);
			FILE *arquivo = fopen(texto,"r");
			if(arquivo == NULL){
				printf("Erro ao carregar o arquivo!\n");
				goto fase1;
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
			tamanho = sizeof(arquivo);
			diagnostico = (int *)calloc(tamanho,sizeof(int));
			for(pos_character = 0; pos_character<tamanho;){
				system("cls");
				register int i; //  (pos_character * 50)/tamanho
				// secao onde estara o progresso do exto concluido
				putchar('[');
				for(i=0;i<(pos_character * 50)/(tamanho-1);i++) putchar('=');
				for(i=(pos_character * 50)/(tamanho-1);i<= 50;i++) putchar(' ');
				printf("]%.2f%",(float)(pos_character * 100)/(float)(tamanho-1));
				putchar('\n');
				// parte para mostrar o progresso do texto
				rewind(arquivo);
				for(i=0; i<pos_character;i++) fgetc(arquivo);
				//fseek(arquivo,pos_character,SEEK_SET); 
				for(i = pos_character; (i<pos_character+MAX_CHAR_TELA) && (i<tamanho);i++ ) putchar(fgetc(arquivo));
	
				putchar('\n');
				rewind(arquivo);
				for(i=0; i<pos_character;i++) fgetc(arquivo);
				//fseek(arquivo,pos_character,SEEK_SET);
				charac = getch();
				if(charac == 8 && pos_character>0){
					pos_character--;
					if(diagnostico[pos_character] == 1) certo--;
					if(diagnostico[pos_character] == 0) errado--;
					continue;
				}
				if(fgetc(arquivo) == charac) diagnostico[pos_character] = 1, certo++;
				else diagnostico[pos_character] = 0, errado++, putchar('\7');
				
			}
			printf("\n\n");
			printf("Certos: %d\nErrado: %d\n\n",certo,errado);
			getch(),system("cls");
			goto fase1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			break;
		case '2':
			printf("Insira o texto a ser praticado: \n(Precione a tecla 'ESC' ou 'ENTER' para terminar de ensirir )\n");
			while( (charac = getche()) != 27 && charac != 13){
				if(pos_character == MAX_LENGHT-2){
					texto[pos_character] = '\0';
					break;
				}
				else if(charac == 8){
					pos_character--;
					fputc(' ',stdout);
					fputc('\b',stdout);
					continue;
				}
				texto[pos_character++] = charac;
			}
			if(charac == 27 || charac == 13) texto[++pos_character] = '\0';
			printf("\n\nTexto insirido com sucesso, %d caracters",strlen(texto));
			
			tamanho = strlen(texto);
			diagnostico = (int *)calloc(tamanho,sizeof(int));
			for(pos_character = 0; pos_character<tamanho;){
				system("cls");
				register int i; //  (pos_character * 50)/tamanho
				// secao onde estara o progresso do exto concluido
				putchar('[');
				for(i=0;i<(pos_character * 50)/(tamanho-1);i++) putchar('=');
				for(i=(pos_character * 50)/(tamanho-1);i<= 50;i++) putchar(' ');
				printf("]%.2f%",(float)(pos_character * 100)/(float)(tamanho-1));
				putchar('\n');
				// parte para mostrar o progresso do texto
				
				for(i = pos_character; (i<pos_character+MAX_CHAR_TELA) && (i<tamanho);i++ ) putchar(texto[i]);
	
				putchar('\n');
				charac = getch();
				if(charac == 8 && pos_character>0){
					pos_character--;
					if(diagnostico[pos_character] == 1) certo--;
					if(diagnostico[pos_character] == 0) errado--;
					continue;
				}
				if(texto[pos_character++] == charac) diagnostico[pos_character] = 1, certo++;
				else diagnostico[pos_character] = 0, errado++, putchar('\7');
				
			}
			printf("\n\n");
			printf("Certos: %d\nErrado: %d\n\n",certo,errado);
			getch(),system("cls");
			goto fase1;
		case 27: case '0': return 0;
		//default:
		//	system("cls");
		//	printf("Opcao errada, insira novamente!\n");
		//	goto fase1;
	}
	return 0;
}
