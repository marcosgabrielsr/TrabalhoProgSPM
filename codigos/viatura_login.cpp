//Aqui estão todas as funções referentes às viaturas
#include "spm_functions.h"

//Função que busca uma viatura disponível e que corresponde às especificações da chamada
viatura *busca_viatura(viatura *&viaturas, char cod[]){
    viatura *p = viaturas;

    while(p != NULL){
        if(strcmp(p->codigo, cod) == 0 && p->disponivel)
            return p;

        p = p->prox;
    }

    return NULL;
}

//Função que busca um policial segundo o nome de guerra informado
policia *busca_policial(){

}

//Função que imprime o menu viatura login e executa suas funcionalidades
void viatura_login(viatura *&viaturas, policia *&policiais){
    char cod[4], nome_guerra[MAX + 1];
    int quant_pol, t = 0, cont = 0;
    bool c = true;
    viatura *carro = NULL;

    printf("====== SPM - Viatura Login ======\n");

    do{
        printf("Polícia (1 - regular / 2 - expecializada): ");
        scanf("%d", &t);
        if(t != 1 && t != 2) printf("Código inválido, tente novamente! \n");

    }while(t != 1 && t != 2);

    do{
        printf("Código da Viatura: ");
        scanf("%s", cod);

        carro = busca_viatura(viaturas, cod);

        if(carro == NULL)
            printf("Este carro não está disponível. Tente novamente! \n");

        else if(strcmp(carro->tipo, "regular") == 0 && t == 1 || strcmp(carro->tipo, "especializada") == 0 && t == 2)
            c = false;
        
        else
            printf("O tipo de viatura requerido não coincide com o tipo de polícia informado. Tente novamente.\n");

    }while(c);

    c = true;
    do{
        printf("Quantidade de PMs: ");
        scanf("%d", &quant_pol);

        if(t == 1){
            if(quant_pol >= 2 && quant_pol <= 4)
                c = false;
            else
                printf("Quantidade inválida. Tente novamente!\n");
        } else{
            if(quant_pol == 4)
                c = false;
            else
                printf("Quantidade inválida. Tente novamente!\n");
        }

    }while(c);

    printf("Identificação dos PMs: ");
    while(cont < quant_pol){
        printf("Nome Guerra: ");
        scanf("%s", nome_guerra);

        cont++;
    }
}