//Aqui estão todas as funções referentes às viaturas
#include "spm_functions.h"

//Função que adiciona novas viaturas no fim da lista
void add_viatura(viatura *&lista, char codigo[], char tipo[]){
    viatura *p = lista, *novo;

    novo = (viatura*) calloc (1, sizeof(viatura));
    strcpy(novo->codigo, codigo);
    strcpy(novo->tipo, tipo);
    novo->prox = NULL;

    if(p == NULL)
        lista = novo;
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

//Função que remove a última viatura da lista
void remove_viatura(viatura *&lista){
    viatura *p = lista, *q = NULL;

    if(p != NULL){
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
}

//Função que lê os dados do arquivo viaturas.txt
void ler_viaturas(viatura *&viaturas){
    FILE *p;
    char cod[4], tipo[MAX + 1];

    p = fopen("arquivos_entrada/viaturas.txt", "r");

    if(p == NULL)
        printf("Erro ao abrir o arquivo!\n");
    else{
        while(feof(p) == 0){
            fscanf(p, "%s", cod);
            fscanf(p, "%s", tipo);
            add_viatura(viaturas, cod, tipo);
        }
        
        fclose(p);
    }
}

//Função que imprime o código e tipo de todas as viaturas armazenadas na lista
void printf_viaturas(viatura *lista){
    for(viatura *p = lista; p != NULL; p = p->prox)
        printf("código: %s,   tipo: %s \n", p->codigo, p->tipo);
    
    printf("\n");
}