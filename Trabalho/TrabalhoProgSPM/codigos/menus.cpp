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

void viatura_login(){
    int tipo, codigo, qPm;
    bool fim = false;

    do{
        printf("\nSPM - Viatura Login\n");

        printf("Tipo de policia (1 - Polica regular / 2 - Policia especializada): ");
        scanf("%d", &tipo);

        printf("Código Viatura: ");
        scanf("%d", &codigo);

        printf("Quantidade de PMs: ");
        scanf("%d", &qPm);

        if((tipo == 1 && (qPm < 2 || qPm > 4)) || (tipo == 2 && qPm != 4))
            printf("Quantidade de PMs não conicide com o tipo de policia selecionado");
        else{

        }
    }while(!fim);
}

void menu_copom(){
    int op;

    do{}while(op != 0);
}