#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//adiciona palavras no arquivo que é lido no jogo
void grava (FILE *palavras)
{
	char *inserir;	
	inserir = (char *)malloc(40*sizeof(char));	
	*inserir = 1;
	palavras = fopen ("FORCA.txt", "a");
	
  while(*inserir!=0)
  {
		printf("Insira a palavra: ");
		__fpurge(stdin);
		gets(inserir);
				
		fprintf(palavras, "%s", inserir);			
		if(*inserir!=0)
			fprintf(palavras, "\n");
	}
	printf("\n");
	
	fclose(palavras);
	free(inserir);
}

//gera a palavra aleatória
void secreto(FILE *palavras, char *dados)
{
	char *ler;
	int *rd, *tamanho, *i;
	
	palavras = fopen ("FORCA.txt", "r");

	rd = (int *)malloc(sizeof(int));
	tamanho = (int *)malloc(sizeof(int));
	ler = (char *)malloc(sizeof(char));
	i = (int *)malloc(sizeof(int));
	
	*tamanho = 0;
	
	while((*ler=getc(palavras))!=EOF)
		if(*ler=='\n')
			(*tamanho)++;
	
	rewind(palavras);		
	
	srand(time(NULL));
	*rd = 1+rand()%(*tamanho);
	
	for(*i=0; *i<(*rd); (*i)++)
		fgets(dados, 50, palavras);	
	
 	fclose(palavras);
 	free(rd); free(tamanho); free(ler); free(i);
}

//le o tamanho da palavra
int checatamanho(char *dados)
{
	int i;
	
	i = strlen(dados)-1;
	
	return i;
}

//gera os "traços" no tamanho da palavra secreta
void teste (char *pal, int *conta)
{
	int i;
	
	for(i=0; i<(*conta); i++)
		pal[i] = '_';
}

//imprime o tabuleiro do jogo
void tabuleiro(char *dados, int *erros, int *cd, char *pal)
{
	system("clear");
	system("clear");
		
	switch(*erros)
	{ 
		case 0:
			printf("__________\n|         |\n|\n|\n|\n|\n|\n|\t%s\n", dados);
			break;
		case 1:
			printf("__________\n|         |\n|         o\n|\n|\n|\n|\n|\t%s\n", dados);	
			break;
		case 2:
			printf("__________\n|         |\n|         o\n|         |\n|\n|\n|\n|\t%s\n", dados);	
			break;
		case 3:
			printf("__________\n|         |\n|         o\n|        /|\n|\n|\n|\n|\t%s\n", dados);	
			break;
		case 4:
			printf("__________\n|         |\n|         o\n|        /|\\ \n|\n|\n|\n|\t%s\n", dados);	
			break;
		case 5:
			printf("__________\n|         |\n|         o\n|        /|\\ \n|        /\n|\n|\n|\t%s\n", dados);	
			break;
		case 6:
			printf("__________\n|         |\n|         o\n|        /|\\ \n|        / \\ \n|\n|\n|\t%s\n", dados);	
			break;
		case 7:
			printf("__________\n|         |\n|         o\n|        /|\\ \n|        / \\ \n|\n|\n|\t%s\n", dados);						
			printf("\n\n==============\nVOCÊ PERDEU!!!\n==============\n\n");
			printf("\nA palavra era: %s\n", pal);
		
			(*cd)=0;		
			break;	
	}											
}

//testa se você acertou ou errou
void testerro (int *tam, int *erros, char *dados, char *secret, char *letra)
{
	int i, certa=77, certa2=0, certa3=0, certa4=0;
			
	for(i=0; i<(*tam); i++)
		if(*letra==dados[i])
		{
			certa=i;
			break;
		}
			
		for(i=(certa+1); i<(*tam); i++)
			if(*letra==dados[i])
			{
				certa2=i;
				break;
			}

		for(i=(certa2+1); i<(*tam); i++)
			if(*letra==dados[i])
			{
				certa3=i;
				break;
			}		

		for(i=(certa3+1); i<(*tam); i++)
			if(*letra==dados[i])
			{
				certa4=i;
				break;
			}	
			
	if(certa==77 && certa2==0 && certa3==0 && certa4==0)
		(*erros)++;				
	else	
	{
		if(certa!=77)
			secret[certa] = *letra;
		if(certa2!=0)
			secret[certa2] = *letra;
		if(certa3!=0)
			secret[certa3] = *letra;		
		if(certa4!=0)
			secret[certa4] = *letra;			
	}					
}

