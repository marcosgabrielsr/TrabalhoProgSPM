//Aqui estão todas as funções referentes às viaturas
#include "spm_functions.h"

void ocorrencia(chamada *&chama, viatura *&v){
    int op;

    printf("\n====== SPM - Viatura Chamada Policial ======\n");
    printf("Descrição: %s \n", chama->descricao);
    printf("Localidade: %s \n", chama->localidade);
    printf("Confirmar Ação Policial - 1     Ação Policial Dispensada - 2\n");
    scanf("%d", &op);

    if(op == 2){
        chama->concluida = true;
        v->chamada = NULL;
    }
}

//Função que imprime o menu viatura login e executa suas funcionalidades
void viatura_login(viatura *&viaturas, policia *&policiais, chamada *&chamada_p, chamada *&chamada_np){
    char cod[4], nome_guerra[MAX + 1];
    int quant_pol, op = 0, cont = 0, tipo = 0;
    bool c = true, find = false;
    viatura *carro = NULL;
    policia *pm = NULL;
    chamada *chama = NULL;

    printf("====== SPM - Viatura Login ======\n");

    do{
        printf("\nPolícia (1 - regular / 2 - expecializada): ");
        scanf("%d", &tipo);
        if(tipo != 1 && tipo != 2) printf("Código inválido, tente novamente! \n");

    }while(tipo != 1 && tipo != 2);

    do{
        printf("\nCódigo da Viatura: ");
        scanf("%s", cod);

        carro = busca_viatura(viaturas, cod);

        if(carro == NULL)
            printf("Este carro não está disponível. Tente novamente! \n");

        else if(strcmp(carro->tipo, "regular") == 0 && tipo == 1 || strcmp(carro->tipo, "especializada") == 0 && tipo == 2){
            carro->disponivel = false;
            c = false;
        }
        
        else
            printf("O tipo de viatura requerido não coincide com o tipo de polícia informado. Tente novamente.\n");

    }while(c);

    c = true;
    do{
        printf("\nQuantidade de PMs: ");
        scanf("%d", &quant_pol);

        if(tipo == 1){
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

    printf("\nIdentificação dos PMs: ");
    while(cont < quant_pol){
        printf("\nNome Guerra: ");
        scanf("%s", nome_guerra);

        pm = busca_policial(policiais, nome_guerra);

        if(pm == NULL)
            printf("O PM inserido não está disponível. Tente novamente!\n");
        else{
            strcpy(pm->cod_viat, cod);
            cont++;
        }
    }

    do{
        printf("\nPara finalizar escolha uma das opções: \n");
        printf("1 - Apto para atender ocorrência\n");
        printf("2 - Cancelar Embarcação\n");
        printf("Escolha uma das opções: ");

        scanf("%d", &op);

        if(op != 2 && op != 1)
            printf("Opção inválida. Tente novamente!\n");

        else if(op == 2){
            carro->disponivel = true;
            cont = 0;

            while(cont < quant_pol){
                policia *p = policiais;
                while(p != NULL){
                    if(strcmp(p->cod_viat, cod) == 0)
                        strcpy(p->cod_viat, "");

                    p = p->prox;
                }

                cont++;
            }
        }

        else if(op == 1){
            if(chamada_p != NULL){
                chama = chamada_p;

                while(chama != NULL && !find){
                    if(!(chama->atribuida) && chama->t_pol == tipo){
                        find = true;
                        carro->chamada = chama;
                        ocorrencia(chama, carro);
                    }
                    else
                        chama = chama->prox;
                }
            }

            if(chamada_p == NULL && chamada_np == NULL || carro->chamada == NULL){
                printf("\n====== SPM - Viatura em Modo Ronda ======\n");
                printf("Viatura direcionada para rondas, no aguardo de chamadas policiais\n");
                printf("1 - Voltar para o Menu Principal\n");
                scanf("%d", &op);
                op = 2;
            }
        }

    }while(op != 1 && op != 2);
    
    printf("\n");
}