//Aqui estão as funções referentes às pessoas
#include "spm_functions.h"

//Adiciona crimes na última posição da lista
void add_crime(crime *&lista, char word[MAX + 1]){
    crime *p = lista, *novo;

    novo = (crime*) calloc (1, sizeof(crime));
    strcpy(novo->crime, word);
    novo->prox = NULL;

    if(lista == NULL)
        lista = novo;
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

//Função que remove o último crime da lista
void remove_crime(crime *&lista){
    crime *p = lista, *q = NULL;

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

//Função que imprime todos os crimes da lista
void printf_crime(crime *lista){
    for(crime *p = lista; p != NULL; p = p->prox)
        printf("- %s\n", p->crime);

    printf("\n");
}

//Função que adiciona pessoas ao fim da lista
void add_pessoa(pessoa *&lista, char nome[], char cidade[], char cpf[], crime *pass, crime *inad, int idade){
    pessoa *p = lista, *novo;

    novo = (pessoa*) calloc (1, sizeof(pessoa));
    novo->preso = false;
    strcpy(novo->nome, nome);
    strcpy(novo->cidade, cidade);
    strcpy(novo->cpf, cpf);
    novo->pass = pass;
    novo->inad = inad;
    novo->idade = idade;
    novo->prox = NULL;

    if(p == NULL)
        lista = novo;
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

//Função que remove a última pessoa da lista
void remove_pessoa(pessoa *&lista){
    pessoa *p = lista, *q = NULL;

    if(lista != NULL){
        while(p->prox != NULL){
            q = p;
            p = p->prox;
        }

        if(p == lista)
            lista = NULL;
        else
            q->prox = NULL;
        
        while(p->pass != NULL) remove_crime(p->pass);
        while(p->inad != NULL) remove_crime(p->inad);

        free(p);
    }
}

//Função que lê as pessoas que estão contidas no arquivo pessoas.txt
void ler_pessoas(pessoa *&lista){
    FILE *p;
    char nome[MAX + 1], cidade[MAX + 1], cpf[15];
    int q_pass, q_inad, idade;
    char word[MAX];

    p = fopen("arquivos_entrada/pessoas.txt", "r");

    if(p == NULL)
        printf("Erro ao abrir o arquivo\n");
    else{
        while(feof(p) == 0){
            crime *pass = NULL, *inad = NULL;

            fscanf(p, " %[^\n]", nome);
            fscanf(p , " %s", cpf);
            fscanf(p, " %[^\n]", cidade);
            fscanf(p, "%d", &idade);
            
            fscanf(p, "%d", &q_pass);
            if(q_pass != 0){
                for(int i = 0; i < q_pass; i++){
                    fscanf(p, " %[^\n]", word);
                    add_crime(pass, word);
                }
            }

            fscanf(p, "%d", &q_inad);
            if(q_inad != 0){
                for(int i = 0; i < q_inad; i++){
                    fscanf(p, " %[^\n]", word);
                    add_crime(inad, word);
                }
            }

            add_pessoa(lista, nome, cidade, cpf, pass, inad, idade);
        }
        
        fclose(p);
    }
}

//Função que imprime no terminal as pessoas armazenadas
void printf_pessoas(pessoa *lista){
    for(pessoa *p = lista; p != NULL; p = p->prox){
        printf("Nome: %s\n", p->nome);
        printf("CPF: %s\n", p->cpf);
        printf("Cidade: %s\n", p->cidade);
        printf("Idade: %d\n", p->idade);

        printf("Passagens: \n");
        printf_crime(p->pass);

        printf("Inadimplências: \n");
        printf_crime(p->inad);

        printf("\n");
    }
}

//Função que busca uma pessoa por CPF e retorna seu ponteiro
pessoa *busca_por_cpf(pessoa *pessoas, char cpf[]){
    pessoa *p = pessoas;

    if(pessoas != NULL){
        while(p != NULL){
            if(strcmp(p->cpf, cpf) == 0)
                return p;

            p = p->prox;
        }
    }

    return NULL;
}