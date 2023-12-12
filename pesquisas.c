
#include "tabelas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pesquisas.h"
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

void listar_dados(Tabela *tabela) {
    printf("Dados da tabela %s:\n", tabela->nome_tabela);
    //Imprime as coluna;
    for (int i = 0; i < tabela->numero_coluna; i++) {
        printf("%s\t", tabela->colunas[i].nome_coluna);
    }
    printf("\n");
    //Imprime o ID;
    for (int i = 0; i < tabela->numero_linha; i++) {
        printf("%d\t", tabela->linhas[i].id);
        //Imprime o resto da linha;
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
    for (int i = 0; i < pegar_tabela->numero_coluna; i++)
        printf("%d - %s\n", i, pegar_tabela->colunas[i].nome_coluna);

    int escolha_coluna;
    printf("Selecione o número da coluna para a pesquisa: ");
    scanf(" %d", &escolha_coluna);

    if (escolha_coluna < 0 || escolha_coluna >= pegar_tabela->numero_coluna) {
        printf("Opção de coluna inválida.\n");
        return;
    }

    char tipo_pesquisa;
    printf("Digite S para string, N para números inteiros ou F para números decimais\n");
    scanf(" %c", &tipo_pesquisa);

    char valor_pesquisa[MAX_COLUNA];
    int valor_pesquisa_int;
    double valor_pesquisa_float;

    if (toupper(tipo_pesquisa) == 'S')
        printf("Digite o valor para pesquisa: "), scanf(" %[^\n]", valor_pesquisa);
    else if (toupper(tipo_pesquisa) == 'N')
        printf("Digite o valor para pesquisa: "), scanf(" %d", &valor_pesquisa_int);
    else if (toupper(tipo_pesquisa) == 'F')
        printf("Digite o valor para pesquisa: "), scanf(" %lf", &valor_pesquisa_float);

    printf("Selecione uma das opções:\n1 - Maior que\n2 - Maior ou igual\n3 - Igual\n4 - Menor que\n5 - Menor ou igual\n6 - Próximo (para strings)\n");

    int opcao_pesquisa;
    printf("Escolha a opção de pesquisa: ");
    scanf(" %d", &opcao_pesquisa);
    printf("Valores encontraos:\n");
    for (int i = 0; i < pegar_tabela->numero_linha; i++) {
        switch (opcao_pesquisa) {
        case 1:
            // Valores maior que o informado
            if ((toupper(tipo_pesquisa) == 'S' && strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) > 0) ||
                (toupper(tipo_pesquisa) == 'N' && atoi(pegar_tabela->linhas[i].valores[escolha_coluna]) > valor_pesquisa_int) ||
                (toupper(tipo_pesquisa) == 'F' && atof(pegar_tabela->linhas[i].valores[escolha_coluna]) > valor_pesquisa_float))
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        case 2:
            // Valores maior ou igual ao informado
            if ((toupper(tipo_pesquisa) == 'S' && strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) == 0) ||
                (toupper(tipo_pesquisa) == 'N' && atoi(pegar_tabela->linhas[i].valores[escolha_coluna]) >= valor_pesquisa_int) ||
                (toupper(tipo_pesquisa) == 'F' && atof(pegar_tabela->linhas[i].valores[escolha_coluna]) >= valor_pesquisa_float))
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        case 3:
            // Valores igual ao informado
            if ((toupper(tipo_pesquisa) == 'S' && strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) == 0) ||
                (toupper(tipo_pesquisa) == 'N' && atoi(pegar_tabela->linhas[i].valores[escolha_coluna]) == valor_pesquisa_int) ||
                (toupper(tipo_pesquisa) == 'F' && atof(pegar_tabela->linhas[i].valores[escolha_coluna]) == valor_pesquisa_float))
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        case 4:
            // Valores menor que o informado
            if ((toupper(tipo_pesquisa) == 'S' && strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) < 0) ||
                (toupper(tipo_pesquisa) == 'N' && atoi(pegar_tabela->linhas[i].valores[escolha_coluna]) < valor_pesquisa_int) ||
                (toupper(tipo_pesquisa) == 'F' && atof(pegar_tabela->linhas[i].valores[escolha_coluna]) < valor_pesquisa_float))
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        case 5:
            // Valores menor ou igual ao informado
            if ((toupper(tipo_pesquisa) == 'S' && strcmp(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) <= 0) ||
                (toupper(tipo_pesquisa) == 'N' && atoi(pegar_tabela->linhas[i].valores[escolha_coluna]) <= valor_pesquisa_int) ||
                (toupper(tipo_pesquisa) == 'F' && atof(pegar_tabela->linhas[i].valores[escolha_coluna]) <= valor_pesquisa_float))
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        case 6:
            // Valores próximo ao informado (para strings)
            if (toupper(tipo_pesquisa) == 'S' && strstr(pegar_tabela->linhas[i].valores[escolha_coluna], valor_pesquisa) != NULL)
                 
                printf("%s\n", pegar_tabela->linhas[i].valores[escolha_coluna]);
            break;
        default:
            printf("Opção de pesquisa inválida.\n");
            return;
        }
    }
}




