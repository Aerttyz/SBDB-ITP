
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "delete.h"
#include "tabelas.h"
#define MAX_COLUNA 20
#define MAX_LINHA 100
#define MAX_TAM_COLUNA 50
#define ARQUIVO "arquivo.txt"

Tabela tabelas[MAX_LINHA];
int numero_tabela=0;
//Função base para receber as tabelas do arquivo.txt;
//Essa função é chamada logo ao inciar o programa;
void ler_arquivo_e_preencher_tabela() {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[MAX_TAM_COLUNA * MAX_COLUNA];
    char *token;
    //While que ler todas as linhas;
    while (fgets(linha, sizeof(linha), arquivo)) {
        Tabela nova_tabela;
        int coluna_atual = 0;
        //Lê a tabela atual;
        sscanf(linha, "Tabela: %s", nova_tabela.nome_tabela);
        (fgets(linha, sizeof(linha), arquivo));
        //Divide a linha em partes separados por espaço;
        token = strtok(linha, "\t");
        while (token != NULL) {
            //Copia a parte separada para o nome da coluna;
            strcpy(nova_tabela.colunas[coluna_atual].nome_coluna, token);
            token = strtok(NULL, "\t");
            coluna_atual++;
        }
        coluna_atual--;
        
        nova_tabela.numero_coluna = coluna_atual;
        int linha_atual = 0;
        //While para ler e preencher as linhas;
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
                //Copia cada parte para os valores das colunas;
                strcpy(nova_tabela.linhas[linha_atual].valores[coluna_atual], token);
                token = strtok(NULL,"\t");
                coluna_atual++;
            }
            linha_atual++;
        }
        nova_tabela.numero_linha = linha_atual;
        //Armazena a tabela em tabelas;
        tabelas[numero_tabela++] = nova_tabela;
    }

    fclose(arquivo);
}

//Insere a tabela no arquivo;
void inserir_dados_arquivo(Tabela *tabela) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo==NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }
    //verifica se há algo no arquivo;
    fseek(arquivo,0,SEEK_END);
    long tam_arquivo = ftell(arquivo);
    fclose(arquivo);
    //se não existir abre o arquivo como modo escrita e iniciar a escrever da linha 1 do arquivo;
    if(tam_arquivo==0){
        FILE *arquivo = fopen(ARQUIVO, "w");
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
            //imprime as linhas da coluna id;
            fprintf(arquivo, "%d\t", tabela->linhas[i].id);
            ///imprime as linhas;
            for (int j = 1; j < tabela->numero_coluna; j++) {
                fprintf(arquivo, "%s\t", tabela->linhas[i].valores[j]);
            }
            fprintf(arquivo, "\n");
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    }
    //se existir, ele abre o arquivo de forma anexação para escrever no final do arquivo;
    else{
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
            //imprime as linhas da coluna id;
            fprintf(arquivo, "%d\t", tabela->linhas[i].id);
            ///imprime as linhas;
            for (int j = 1; j < tabela->numero_coluna; j++) {
                fprintf(arquivo, "%s\t", tabela->linhas[i].valores[j]);
            }
            fprintf(arquivo, "\n");
        }
        fprintf(arquivo, "\n");
        fclose(arquivo);
    }
    
}
//Verifica se existe algum id na tabela;
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
         //Procura pela tabela comparando com o nome informado;   
        if (strcmp(tabelas[i].nome_tabela, nome_tabela) == 0) {
            //atribui a tabela encontrada;
            pegar_tabela = &tabelas[i];
            break;
        }
    }
    if (pegar_tabela == NULL) {
        printf("Não existe essa tabela.\n");
        return;
    }
    Linha nova_linha;
    int id_valido=0;
    do {
        printf("Informe o ID (deve ser inteiro e sem sinal): ");
        //Verifica se o ID é inteiro;
        if(scanf("%d", &nova_linha.id) != 1){
            printf("O ID inserido deve ser um número inteiro.\n");
            while (getchar()!='\n'); // Limpa o buffer de entrada
        } 
        //Verifica se o ID é positivo;
        else if(nova_linha.id <= 0){
            printf("O ID inserido deve ser um número inteiro positivo.\n");
        } 
        //Verifica a primary key;
        else if(testar_chave_primaria(pegar_tabela, nova_linha.id)){
            printf("Chave primária já existe.\n");
            return;
        }
        else id_valido = 1;
    }while(!id_valido);
    

    
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char linha[MAX_TAM_COLUNA * MAX_COLUNA];
    int encontrou_tabela = 0;

    
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome_lido[MAX_TAM_COLUNA];
        sscanf(linha, "Tabela: %s", nome_lido);
        // Verifica se a tabela já existe;
        if (strcmp(nome_lido, nome_tabela) == 0) {
            encontrou_tabela = 1;
            break;
        }
    }
    fclose(arquivo);
    //Se a tabela existir apaga a tabela para posteriormente gravar
    //a tabela com a nova linha adicionada;
    if(encontrou_tabela){
        apagar_tabela_arquivo(nome_tabela);
    }
    

    //Da tabela selecionada percorre o número de colunas;
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

    int numero_colunas = 1;

    char opcao;
    do {
        printf("Deseja adicionar mais uma coluna? (S/N): ");
        scanf(" %c", &opcao);

        if (toupper(opcao) == 'S') {
            printf("Informe o nome da próxima coluna: ");
            scanf(" %[^\n]", nova_tabela.colunas[numero_colunas].nome_coluna);
            numero_colunas++;
        } else if (toupper(opcao)=='N') {
            break;
        }
    } while (toupper(opcao) != 'N');

    nova_tabela.numero_coluna = numero_colunas;
    numero_tabela++;
    tabelas[numero_tabela - 1] = nova_tabela;
}

