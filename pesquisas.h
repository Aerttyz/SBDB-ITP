#ifndef PESQUISAS_H
#define PESQUISAS_H

#include "tabelas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

void listar_dados(Tabela *tabela) {
    printf("Dados da tabela %s:\n", tabela->nome_tabela);
    for (int i = 0; i < tabela->numero_coluna; i++) {
        printf("%s\t", tabela->colunas[i].nome_coluna);
    }
    printf("\n");
    for (int i = 0; i < tabela->numero_linha; i++) {
        printf("%d\t", tabela->linhas[i].id);
        for (int j = 1; j < tabela->numero_coluna; j++) {
            printf("%s\t", tabela->linhas[i].valores[j]);
        }
        printf("\n");
    }
}

void listar_tabelas() {
    printf("Tabelas:\n");
    for (int i = 0; i < numero_tabela; i++) {
        printf("- %s\n", tabelas[i].nome_tabela);
    }
}

void pesquisar_valor() {
    if (numero_tabela == 0) {
        printf("Não existem tabelas. Crie uma tabela para realizar a pesquisa.\n");
        return;
    }

    char nome_tabela[MAX_TAM_COLUNA];
    printf("Informe o nome da tabela onde deseja pesquisar o valor: ");
    scanf(" %[^\n]", nome_tabela);

    Tabela *pegar_tabela = NULL;
    for (int i = 0; i < numero_tabela; i++) {
        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
            pegar_tabela = &tabelas[i];
            break;
        }
    }

    if (pegar_tabela == NULL) {
        printf("Tabela não encontrada.\n");
        return;
    }

    printf("Colunas disponíveis na tabela %s:\n", pegar_tabela->nome_tabela);
    for (int i = 0; i < pegar_tabela->numero_coluna; i++) {
        printf("%d - %s\n", i, pegar_tabela->colunas[i].nome_coluna);
    }

    int escolha_coluna;
    printf("Selecione o número da coluna para a pesquisa: ");
    scanf(" %d", &escolha_coluna);

    // Ajuste para mexer no índice da coluna

    if (escolha_coluna < 0 || escolha_coluna >= pegar_tabela->numero_coluna) {
        printf("Opção de coluna inválida.\n");
        return;
    }
    if (escolha_coluna != 0) {
        char tipo_pesquisa;
        char valor_pesquisa[MAX_COLUNA];
        int valor_pesquisa_int;
        double valor_pesquisa_float;

        printf("Digite S para string, N para números inteiros ou F para números decimais\n");
        scanf(" %c", &tipo_pesquisa);

        if (toupper(tipo_pesquisa) == 'S') {
            printf("Digite o valor para pesquisa: ");
            scanf(" %[^\n]", valor_pesquisa);
        } else if (toupper(tipo_pesquisa) == 'N') {
            printf("Digite o valor para pesquisa: ");
            if (pegar_tabela->colunas[escolha_coluna].tipo == 1) {
                scanf(" %d", &valor_pesquisa_int);
            } else {
                printf("Essa coluna não é do tipo número inteiro.\n");
                return;
            }
        } else if (toupper(tipo_pesquisa) == 'F') {
            printf("Digite o valor para pesquisa: ");
            if (pegar_tabela->colunas[escolha_coluna].tipo == 1) {
                scanf(" %lf", &valor_pesquisa_float);
            } else {
                printf("Essa coluna não é do tipo número decimal.\n");
                return;
            }
        }

        printf("Selecione uma das seguintes opções:\n1 - Valores maiores que o informado\n2 - Valores maiores ou iguais ao informado\n3 - Valores iguais ao informado\n4 - Valores menores que o informado\n5 - Valores menores ou iguais ao informado\n6 - Valores próximo ao informado (caso a coluna seja de string)\n");
        int opcao_pesquisa;

        printf("Escolha a opção de pesquisa: ");
        scanf(" %d", &opcao_pesquisa);

        for (int i = 0; i < pegar_tabela->numero_linha; i++) {
            switch (opcao_pesquisa) {
            case 1:
                // Valores maior que o informado
                if (toupper(tipo_pesquisa) == 'S') {
                    if (strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) > 0) {
                        printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                    }
                } else if (toupper(tipo_pesquisa) == 'N') {
                    int valor_tabela = atoi(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela > valor_pesquisa_int) {
                        printf("%d\n", valor_tabela);
                    }
                } else if (toupper(tipo_pesquisa) == 'F') {
                    double valor_tabela = atof(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela > valor_pesquisa_float) {
                        printf("%lf\n", valor_tabela);
                    }
                }
                break;
            case 2:
                // Valores maiores ou iguais ao informado
                if (toupper(tipo_pesquisa) == 'S') {
                    if (strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) == 0) {
                        printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                    }
                } else if (toupper(tipo_pesquisa) == 'N') {
                    int valor_tabela = atoi(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela >= valor_pesquisa_int) {
                        printf("%d\n", valor_tabela);
                    }
                } else if (toupper(tipo_pesquisa) == 'F') {
                    double valor_tabela = atof(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela >= valor_pesquisa_float) {
                        printf("%lf\n", valor_tabela);
                    }
                }
                break;

            case 3:
                // Valores iguais ao informado
                if (toupper(tipo_pesquisa) == 'S') {
                    if (strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) == 0) {
                        printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                    }
                } else if (toupper(tipo_pesquisa) == 'N') {
                    int valor_tabela = atoi(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela == valor_pesquisa_int) {
                        printf("%d\n", valor_tabela);
                    }
                } else if (toupper(tipo_pesquisa) == 'F') {
                    double valor_tabela = atof(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela == valor_pesquisa_float) {
                        printf("%lf\n", valor_tabela);
                    }
                }
                break;
            case 4:
                // Valores menores
                if (toupper(tipo_pesquisa) == 'S') {
                    if (strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) < 0) {
                        printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                    }
                } else if (toupper(tipo_pesquisa) == 'N') {
                    int valor_tabela = atoi(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela < valor_pesquisa_int) {
                        printf("%d\n", valor_tabela);
                    }
                } else if (toupper(tipo_pesquisa) == 'F') {
                    double valor_tabela = atof(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela < valor_pesquisa_float) {
                        printf("%lf\n", valor_tabela);
                    }
                }
                break;
            case 5:
                // Valores menores ou iguais ao informado
                if (toupper(tipo_pesquisa) == 'S') {
                    if (strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) <= 0) {
                        printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                    }
                } else if (toupper(tipo_pesquisa) == 'N') {
                    int valor_tabela = atoi(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela <= valor_pesquisa_int) {
                        printf("%d\n", valor_tabela);
                    }
                } else if (toupper(tipo_pesquisa) == 'F') {
                    double valor_tabela = atof(pegar_tabela->linhas[i].valores[escolha_coluna]);
                    if (valor_tabela <= valor_pesquisa_float) {
                        printf("%lf\n", valor_tabela);
                    }
                }
                break;
            case 6:
                // Valores próximo ao informado (caso a coluna seja de string)
                if (toupper(tipo_pesquisa) == 'S') {
                    int valor_encontrado = 0;
                    for (int i = 0; i < pegar_tabela->numero_linha; i++) {
                        if (strstr(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) != NULL) {
                            printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
                            valor_encontrado = 1;
                        }
                    }
                    if (valor_encontrado) {
                        return;
                    }
                } else {
                    printf("Essa opção só é válida para pesquisa em strings.\n");
                }
                break;
            default:
                printf("Opção de pesquisa inválida.\n");
                return;
            }
        }
    } else {
        int valor_pesquisa_int;
        printf("Digite o valor para pesquisa: ");
        scanf(" %d", &valor_pesquisa_int);
        printf("Selecione uma das seguintes opções:\n1 - Valores maiores que o informado\n2 - Valores maiores ou iguais ao informado\n3 - Valores iguais ao informado\n4 - Valores menores que o informado\n5 - Valores menores ou iguais ao informado\n");
        int opcao_pesquisa;
        printf("Escolha a opção de pesquisa: ");
        scanf(" %d", &opcao_pesquisa);

        for (int i = 0; i < pegar_tabela->numero_linha; i++) {
            int valor_tabela = pegar_tabela->linhas[i].id;
            switch (opcao_pesquisa) {
            case 1:
                // Valores maiores que o informado
                if (valor_tabela > valor_pesquisa_int) {
                    printf("%d\n", valor_tabela);
                }
                break;
            case 2:
                // Valores maiores ou iguais ao informado
                if (valor_tabela >= valor_pesquisa_int) {
                    printf("%d\n", valor_tabela);
                }
                break;
            case 3:
                // Valores iguais ao informado
                if (valor_tabela == valor_pesquisa_int) {
                    printf("%d\n", valor_tabela);
                }
                break;
            case 4:
                // Valores menores que o informado
                if (valor_tabela < valor_pesquisa_int) {
                    printf("%d\n", valor_tabela);
                }
                break;
            case 5:
                // Valores menores ou iguais ao informado
                if (valor_tabela <= valor_pesquisa_int) {
                    printf("%d\n", valor_tabela);
                }
                break;
            default:
                printf("Opção de pesquisa inválida.\n");
                return;
            }
        }
    }
}


#endif /* PESQUISAS_H */