//checa a condição de vitória
int win(char *dados, char *secret, int *tam, int *cd)
{
	int i, c=0;
	
	for(i=0; i<(*tam); i++)
		if(secret[i]==dados[i])
			c++;
	
	if(c==(*tam))
	{
		system("clear");
	  system("clear");		
		printf("\n\n==============\nVOCÊ GANHOU!!!\n==============\n\n");
		(*cd)=0;
	}	
		
	c=0;		
}

//função que salva o tempo 
double tempo()
{
 struct timeval tv;
 
 gettimeofday(&tv,0);
 
 return (tv.tv_sec+tv.tv_usec/1e6);
}

void main ()
{
	//declara as variaveis e abre arquivo
	int i, j, t=0;
	FILE *arquivo, *besttime;
	char *palavra, *segredo, *letra;
	int *mode, *cont, *erro, *cond, *cond2;
	double t1,t2,aux;
	besttime = fopen("BestTimes.txt", "a");

	//reserva espaço na memoria
	palavra = (char *)malloc(40*sizeof(char));
	mode = (int *)malloc(sizeof(int));
	cont = (int *)malloc(sizeof(int));
	segredo = (char *)malloc(40*sizeof(char));
	erro = (int *)malloc(sizeof(int));
	letra = (char *)malloc(sizeof(char));
	cond = (int *)malloc(sizeof(char));
	cond2 = (int *)malloc(sizeof(char));

	//atribui valores as devidas variaveis			
	*erro = 0; *cond = 1; *cond2 = 1;

	//tela inicial do game	
	system("clear");
	system("clear");	
			printf("================================================================================\nFAZER\t\t\tCÓDIGO\n\nADICIONAR PALAVRAS\t1\nJOGAR\t\t\t2\n\n================================================================================\n");
	printf("O que fazer: ");		
	scanf("%d", mode);		
	
	if(*mode==1)
		grava(arquivo);
	else if(*mode==2)
	{
		t1 = tempo();
		
		secreto(arquivo, palavra);
		*cont = checatamanho(palavra);
		teste(segredo, cont);

		while(*cond==1 && *cond2==1)
		{
			tabuleiro(segredo, erro, cond, palavra);		
			printf("\nInsira uma letra: ");
			__fpurge(stdin);		
			gets(letra);
			tabuleiro(segredo, erro, cond, palavra);
			testerro(cont, erro, palavra, segredo, letra);	
			tabuleiro(segredo, erro, cond, palavra);
			win(palavra, segredo, cont, cond2);			
		}	
	
		//pega o tempo final e faz a conta da duração do jogo		
		if(*cond2==0)
		{	
			t2 = tempo();
			fprintf(besttime, "%.3lf segundos\n", t2-t1);
			fclose(besttime);		
		}
		else
		 fclose(besttime);
		
		//abre o arquivo e arruma em ordem crescente
		besttime = fopen("BestTimes.txt", "r");	 
		
		while((*letra=getc(besttime))!=EOF)
			if(*letra == '\n')
				t++;
		
		double vet[t];
		char seg[50];
				
		rewind(besttime);
		
		for(i=0; i<t; i++)
		 fscanf(besttime, "%lf%s", &vet[i], seg); 
		
		for(i=0; i<t; i++)
		 for(j=i; j<t; j++)
			if(vet[i]>vet[j])
			{
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
		 
		fclose(besttime);
		
		besttime = fopen("BestTimes.txt", "w");	
				
		for(i=0; i<t; i++)
			fprintf(besttime, "%.3lf %s\n", vet[i], seg);			
			
		fclose(besttime);
		
		besttime = fopen("BestTimes.txt", "r");			
		
		printf("===============\nMELHORES TEMPOS\n\n");
		while((*letra=getc(besttime))!=EOF)
			printf("%c", *letra);	
		printf("===============\n\n");			 
				
		fclose(besttime);											
	}
		free(palavra); free(mode); free(cont); free(segredo); free(erro); free(letra); free(cond);
}
