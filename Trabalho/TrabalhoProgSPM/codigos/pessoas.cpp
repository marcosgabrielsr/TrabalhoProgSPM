//Aqui estão as funções referentes às pessoas
#include "spm_functions.h"

//Função que adiciona pessoas ao fim da lista
void add_pessoa(pessoa *&lista, char nome[], char cidade[], char cpf[], char *pass, char *inad, int idade, int q_pass, int q_inad){
    pessoa *p = lista, *novo;

    novo = (pessoa*) calloc (1, sizeof(pessoa));
    strcpy(novo->nome, nome);
    strcpy(novo->cidade, cidade);
    strcpy(novo->cpf, cpf);
    novo->q_pass = q_pass;
    novo->q_inad = q_inad;
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
        
        free(p);
    }
}

//Função que lê as pessoas que estão contidas no arquivo pessoas.txt
void ler_pessoas(pessoa *&lista){
    FILE *p;
    char nome[MAX + 1], cidade[MAX + 1], cpf[15];
    int q_pass, q_inad, idade;
    char *pass, *inad;

    p = fopen("arquivos_entrada/pessoas.txt", "r");

    if(p == NULL)
        printf("Erro ao abrir o arquivo\n");
    else{
        while(feof(p) == 0){
            fscanf(p, " %[^\n]", nome);
            fscanf(p , " %s", cpf);
            fscanf(p, " %[^\n]", cidade);
            fscanf(p, "%d", &idade);
            
            fscanf(p, "%d", &q_pass);
            if(q_pass != 0){
                pass = (char*) calloc (q_pass, sizeof(char));

                for(int i = 0; i < q_pass; i++)
                    fscanf(p, " %[^\n]", pass[i]);
            }

            fscanf(p, "%d", &q_inad);
            if(q_inad != 0){
                inad = (char*) calloc (q_inad, sizeof(char));

                for(int i = 0; i < q_inad; i++)
                    fscanf(p, " %[^\n]", inad[i]);
            }

            add_pessoa(lista, nome, cidade, cpf, pass, inad, idade, q_pass, q_inad);
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

        printf("Passagens(%d): \n", p->q_pass);
        for(int i = 0; i < p->q_pass; i++){
            printf("-%s\n", p->pass[i]);
        }

        printf("Inadiplências(%d): \n");
        for(int i = 0; i < p->q_inad; i++){
            printf("-%s\n", p->inad);
        }
    }
}