#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

Tabela tabelas[MAX_LINHA];
int numero_tabela = 0;
 
void inserir_dados_arquivo(Tabela *tabela) {
    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    fprintf(arquivo, "Tabela: %s\n", tabela->nome_tabela);
    for (int i = 0; i < tabela->numero_coluna; i++) {
        fprintf(arquivo, "%s\t", tabela->colunas[i].nome_coluna);
    }
    fprintf(arquivo, "\n");
    
    for (int i = 0; i < tabela->numero_linha; i++) {
        fprintf(arquivo, "%d\t", tabela->linhas[i].id);
        //aqui foi feito outro ajuste técnico
        for (int j = 1; j < tabela->numero_coluna; j++) {
            fprintf(arquivo, "%s\t", tabela->linhas[i].valores[j]);
        }
        fprintf(arquivo, "\n");
    }
    fprintf(arquivo, "\n");
    fclose(arquivo);
}

int testar_chave_primaria(Tabela *tabela, int id) {
    for (int i = 0; i < tabela->numero_linha; i++) {
        if (tabela->linhas[i].id == id) return 1;
    }
    return 0;
}

void criar_linha() {
    char nome_tabela[MAX_TAM_COLUNA];
    printf("Informe o nome da tabela que deseja inserir a nova linha: ");
    scanf(" %[^\n]", nome_tabela);
    Tabela *pegar_tabela = NULL;
    for (int i = 0; i < numero_tabela; i++) {
        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
            pegar_tabela = &tabelas[i];
            break;
        }
    }
    if (pegar_tabela == NULL) {
        printf("Não existe essa tabela.\n");
        return;
    }
    Linha nova_linha;
    printf("Informe os valores da nova linha:\n");
    printf("Insira o ID (deve ser inteiro e sem sinal): ");
    scanf(" %d", &nova_linha.id);
    if (testar_chave_primaria(pegar_tabela, nova_linha.id)) {
        printf("Chave primária já existente.\n");
        return;
    }
    //aqui tem ajustes técnicos para poder pegar os valores sem vazar memoria, por isso começa do 1 
    for (int i = 1; i < pegar_tabela->numero_coluna; i++) {
        printf(" %s: ", pegar_tabela->colunas[i].nome_coluna);
        scanf(" %s", nova_linha.valores[i]);
    }
    pegar_tabela->linhas[pegar_tabela->numero_linha++] = nova_linha;
    inserir_dados_arquivo(pegar_tabela);
}

void criar_tabela() {
    Tabela nova_tabela;
    printf("Informe o nome da tabela: ");
    scanf(" %[^\n]", nova_tabela.nome_tabela);
    printf("Informe o nome da coluna da chave primária (ID): ");
    scanf(" %[^\n]", nova_tabela.colunas[0].nome_coluna);
    nova_tabela.colunas[0].primary_key = 1;
    nova_tabela.colunas[0].tipo = 1;

    int numero_colunas = 1;

    char opcao;
    do {
        printf("Deseja adicionar mais uma coluna? (S/N): ");
        scanf(" %c", &opcao);

        if (toupper(opcao) == 'S') {
            printf("Informe o nome da próxima coluna: ");
            scanf(" %[^\n]", nova_tabela.colunas[numero_colunas].nome_coluna);
            nova_tabela.colunas[numero_colunas].primary_key = 0; 
            nova_tabela.colunas[numero_colunas].tipo = 1; 
            numero_colunas++;
        } else if (toupper(opcao)=='N') {
            printf("Opção inválida. Por favor, digite S ou N.\n");
        }
    } while (toupper(opcao) != 'N');

    nova_tabela.numero_coluna = numero_colunas;
    numero_tabela++;
    tabelas[numero_tabela - 1] = nova_tabela;
}

#endif /*TABELAS_H*/