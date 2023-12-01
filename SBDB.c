#include <stdio.h>
#include <stdlib.h>
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

Tabela tabelas[MAX_LINHA];
int numero_tabela = 0;

void inserir_dados_arquivo(Tabela *tabela) {
    FILE *arquivo = fopen(ARQUIVO, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fprintf(arquivo, "Tabela: %s\n", tabela->nome_tabela);
    fprintf(arquivo, "ID\t");
    for (int i = 0; i < tabela->numero_coluna; i++) {
        fprintf(arquivo, "%s\t", tabela->colunas[i].nome_coluna);
    }
    fprintf(arquivo, "\n");
    
    for (int i = 0; i < tabela->numero_linha; i++) {
        fprintf(arquivo, "%d\t", tabela->linhas[i].id);
        for (int j = 0; j < tabela->numero_coluna; j++) {
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
    scanf("%d", &nova_linha.id);
    if (testar_chave_primaria(pegar_tabela, nova_linha.id)) {
        printf("Chave primária já existente.\n");
        return;
    }
    for (int i = 0; i < pegar_tabela->numero_coluna; i++) {
        printf("%s: ", pegar_tabela->colunas[i].nome_coluna);
        scanf("%s", nova_linha.valores[i]);
    }
    pegar_tabela->linhas[pegar_tabela->numero_linha++] = nova_linha;
    inserir_dados_arquivo(pegar_tabela);
}

void listar_dados(Tabela *tabela) {
    printf("Dados da tabela %s:\n", tabela->nome_tabela);
    for (int i = 0; i < tabela->numero_coluna; i++) {
        printf("%s\t", tabela->colunas[i].nome_coluna);
    }
    printf("\n");
    for (int i = 0; i < tabela->numero_linha; i++) {
        printf("%d\t", tabela->linhas[i].id);
        for (int j = 0; j < tabela->numero_coluna; j++) {
            printf("%s\t", tabela->linhas[i].valores[j]);
        }
        printf("\n");
    }
}

void criar_tabela() {
    Tabela nova_tabela;
    printf("Informe o nome da tabela: ");
    scanf("%s", nova_tabela.nome_tabela);
    printf("Informe o número de colunas: ");
    scanf("%d", &nova_tabela.numero_coluna);
    printf("Informe o nome da coluna da chave primária: ");
    scanf(" %[^\n]", nova_tabela.colunas[0].nome_coluna);
    nova_tabela.colunas[0].primary_key = 1;
    nova_tabela.colunas[0].tipo = 1;
    numero_tabela++;
    tabelas[numero_tabela - 1] = nova_tabela;
}

void listar_tabelas() {
    printf("Tabelas:\n");
    for (int i = 0; i < numero_tabela; i++) {
        printf("- %s\n", tabelas[i].nome_tabela);
    }
}

int main() {
    int operador = 1;

    while (operador) {
        printf("\nSelecione uma das seguintes opções:\n");
        printf("0 - Fechar programa\n1 - Criar tabela\n2 - Listar tabelas\n3 - Criar nova linha na tabela\n4 - Listar dados de uma tabela\n5 - Pesquisar valor em uma tabela\n6 - Apagar linha de uma tabela\n7 - Apagar uma tabela\n");
        
        scanf("%d", &operador);
        switch (operador) {
            case 1:
                criar_tabela();
                break;
            case 2:
                listar_tabelas();
                break;
            case 3:
                criar_linha();
                break;
            case 4:
                if (numero_tabela == 0) {
                    printf("Não existe tabela, crie uma para prosseguir.\n");
                } else {
                    char nome_tabela[MAX_TAM_COLUNA];
                    printf("Informe a tabela desejada: ");
                    scanf("%s", nome_tabela);
                    Tabela *pegar_tabela = NULL;
                    for (int i = 0; i < numero_tabela; i++) {
                        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
                            pegar_tabela = &tabelas[i];
                            break;
                        }
                    }
                    if (pegar_tabela == NULL) printf("Tabela não existe.\n");
                    else listar_dados(pegar_tabela);
                }
                break;
            case 0:
                printf("Finalizando...\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }

    return 0;
}
