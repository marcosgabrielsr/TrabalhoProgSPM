//Aqui estão todas as funções responsáveis pela opção Oficial
#include "spm_functions.h"

boletim *oficial_r_boletim(boletim *&bos, boletim *&r_bo){
    boletim *bo = bos, *aux = NULL;

    while(bo != r_bo && bo != NULL){
        aux = bo;
        bo = bo->prox;
    }

    if(bo == bos){
        bos = bos->prox;
        free(bo);
        return bos;
    
    } else {
        aux->prox = bo->prox;
        free(bo);
        return aux->prox;
    }
}

void conta_viaturas(viatura *viaturas, policia *pms, int &q_v, int &q_p){
    viatura *v = viaturas;
    policia *p = pms;

    while(v != NULL){
        if(!(v->disponivel)){
            q_v += 1;

            p = pms;
            while(p != NULL){
                if(!strcmp(v->codigo, p->cod_viat))
                    q_p += 1;

                p = p->prox;
            }
        }

        v = v->prox;
    }
}

//Função que imprime no terminal o menu de opções do oficial
void menu_oficial(boletim *&bos, viatura *&viaturas, policia *&policiais){
    int op, op2;
    char nome_guerra[MAX + 1], senha[MAX + 1];
    boletim *bo = bos;
    bool continuar = true;
    policia *pm = NULL;

    printf("\n====== SPM - Oficial ======\n");
    printf("Nome Guerra: ");
    scanf("%s", nome_guerra);
    printf("Senha: ");
    scanf("%s", senha);

    pm = verifica_login(policiais, nome_guerra, senha);

    if(pm != NULL || strcmp(pm->cargo, "Oficial") != 0)
        printf("Login Inválido. Oficial não Encontrado!\n");
    
    else{
        do{
            printf("1 - Visualizar Boletins \n2 - Gerar Relatório \n3 - Sair \n");
            printf("Escolha uma opção: ");
            scanf("%d", &op);

            if(op == 1){
                if(bos == NULL)
                    printf("Não há Boletins\n");

                else{
                    while(bo != NULL && continuar){
                        
                        printf("\n====== SPM - Oficial Exclusão de Boletins\n");
                        printf("Texto: %s \n\n", bo->texto);

                        do{
                            printf("1 - Excluir \n2 - Ir para o próximo \n3 - Sair\n");
                            printf("Escolha uma das opções: ");
                            scanf("%d", &op2);

                            if(op2 == 1)
                                bo = oficial_r_boletim(bos, bo);

                            else if(op2 == 2)
                                bo = bo->prox;

                            else if(op2 == 3)
                                continuar = false;                

                            else 
                                printf("Opção inválida. Tente novamente!\n");

                            printf("\n");

                        }while(op2 != 1 && op2 != 2 && op2 != 3);

                        printf("\n");
                    }

                    if(bos == NULL)
                        printf("Não há mais boletins\n");
                }
            }

            else if(op == 2){

            }

            // else if(op != 3)

        }while(op != 3);
    }
}