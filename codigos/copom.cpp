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
    novo->atribuida = false;
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
void printf_chamadas(chamada *lista){
    for(chamada *p = lista; p != NULL; p = p->prox){
        printf("\n Chamada: ");

        printf("Tipo: ");
        if(p->t_pol == 1)
            printf("Regular\n");
        else
            printf("Especializada\n");

        if(p->prioridade == 1)
            printf("Não Prioritária\n");
        else
            printf("Prioritária\n");
        
        (p->atribuida) ? printf("Atribuída: Sim\n") : printf("Atribuída: Não\n");

        (p->concluida) ? printf("Concluída: Sim\n") : printf("Concluída: Não\n");

        printf("Descrição: %s\n", p->descricao);

        printf("Localidade: %s\n", p->localidade);

        printf("\n");
    }
}

//Função que pega a viatura que recebeu menor quantidade de chamadas
viatura * pega_menor_q_chamada(viatura *viaturas, int t_pol){
    viatura *v = viaturas;
    viatura *min = viaturas;
    int t;

    if(viaturas != NULL){
        if(t_pol == 1)
            min = v;
        else
            min = v->prox;
        
        if(strcmp(v->tipo, "regular"))
            t = 1;
        else
            t = 2;
        
        while(v != NULL){
            if(t == t_pol && !(v->disponivel) && v->chamada == NULL && v->q_chamadas < min->q_chamadas)
            min = v;

            v = v->prox;
        }

        if(!(min->disponivel) && v->chamada == NULL)
            return min;
        else
            return NULL;

    } else {
        return NULL;
    }
}

//Algoritmo responsável por distribuir uma chamada recém chegada
void distribuir_chamada(chamada *&chamadas_p, chamada *&chamadas_np, viatura *&viaturas){
    chamada *cp = chamadas_p;
    chamada *cpn = chamadas_np;
    viatura *v;

    //verifica se há alguma polícia regular ou especializada para atender às chamadas prioritárias
    while(cp != NULL){
        v = pega_menor_q_chamada(viaturas, cp->t_pol);

        //Se há alguma vitura que atenda aos requisitos de distribuição de chamadas
        if(v != NULL){
            //Atribuimos a chamada à esta respectiva viatura e atualizamos o status da chamada
            //para atribuida
            v->chamada = cp;
            cp->atribuida = true;
            printf("Chamada atribuída à viatura de código: %s\n", v->codigo);
        }

        cp = cp->prox;
    }

    //Verifica se há alguma viatura regular para atender a chamadas não prioritárias
    while(cpn != NULL){
        v = pega_menor_q_chamada(viaturas, 1);

        //Se há alguma vitura que atenda aos requisitos de distribuição de chamadas
        if(v != NULL){
            //Atribuimos a chamada à esta respectiva viatura e atualizamos o status da chamada
            //para atribuida
            v->chamada = cpn;
            cpn->atribuida = true;
            printf("Chamada atribuída à viatura de código: %s\n", v->codigo);
        }

        cpn = cpn->prox;
    }

}

//Função que imprime o menu para cadastro de chamadas
void menu_copom(chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end, viatura *&viaturas){
    int t_pol, prioridade, q_viat;
    char descricao[MAX + 1], local[MAX + 1];

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

    if(prioridade == 1)
        enfileirar_chamada(np_begin, np_end, t_pol, prioridade, descricao, local);
    else
        enfileirar_chamada(p_begin, p_end, t_pol, prioridade, descricao, local);

    distribuir_chamada(p_begin, p_end, viaturas);

    printf("\n");
}