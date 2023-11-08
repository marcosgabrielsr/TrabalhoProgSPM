//Aqui estão todas as funções referentes ao copom e ao cadastro de chamadas
#include "spm_functions.h"

//Função que adiciona uma chamada na última posição da lista
void enfileirar_chamada(chamada *&begin, chamada *&end, int t_pol, int prio, char descricao[], char local[]){
    chamada *novo;

    novo = (chamada*) calloc (1, sizeof(chamada));
    novo->prioridade = prio;
    novo->t_pol = t_pol;
    strcpy(novo->descricao, descricao);
    strcpy(novo->localidade, local);
    novo->concluida = false;
    novo->prox = NULL;

    if(begin == NULL){
        begin = novo;
        end = novo;
    }
    else{
        end->prox = novo;
        end = novo;
    }
}

//Função que remove a última chamada da lista
void desenfileirar_chamada(chamada *&fila, chamada *&end){
    chamada *p = fila;

    if(fila != NULL){
        fila = fila->prox;
        free(p);
    }

    if(fila == NULL)
        end = NULL;
}

//Função que imprime na tela todas as chamadas cadastradas
void printf_chamadas(chamada *lista, int t_pol){
    chamada *p = lista;
    
    if(t_pol == 2){
        while(p != NULL){
            if(p->t_pol == 2 && p->prioridade == 2){
                printf("====== Polícia Especializada =======\n");
                printf("Prioridade: Prioritária\n");
                printf("Localidade: %s\n", p->localidade);
                printf("Descrição: %s\n", p->descricao);
                printf("\n");
            }

            p = p->prox;
        }
    } else{
        while(p != NULL){
            if(p->t_pol == 1){
                printf("======= Polícia Regular ======\n");
                (p->prioridade == 2) ? printf("Prioridade: Prioritária\n"):printf("Prioridade: Não Prioritária\n");
                printf("Localidade: %s\n", p->localidade);
                printf("Descrição: %s\n", p->descricao);
                printf("\n");
            }

            p = p->prox;
        }
    }
}

//Função que imprime o menu para cadastro de chamadas
void menu_copom(chamada *&begin, chamada *&end){
    int ativo = 1;
    int t_pol, prioridade, q_viat;
    char descricao[MAX + 1], local[MAX + 1];

    do{
        printf("====== SPM-COPOM ======\n");
        printf("Polícia (1 - Regular / 2 - Especializada): ");
        scanf("%d", &t_pol);

        if(t_pol == 1){
            printf("Prioridade (1 - Não Prioritária / 2 - Prioritária): ");
            scanf("%d", &prioridade);
        } else{
            printf("Prioridade: Prioritária\n");
            prioridade = 2;
        }

        printf("Descrição: ");
        scanf(" %[^\n]", descricao);

        printf("Localidade: ");
        scanf(" %[^\n]", local);

        enfileirar_chamada(begin, end, t_pol, prioridade, descricao, local);

        printf("Continuar (1/0): ");
        scanf("%d", &ativo);

        printf("\n");
    }while(ativo);
}