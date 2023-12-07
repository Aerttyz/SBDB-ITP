#ifndef TABELAS_H
#define TABELAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "delete.h"
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

void apagar_tabela_arquivo(char nome_tabela[MAX_TAM_COLUNA]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    FILE *temp_arquivo = fopen("temp.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro ao criar arquivo temp\n");
        fclose(arquivo);
        return;
    }
    char linha[1000];
    int apagar = 0;
    //enquanto houver tabelas corre no while;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, nome_tabela) != NULL) {
            apagar = 1;
            continue;
        }
        if (apagar) {
            if (linha[0] == '\n') {
                apagar = 0;
                continue;
            }continue;
        }
        fprintf(temp_arquivo, "%s", linha);
    }fclose(arquivo);
    fclose(temp_arquivo);
    if (remove(ARQUIVO) != 0) {
        printf("Erro ao apagar o arquivo original.\n");
        return;
    }
    if (rename("temp.txt", ARQUIVO) != 0) {
        printf("Erro ao renomear o arquivo temporário.\n");
        return;
    }
}

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

void ler_arquivo_e_preencher_tabela() {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[MAX_TAM_COLUNA * MAX_COLUNA];
    char *token;
    while (fgets(linha, sizeof(linha), arquivo)) {
        Tabela nova_tabela;
        int coluna_atual = 0;
        sscanf(linha, "Tabela: %s", nova_tabela.nome_tabela);
        fgets(linha, sizeof(linha), arquivo);
        token = strtok(linha, "\t");
        while (token != NULL) {
            strcpy(nova_tabela.colunas[coluna_atual].nome_coluna, token);
            token = strtok(NULL, "\t");
            coluna_atual++;
        }
            coluna_atual--;
        nova_tabela.numero_coluna = coluna_atual;
        int linha_atual = 0;
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (linha[0] == '\n') {
                break; 
            }
            sscanf(linha, " %d", &nova_tabela.linhas[linha_atual].id);

            coluna_atual = 0;
            token = strtok(linha,"\t");
            while (token != NULL) {
                if (coluna_atual >= nova_tabela.numero_coluna) {
                    break;
                }
                strcpy(nova_tabela.linhas[linha_atual].valores[coluna_atual], token);
                token = strtok(NULL,"\t");
                coluna_atual++;
            }
            linha_atual++;
        }
        nova_tabela.numero_linha = linha_atual;
        tabelas[numero_tabela++] = nova_tabela;
    }

    fclose(arquivo);
}

 
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
    
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[MAX_TAM_COLUNA * MAX_COLUNA];
    int encontrou_tabela = 0;

    // Verifica se a tabela já existe no arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome_lido[MAX_TAM_COLUNA];
        sscanf(linha, "Tabela: %s", nome_lido);
        if (strcmp(nome_lido, nome_tabela) == 0) {
            encontrou_tabela = 1;
            break;
        }
    }
    fclose(arquivo);
    if(encontrou_tabela){
        apagar_tabela_arquivo(nome_tabela);
    }
    
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
        scanf(" %[^\n]", nova_linha.valores[i]);
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
            break;
        }
    } while (toupper(opcao) != 'N');

    nova_tabela.numero_coluna = numero_colunas;
    numero_tabela++;
    tabelas[numero_tabela - 1] = nova_tabela;
}

#endif /*TABELAS_H*/
