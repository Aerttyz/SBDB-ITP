#ifndef DELETE_H
#define DELETE_H

#include "tabelas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"
/*
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
    }printf("Tabela removida!!");
}
*/
void apagar_linha(char nome_tabela[MAX_TAM_COLUNA], int id) {
    int indice_tabela = -1;
    Tabela *pegar_tabela = NULL;
    for (int i = 0; i < numero_tabela; i++) {
        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
            pegar_tabela = &tabelas[i];
            indice_tabela = i;
            break;
        }
    }
    if (indice_tabela != -1 && pegar_tabela != NULL) {
        int indice_linha = -1;
        for (int i = 0; i < pegar_tabela->numero_linha; i++) {
            if (pegar_tabela->linhas[i].id == id) {
                indice_linha = i;
                break;
            }
        }
        if (indice_linha != -1) {
            for (int i = indice_linha; i < pegar_tabela->numero_linha - 1; i++) {
                pegar_tabela->linhas[i] = pegar_tabela->linhas[i + 1];
            }
            pegar_tabela->numero_linha--;
            FILE *arquivo = fopen(ARQUIVO, "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return;
            }
            for (int i = 0; i < numero_tabela; i++) {
                if (i == indice_tabela) {
                    fprintf(arquivo, "Tabela: %s\n", pegar_tabela->nome_tabela);
                    for (int j = 0; j < pegar_tabela->numero_coluna; j++) {
                        fprintf(arquivo, "%s\t", pegar_tabela->colunas[j].nome_coluna);
                    }
                    fprintf(arquivo, "\n");
                    for (int j = 0; j < pegar_tabela->numero_linha; j++) {
                        fprintf(arquivo, "%d\t", pegar_tabela->linhas[j].id);
                        for (int k = 1; k < pegar_tabela->numero_coluna; k++) {
                            fprintf(arquivo, "%s\t", pegar_tabela->linhas[j].valores[k]);
                        }
                        fprintf(arquivo, "\n");
                    }
                    fprintf(arquivo, "\n");
                } else {
                    fprintf(arquivo, "Tabela: %s\n", tabelas[i].nome_tabela);
                }
            }

            fclose(arquivo);
            printf("Linha com ID %d removida da tabela '%s' com sucesso.\n", id, nome_tabela);
        } else {
            printf("Linha com ID %d não encontrada na tabela '%s'.\n", id, nome_tabela);
        }
    } else {
        printf("Tabela '%s' não encontrada.\n", nome_tabela);
    }
}


void apagar_tabela(char nome_tabela[MAX_TAM_COLUNA]) {
    int indice_tabela = -1;
    // Procura a tabela pelo nome
    for (int i = 0; i < numero_tabela; i++) {
        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
            indice_tabela = i;
            break;
        }
    }
    if (indice_tabela != -1) { 
        // Remove a tabela do array se for encontrada
        for (int i = indice_tabela; i < numero_tabela - 1; i++) {
            tabelas[i] = tabelas[i + 1];
        }
        // Reduz o número total de tabelas
        numero_tabela--;
        apagar_tabela_arquivo(nome_tabela);
        printf("Tabela '%s' removida com sucesso.\n", nome_tabela);
    } else {
        printf("Tabela '%s' não encontrada.\n", nome_tabela);
    }
}

#endif /*DELETE_H*/