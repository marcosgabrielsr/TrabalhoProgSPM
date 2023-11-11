#include "spm_functions.h"

//Função que verifica se o código inserido existe
bool verifica_codigo(char cod[], viatura *viaturas){
    viatura *p = viaturas;

    while(p != NULL){
        if(strcmp(p->codigo, cod) == 0)
            return true;
        p = p->prox;
    }

    return false;
}

//função que busca o código da viatura
viatura* busca_cod(char cod[], viatura *viaturas){
    viatura *p = viaturas;

    while(p != NULL && strcmp(p->codigo, cod) != 0)
        p = p->prox;

    return p;
}

//Função responsável pela funcionalidade de viatura em uso
void viatura_uso(viatura *&viaturas, pessoa *&pessoas){

    char cod[4];
    viatura *carro = NULL;

    printf("Insira o código da viatura: ");
    scanf("%s", cod);

    if (verifica_codigo(cod, viaturas)) {

        carro = busca_cod(cod, viaturas);

        printf("cod: %s", carro->codigo);

        if (carro->disponivel == true)
            printf("Não foi embarcado");

        else if (carro->disponivel == false && carro->chamada == NULL)
            printf("Viatura direcionada para rondas, no aguardo de chamadas policiais");

        else if (!(carro->disponivel) && carro->chamada != NULL)
            ocorrencia(carro->chamada, carro, pessoas);
    }else
        printf("Código inválido, tente novamente");

}
