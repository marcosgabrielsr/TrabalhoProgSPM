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
void viatura_uso(viatura *&viaturas, pessoa *&pessoas, chamada *&r_begin, chamada *&r_end){
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

        else if(carro->atd_reforco)
            printf("Viatura atendendo a pedido de reforço!\n");

        else if (carro->disponivel == false && carro->chamada == NULL)
            printf("Viatura direcionada para rondas, no aguardo de chamadas policiais\n");

        else if (!(carro->disponivel) && carro->chamada != NULL && !(carro->prisao_and))
            ocorrencia(carro->chamada, carro, viaturas, pessoas, r_begin, r_end);

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
                    p->chamada = carro->chamada;
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
                    chamada *chama = carro->chamada;
                    chama->concluida = true;

                    for(viatura *v = viaturas; v != NULL; v = v->prox){
                        if(v->chamada != NULL){
                            if((v->chamada)->reforco == chama){
                                (v->chamada)->concluida = true;
                                v->chamada = NULL;
                                v->atd_reforco = false;
                                v->prisao_and = false;
                                v->q_chamadas += 1;
                            }
                        }
                    }

                    for(chamada *c = r_begin; c != NULL; c = c->prox){
                        if(!(c->concluida) && (c->reforco) == chama)
                            c->concluida = true;
                    }

                    carro->chamada = NULL;
                    carro->prisao_and = false;
                    carro->q_chamadas += 1;
                }

            }while(op2 != 1 && op2 != 2);
        }
    }else
        printf("Código inválido, tente novamente");

}
