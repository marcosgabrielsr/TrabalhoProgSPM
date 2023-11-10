//Aqui estão todas as funções responsáveis por imprimir menus no terminal
#include "spm_functions.h"

//Função que inicializa o sistemas pegando todos os dados dos arquivos
void iniciar_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais){
    ler_pessoas(pessoas);
    ler_viaturas(viaturas);
    ler_policiais(policiais);
}

//Função que limpa a memória alocada dinamicamente
void encerra_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end){
    while(pessoas != NULL) remove_pessoa(pessoas);
    while(viaturas != NULL) remove_viatura(viaturas);
    while(policiais != NULL) remove_policial(policiais);

    while(p_begin != NULL) desenfileirar_chamada(p_begin, p_end);

    while(np_begin != NULL) desenfileirar_chamada(np_begin, np_end);

    if(p_begin != NULL || p_end != NULL)
        printf("Erro ao desalocar as chamadas\n");
    
    if(np_begin != NULL || np_end != NULL)
        printf("Erro ao desalocar as chamadas\n");
}

//Função que imprime o menu principal na tela
void menu_principal(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end){
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

        printf("\n");

        if(op == 1)
            viatura_login(pessoas, viaturas, policiais, p_begin, np_begin);

        else if(op == 2)
            viatura_uso(viaturas);

        else if(op == 3)
            menu_copom(p_begin, p_end, np_begin, np_end, viaturas);

    }while(op != 0);
}