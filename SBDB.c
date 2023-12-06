#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "delete.h"
#include "tabelas.h"
#include "pesquisas.h"
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

int main() {
    int operador = 1;
    ler_arquivo_e_preencher_tabela();
    while (operador) {
        printf("\n----Selecione uma das seguintes opções:\n");
        printf("0 - Fechar programa\n1 - Criar tabela\n2 - Listar tabelas\n3 - Criar nova linha na tabela\n4 - Listar dados de uma tabela\n5 - Pesquisar valor em uma tabela\n6 - Apagar linha de uma tabela\n7 - Apagar uma tabela\n");
        scanf(" %d", &operador);
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
                    scanf(" %[^\n]", nome_tabela);
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
            case 5:
                pesquisar_valor();
                break;
            case 6:
                char nome_tabela_apagar_linha[MAX_TAM_COLUNA];
                int id_linha_apagar;
                printf("Informe o nome da tabela da qual deseja apagar a linha: ");
                scanf(" %[^\n]", nome_tabela_apagar_linha);
                printf("Informe o ID da linha que deseja apagar: ");
                scanf(" %d", &id_linha_apagar);
                apagar_linha(nome_tabela_apagar_linha, id_linha_apagar);
                break;
            case 7:
                char nome_tabela_apagar[MAX_TAM_COLUNA];
                printf("Informe o nome da tabela que deseja apagar: ");
                scanf(" %[^\n]", nome_tabela_apagar);
                apagar_tabela(nome_tabela_apagar);
                break;
            case 0:
                //inserir_dados_arquivo(pegar_tabela)
                printf("Finalizando...\n");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    }
    return 0;
}