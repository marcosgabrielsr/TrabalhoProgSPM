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
        if(strlen(pm->cod_viat) != 0 && !strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;
        
        c = c->prox;
    }

    c = np_begin;
    while(c != NULL){
        if(strlen(pm->cod_viat) != 0 && !strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;

        c = c->prox;
    }

    c = r_begin;
    while(c != NULL){
        if(strlen(pm->cod_viat) != 0 && !strcmp(pm->cod_viat, c->cod) && c->concluida && !(c->tem_bo))
            return c;

        c = c->prox;
    }

    return NULL;
}

//Função que verifica login e retorna o ponteiro do pm caso o login esteja correto
policia *verifica_login(policia *&pms, char nome_guerra[], char senha[]){
    policia *p = pms;

    criptografar(senha);

    while(p != NULL){
        if(!(strcmp(p->nome_guerra, nome_guerra)) && !(strcmp(p->senha, senha)))
            return p;

        p = p->prox;
    }

    return NULL;
}

void ler_boletim(boletim *&bos){
    FILE *bo = NULL;
    char text[MAX_TEXT];

    bo = fopen("arquivos_saida/boletim.txt", "r");

    if(bo == NULL)
        printf("Erro ao abrir o boletim.txt\n");
    else{
        while(feof(bo) == 0){
            fscanf(bo, " %[^\n]", text);

            add_boletim(bos, text);
        }

        fclose(bo);
    }
}

//Função que atualiza o arquivo txt que armazena os boletins
void update_boletim(boletim *bos){
    FILE *bo = NULL;
    boletim *b = bos;

    bo = fopen("arquivos_saida/boletim.txt", "w");

    while(b != NULL){
        if(b->prox != NULL)
            fprintf(bo, "%s\n", b->texto);
        else
            fprintf(bo, "%s", b->texto);
        
        b = b->prox;
    }

    fclose(bo);
}

//Função responsável por gerar um boletim de ocorrência
void pm_gera_boletim(policia *policiais, chamada *&p_begin, chamada *&np_begin, chamada *&r_begin, boletim *&bos){
    bool continuar = true;
    int op;
    char nome_guerra[MAX + 1];
    char senha[MAX + 1];
    char texto[MAX_TEXT];
    policia *pm = NULL;
    chamada *c = NULL;
    
    printf("\n====== SPM - Polícia Militar ======\n");

    printf("Nome de Guerra: ");
    scanf("%s", nome_guerra);

    printf("Senha: ");
    scanf("%s", senha);

    pm = verifica_login(policiais, nome_guerra, senha);

    if(pm != NULL){
        printf("Login Correto!\n");

        do{
            c = busca_chamada_pm(pm, p_begin, np_begin, r_begin);

            if(c != NULL){
                printf("\n====== SPM - Boletim Chamda ======\n");
                printf("Descricao: %s\n", c->descricao);
                printf("Localidade: %s\n", c->localidade);

                do{
                    printf("Escolha uma das opções abaixo: \n");
                    printf("1 - Gerar Boletim \n2 - Encerrar\n");
                    scanf("%d", &op);

                    if(op == 1){
                        c->tem_bo = true;
                        printf("Insira o texto: ");
                        scanf(" %[^\n]", texto);

                        add_boletim(bos, texto);

                        update_boletim(bos);
                    
                    } else if(op == 2)
                        continuar = false;

                }while(op != 1 && op != 2);
            
            }else{
                printf("Não há chamadas para realizar boletim!\n");
            }

        }while(c != NULL && continuar);

    } else
        printf("Login Inválido!\n");
}