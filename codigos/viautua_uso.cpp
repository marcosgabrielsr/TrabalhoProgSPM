//Aqui estão todas as funções referentes às viaturas
#include "spm_functions.h"

void viatura_uso(viatura *&viaturas, chamada *&chamadas){

    char cod[4];
    viatura *carro = NULL;

    printf("Insira o código da viatura: ");
    scanf("%s", cod);

    carro = busca_viatura(viaturas, cod);

    if (carro == NULL)
        printf("Código inválido, tente novamente! \n");
    else if (carro->disponivel == true)
        printf("Não foi embarcado");
    else if (carro->disponivel == false && chamadas->atribuida == false)
        printf("Viatura direcionada para rondas, no aguardo de chamadas policiais");
    else{
        //etapa 4 e 5 (vinculado à viatura login)
    }
}
