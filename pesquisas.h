#ifndef PESQUISAS_H
#define PESQUISAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

void listar_dados(Tabela *tabela);

void listar_tabelas();

void pesquisar_valor();


#endif /* PESQUISAS_H */