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
    scanf("%d", &nova_linha.id);
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

    int numero_colunas = 1; // Começamos com 1 para a coluna ID

    char opcao;
    do {
        printf("Deseja adicionar mais uma coluna? (S/N): ");
        scanf(" %c", &opcao);

        if (opcao == 'S' || opcao == 's') {
            printf("Informe o nome da próxima coluna: ");
            scanf(" %[^\n]", nova_tabela.colunas[numero_colunas].nome_coluna);
            nova_tabela.colunas[numero_colunas].primary_key = 0; // Não é chave primária
            nova_tabela.colunas[numero_colunas].tipo = 1; // Tipo de dados, exemplo 1 para string
            numero_colunas++;
        } else if (opcao != 'N' && opcao != 'n') {
            printf("Opção inválida. Por favor, digite S ou N.\n");
        }
    } while (opcao != 'N' && opcao != 'n');

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
void pesquisar_valor(){
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
        if(pegar_tabela->colunas[i].primary_key!=1){
        printf("%d - %s\n", i + 1, pegar_tabela->colunas[i].nome_coluna);
        }
    }

    int escolha_coluna;
    printf("Selecione o número da coluna para a pesquisa: ");
    scanf("%d", &escolha_coluna);
    escolha_coluna--;

    if (escolha_coluna < 0 || escolha_coluna >= pegar_tabela->numero_coluna) {
        printf("Opção de coluna inválida.\n");
        return;
    }
	
    char tipo_pesquisa;
    char valor_pesquisa[MAX_COLUNA];
    int valor_pesquisa_int;
    printf("Digite S para string ou N para números\n");
    scanf(" %c", &tipo_pesquisa);
    if(tipo_pesquisa=='S' || tipo_pesquisa=='s'){
    	printf("Digite o valor para pesquisa: ");
    	scanf(" %[^\n]", valor_pesquisa);
    }else if(tipo_pesquisa=='N' || tipo_pesquisa=='n'){
    	printf("Digite o valor para pesquisa: ");
	scanf("%d",&valor_pesquisa_int);
    }
    
    
    printf("Selecione uma das seguintes opções:\n 1 - Valores maior que o informado\n2 - Valores maior ou igual ao informado\n3 - Valores igual ao informado\n4 - Valores menor que o informado\n5 - Valores menor ou igual ao informado\n6 - Valores próximo ao informado (caso a coluna seja de string)\n");
    int opcao_pesquisa;
    printf("Escolha a opção de pesquisa: ");
    scanf("%d", &opcao_pesquisa);

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
