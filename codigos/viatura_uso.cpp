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
    char cod[4], cpf[MAX];
    int q, cont = 0, op2;
    viatura *carro = NULL;
    pessoa *p = NULL;

    printf("\n====== SPM - Viatura em Uso ======\n");

    printf("Insira o código da viatura: ");
    scanf("%s", cod);

    if (verifica_codigo(cod, viaturas)) {

        carro = busca_cod(cod, viaturas);

        if (carro->disponivel == true)
            printf("Não foi embarcado\n");

        else if (carro->disponivel == false && carro->chamada == NULL)
            printf("Viatura direcionada para rondas, no aguardo de chamadas policiais\n");

        else if (!(carro->disponivel) && carro->chamada != NULL && !(carro->prisao_and))
            ocorrencia(carro->chamada, carro, pessoas);

        else if (!(carro->disponivel) && carro->chamada != NULL && carro->prisao_and){

            printf("\n====== SPM - Viatura: Prisão em Andamento ======\n");
            printf("Indivíduo(s) conduzido(s) para a DP: ");
            scanf("%d", &q);

            while(cont < q){
                printf("CPF: ");
                scanf(" %s", cpf);

                p = busca_por_cpf(pessoas, cpf);

                if(p != NULL){
                    p->preso = true;
                    cont++;

                } else {
                    printf("Pessoa não cadastrada. Tente novamente!\n");
                }
            }

            do{
                printf("\n====== SPM - Viatura: Prisão em Andamento ======\n");
                printf("1 - Confirmar retorno da DP\n");
                printf("2 - Voltar para o Menu Principal\n");
                scanf("%d", &op2);

                if(op2 == 1){
                    (carro->chamada)->concluida = true;
                    carro->chamada = NULL;
                    carro->q_chamadas += 1;
                    carro->prisao_and = false;
                }

            }while(op2 != 1 && op2 != 2);
        }
    }else
        printf("Código inválido, tente novamente");

}
