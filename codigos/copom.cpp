//Aqui estão todas as funções referentes ao copom e ao cadastro de chamadas
#include "spm_functions.h"

//Função que adiciona uma chamada na última posição da lista
void add_chamada(chamada *&lista, int t_pol, int prio, char descricao[], char local[]){
    chamada *p = lista, *novo;

    novo = (chamada*) calloc (1, sizeof(chamada));
    novo->prioridade = prio;
    novo->t_pol = t_pol;
    strcpy(novo->descricao, descricao);
    strcpy(novo->localidade, local);
    novo->concluida = false;
    novo->prox = NULL;

    if(lista == NULL)
        lista = novo;
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

//Função que remove a última chamada da lista
void remove_chamada(chamada *&lista){
    chamada *p = lista, *q = NULL;

    while(p->prox != NULL){
        q = p;
        p = p->prox;
    }

    if(p == lista)
        lista = NULL;
    else
        q->prox = NULL;
    
    free(p);
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
void menu_copom(chamada *&lista){
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

        add_chamada(lista, t_pol, prioridade, descricao, local);

        printf("Continuar (1/0): ");
        scanf("%d", &ativo);

        printf("\n");
    }while(ativo);
}