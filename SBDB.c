#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    int inteiro;
    char *string;
    float floats;
    double doubles;
    char caracteres;
} TABELA;

TABELA **aumentar_lin(int colun, int *lin) {
    (*lin)++;
    TABELA **tabela = (TABELA **)malloc(sizeof(TABELA *) * (*lin));
    tabela[(*lin) - 1] = (TABELA *)malloc(sizeof(TABELA) * colun);
    return tabela;
}

void liberar_espaço(TABELA **tabela, int lin){
    for(int i = 0; i < lin; i++) {
        free(tabela[i]);
    }
    free(tabela);
}

void criar_tabela(TABELA ***tabela, int *lin, int *colun) {
    printf("Informe o nome da tabela:\n");
    char nome_tabela[50];
    char nome_colun[50];
    scanf(" %[^\n]", nome_tabela);
    printf("Informe quantas colunas sua tabela terá:");
    scanf("%d", colun);

    *tabela = aumentar_lin(*colun, lin);
    if (*tabela == NULL) {
        return;
    }
    (*tabela)[0][0].string = (char *)malloc(strlen(nome_tabela) + 1);
    strcpy((*tabela)[0][0].string, nome_tabela);
    printf("nome table: %s\n", (*tabela)[0][0].string);

    for (int i = 1; i < *colun + 1; i++) {
        printf("Informe o nome da coluna:");
        scanf(" %[^\n]", nome_colun);
        (*tabela)[0][i].string = (char *)malloc(strlen(nome_colun) + 1);
        strcpy((*tabela)[0][i].string, nome_colun);
    }
    
}

void listar_tabela(void) {
    printf("listar");
}

TABELA **criar_linha(TABELA **tabela, int colun, int *lin) {
    TABELA **temp = aumentar_lin(colun, lin);
    if (temp == NULL) {
        return tabela;
    }
    return temp;
}

void listar_dados(TABELA **tabela, int lin, int colun) {
    printf("\nImprimindo a tabela:\n");
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < colun+1; j++) {
            if (tabela[i][j].string != NULL) {
                printf("%s\t", tabela[i][j].string);
            } else {
                printf("NULL\t");
            }
        }
        printf("\n");
    }
}

void pesquisar_valor(void) {
    printf("pesquisar");
}

void apagar_linha(void) {
    printf("apagar");
}

void apagar_tabela(void) {
    printf("apagar_tabela");
}

int main() {
    int operador = 1;
    int lin = 0;
    int colun = 0;
    TABELA **tabela = NULL;

    while (operador) {
        printf("\nSelecione uma das seguintes opções:\n");
        printf("0 - Fechar programa\n1 - Criar tabela\n2 - Listar tabelas\n3 - Criar nova linha na tabela\n4 - Listar dados de uma tabela\n5 - Pesquisar valor em uma tabela\n6 - Apagar linha de uma tabela\n7 - Apagar uma tabela\n");
        operador = 0;

        scanf("%d", &operador);
        switch (operador) {
        case 1:
            criar_tabela(&tabela, &lin, &colun);
            break;
        case 2:
            listar_tabela();
            break;
        case 3:
            tabela = criar_linha(tabela, colun, &lin);
            break;
        case 4:
            listar_dados(tabela,lin,colun);
            break;
        case 5:
            pesquisar_valor();
            break;
        case 6:
            apagar_linha();
            break;
        case 7:
            apagar_tabela();
            break;
        case 0:
            printf("Finalizando...");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    }

    liberar_espaço(tabela, lin);

    return 0;
}
