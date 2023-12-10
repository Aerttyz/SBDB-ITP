#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <string.h>
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

typedef struct {
    char nome_coluna[MAX_TAM_COLUNA];
    int primary_key;
    int tipo;
} Coluna;

typedef struct {
    char valores[MAX_COLUNA][100];
    int id;
} Linha;

typedef struct {
    char nome_tabela[MAX_TAM_COLUNA];
    int numero_coluna;
    Coluna colunas[MAX_COLUNA];
    int numero_linha;
    Linha linhas[MAX_LINHA];
} Tabela;

extern Tabela tabelas[];
extern int numero_tabela;


void ler_arquivo_e_preencher_tabela();

void inserir_dados_arquivo(Tabela *tabela);

int testar_chave_primaria(Tabela *tabela, int id);

void criar_linha();

void criar_tabela();
#endif /*TABELAS_H*/