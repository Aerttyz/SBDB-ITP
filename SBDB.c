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
        printf("Erro ao abrir o arquivo.\n");
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
        for (int j = 1; j < tabela->numero_coluna; j++) {
            printf("%s\t", tabela->linhas[i].valores[j]);
        }
        printf("\n");
    }
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
        } else if (opcao != 'N' && opcao != 'n') {
            printf("Opção inválida. Por favor, digite S ou N.\n");
        }
    } while (toupper(opcao) != 'N');

    nova_tabela.numero_coluna = numero_colunas;
    numero_tabela++;
    tabelas[numero_tabela - 1] = nova_tabela;
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
        printf("%d - %s\n", i , pegar_tabela->colunas[i].nome_coluna);
    }

    int escolha_coluna;
    printf("Selecione o número da coluna para a pesquisa: ");
    scanf(" %d", &escolha_coluna);
    
    // Ajuste para manipular corretamente o índice da coluna

    if (escolha_coluna < 0 || escolha_coluna >= pegar_tabela->numero_coluna) {
        printf("Opção de coluna inválida.\n");
        return;
    }
    if(escolha_coluna!=0){
    char tipo_pesquisa;
    char valor_pesquisa[MAX_COLUNA];
    int valor_pesquisa_int;

    printf("Digite S para string ou N para números\n");
    scanf(" %c", &tipo_pesquisa);

    if (toupper(tipo_pesquisa) == 'S') {
        printf("Digite o valor para pesquisa: ");
        scanf(" %[^\n]", valor_pesquisa);
    } else if (toupper(tipo_pesquisa) == 'N') {
        printf("Digite o valor para pesquisa: ");
        if (pegar_tabela->colunas[escolha_coluna].tipo == 1) {
            scanf(" %d", &valor_pesquisa_int);
        } else {
            printf("Essa coluna não é do tipo número.\n");
            return;
        }
    }

    printf("Selecione uma das seguintes opções:\n1 - Valores maiores que o informado\n2 - Valores maiores ou iguais ao informado\n3 - Valores iguais ao informado\n4 - Valores menores que o informado\n5 - Valores menores ou iguais ao informado\n6 - Valores próximo ao informado (caso a coluna seja de string)\n");
    int opcao_pesquisa;
    
    printf("Escolha a opção de pesquisa: ");
    scanf(" %d", &opcao_pesquisa);
    
    for(int i = 0; i < pegar_tabela->numero_linha;i++){
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
                if(valor_encontrado){
                    return;
                }
            }
            else {
                printf("Essa opção só é válida para pesquisa em strings.\n");
            }
            break;
        default:
            printf("Opção de pesquisa inválida.\n");
            return;
 
    }

       }
}else{
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
int main() {
    int operador = 1;

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
