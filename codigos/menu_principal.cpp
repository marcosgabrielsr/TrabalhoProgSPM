//Aqui estão todas as funções responsáveis por imprimir menus no terminal
#include "spm_functions.h"

//Função que inicializa o sistemas pegando todos os dados dos arquivos
void iniciar_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais){
    ler_pessoas(pessoas);
    ler_viaturas(viaturas);
    ler_policiais(policiais);
}

//Função que limpa a memória alocada dinamicamente
void encerra_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&begin, chamada *&end){
    while(pessoas != NULL) remove_pessoa(pessoas);
    while(viaturas != NULL) remove_viatura(viaturas);
    while(policiais != NULL) remove_policial(policiais);
    while(begin != NULL) desenfileirar_chamada(begin, end);

    if(begin != NULL || end != NULL)
        printf("Erro ao desalocar as chamadas\n");
}

//Função que imprime o menu principal na tela
void menu_principal(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&begin, chamada *&end){
    int op;

    do{
        printf("\n====== SPM - Funcionalidades ======\n");
        printf("1 - Viatura login\n");
        printf("2 - Vitura em Uso\n");
        printf("3 - COPOM\n");
        printf("4 - Polícia Militar\n");
        printf("5 - Oficial\n");
        printf("6 - Comandante Geral\n");
        printf("0 - Encerrar Programa\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &op);

        if(op == 1)
            viatura_login(viaturas, policiais);
        else if(op == 3){
            menu_copom(begin, end);
            printf_chamadas(begin, 1);
        }


    }while(op != 0);
}