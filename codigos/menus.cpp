//Aqui estão todas as funções responsáveis por imprimir menus no terminal
#include "spm_functions.h"

void general_menu(){
    int op;

    do{
        printf("\n SPM - Funcionalidades\n");
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