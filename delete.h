#ifndef DELETE_H
#define DELETE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

void apagar_linha(char nome_tabela[MAX_TAM_COLUNA], int id); 

void apagar_tabela(char nome_tabela[MAX_TAM_COLUNA]); 

void apagar_tabela_arquivo(char nome_tabela[MAX_TAM_COLUNA]); 
#endif /*DELETE_H*/