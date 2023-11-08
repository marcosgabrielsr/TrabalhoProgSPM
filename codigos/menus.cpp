//Aqui estão todas as funções responsáveis por imprimir menus no terminal
#include "spm_functions.h"

//Função que inicializa o sistemas pegando todos os dados dos arquivos
void iniciar_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais){
    ler_pessoas(pessoas);
    ler_viaturas(viaturas);
    ler_policiais(policiais);
}

//Função que limpa a memória alocada dinamicamente
void encerra_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais){
    while(pessoas != NULL) remove_pessoa(pessoas);
    while(viaturas != NULL) remove_viatura(viaturas);
    while(policiais != NULL) remove_policial(policiais);

    if(pessoas != NULL || viaturas != NULL || policiais != NULL)
        printf("Erro ao desalocar a memória alocada dinamicamente! \n");
}

void menu_principal(){
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

        scanf("%d", &op);

    }while(op != 0);
}