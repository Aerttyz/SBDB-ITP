#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char nome_tabela[50];
struct tabela{
    int dados_tabela[3][3];
}
void criar_tabela(void){
    printf("Informe o nome da tabela:\n");
    scanf("%s",nome_tabela);
    struct tabela *ptr = (struct tabela *)malloc(sizeof(struct tabela));
    if(prt == NULL) printf("Erro ao definir nome.\n"); return 1;
    free(ptr);
    printf("informe")
}
void listar_tabela(void){
    printf("listar");
}
void criar_linha(void){
    printf("criar_linha");
}
void listar_dados(void){
    printf("listar_dados");
}
void pesquisar_valor(void){
    printf("pesquisar");
}
void apagar_linha(void){
    printf("apagar");
}
void apagar_tabela(void){
    printf("apagar_tabela");
}
int main(){
    int operador=1;
    
    while(operador){
        printf("\nSelecione uma das seguintes opções:\n");
        printf("0 - Fechar programa\n1 - Criar tabela\n2 - Listar tabelas\n3 - Criar nova linha na tabela\n4 - Listar dados de uma tabela\n5 - Pesquisar valor em uma tabela\n6 - Apagar linha de uma tabela\n7 - Apagar uma tabela\n");
        

        scanf("%d",&operador);
        switch(operador){
            case 1:
                criar_tabela();
                break;
            case 2:
                listar_tabela();
                break;
            case 3:
                criar_linha();
                break;
            case 4:
                listar_dados();
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
        }
    }
    return 0;
}