//Aqui estão as funções utilizadas para a opção "Policia Militar" do menu
#include "spm_functions.h"

//Função que adiciona no fim um novo item à lista de boletins
void add_boletim(boletim *&bo, char text[]){
    boletim *b = bo, *novo;

    novo = (boletim*) calloc (1, sizeof(boletim));
    strcpy(novo->texto, text);
    novo->prox = NULL;

    if(bo == NULL)
        bo = novo;
    else{
        while(b->prox != NULL) b = b->prox;
        b->prox = novo;
    }
}

//Função que remove o último boletim do fim da lista
void remove_boletim(boletim *&bo){
    boletim *b = bo, *q = NULL;

    while(b->prox != NULL){
        q = b;
        b = b->prox;
    }

    if(b == bo)
        bo = NULL;
    else
        q = NULL;
    
    free(b);
}

//Função que busca a primeira ocorrência de um policial em uma chamada já concluída
chamada *busca_chamada_pm(policia *pm, chamada *p_begin, chamada *np_begin, chamada *r_begin){
    chamada *c;

    c = p_begin;
    while(c != NULL){
        if(!strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;
        
        c = c->prox;
    }

    c = np_begin;
    while(c != NULL){
        if(!strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;

        c = c->prox;
    }

    c = r_begin;
    while(c != NULL){
        if(!strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;

        c = c->prox;
    }

    return NULL;
}

//Função que verifica login e retorna o ponteiro do pm caso o login esteja correto
policia *verifica_login(policia *&pms, char nome_guerra[], char senha[]){
    policia *p = pms;

    printf("antes: %s\n", senha);

    criptografar(senha);

    printf("depois: %s\n", senha);

    while(p != NULL){
        if(!(strcmp(p->nome_guerra, nome_guerra)) && !(strcmp(p->senha, senha)))
            return p;

        p = p->prox;
    }

    return NULL;
}

//Função responsável por gerar um boletim de ocorrência
void pm_gera_boletim(policia *policiais, chamada *&p_begin, chamada *&np_begin, chamada *&r_begin, boletim *&boletim){
    char nome_guerra[MAX + 1];
    char senha[MAX + 1];
    char texto[MAX_TEXT];
    policia *pm = NULL;
    FILE *file = NULL;
    
    printf("\n====== SPM - Polícia Militar ======\n");

    printf("Nome de Guerra: ");
    scanf("%s", nome_guerra);

    printf("Senha: ");
    scanf("%s", senha);

    pm = verifica_login(policiais, nome_guerra, senha);

    if(pm != NULL){
        printf("Insira o texto: ");
        scanf(" %[^\n]", texto);

    } else
        printf("Código Inválido!\n");
}