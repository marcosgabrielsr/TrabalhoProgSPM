//Aqui estão todas as funções referente aos policiais
#include "spm_functions.h"

//Função que adiciona um policial no fim da lista
void add_policial(policia *&lista, char nome[], char cpf[], char nome_guerra[], char cidade[], int idade, char cargo[], char senha[]){
    policia *p = lista, *novo;

    novo = (policia*) calloc (1, sizeof(policia));
    strcpy(novo->nome, nome);
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome_guerra, nome_guerra);
    strcpy(novo->cidade, cidade);
    novo->idade = idade;
    strcpy(novo->cargo, cargo);
    strcpy(novo->senha, senha);
    novo->prox = NULL;

    if(p == NULL)
        lista = novo;
    else{
        while(p->prox != NULL) p = p->prox;
        p->prox = novo;
    }
}

//Função que remove o último policial da lista
void remove_policial(policia *&lista){
    policia *p = lista, *q = NULL;

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

//Função que lê os policiais que estão contidos no arquivo policiais.txt
void ler_policiais(policia *&lista){
    FILE *p;
    char nome[MAX + 1];
    char nome_guerra[MAX + 1];
    char cidade[MAX + 1];
    char cargo[MAX + 1];
    char cpf[15];
    char senha[MAX + 1];
    int idade;

    p = fopen("arquivos_entrada/policiais.txt", "r");

    if(p == NULL)
        printf("Erro ao abrir o arquivo\n");
    else{
        while(feof(p) == 0){
            fscanf(p, " %[^\n]", nome);
            fscanf(p, "%s", cpf);
            fscanf(p, " %s", nome_guerra);
            fscanf(p, " %[^\n]", cidade);
            fscanf(p, "%d", &idade);
            fscanf(p, " %[^\n]", cargo);
            fscanf(p, "%s", senha);

            add_policial(lista, nome, cpf, nome_guerra, cidade, idade, cargo, senha);
        }

        fclose(p);
    }
}

//Função que imprime os policiais armazenados na lista
void printf_policiais(policia *lista){
    for(policia *p = lista; p != NULL; p = p->prox){
        printf("Nome: %s\n", p->nome);
        printf("CPF: %s\n", p->cpf);
        printf("Nome Guerra: %s\n", p->nome_guerra);
        printf("Cidade: %s\n", p->cidade);
        printf("Idade: %d\n", p->idade);
        printf("Cargo: %s\n", p->cargo);
        printf("Senha: %s\n", p->senha);
        printf("\n");
    }
}

//Função de criptografia para senhas
void criptografar(char word[]){
    int i = 0;
    int j = strlen(word) - 1;

    for(int i = 0; word[i] != '\0'; i++){
        if(word[i] < 48 || word[i] > 57){
            word[i] = word[i] + 3;

            if(word[i] > 122)
                word[i] = 96 + (word[i] - 122);
        }
    }

    while(i < j){
        char aux = word[i];

        word[i] = word[j];
        word[j] = aux;

        i++;
        j--;
    }
}

//Função que busca um policial segundo o nome de guerra informado
policia *busca_policial(policia *&policiais, char nome_guerra[]){
    policia *p = policiais;

    while(p != NULL){
        if(strcmp(p->nome_guerra, nome_guerra) == 0 && strlen(p->cod_viat) == 0)
            return p;

        p = p->prox;
    }

    return NULL;
}