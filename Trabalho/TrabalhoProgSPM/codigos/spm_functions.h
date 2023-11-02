//Biblioteca geral para as funções do sistema

//Funcionalidades:
//Ler e armazenar pessoas
//Ler e armazenar policiais -- feito
//Ler e armazenar viaturas -- feito
//Sistema de criptografia dos policiais
//COPOM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct viatura{
    char codigo[4];
    char tipo[MAX];
    struct viatura *prox;
};

struct pessoa{
    char nome[MAX + 1], cidade[MAX + 1], cpf[15];
    int q_pass, q_inad, idade;
    char pass[MAX][MAX + 1], inad[MAX][MAX + 1];
    struct pessoa *prox;
};

struct policia{
    char nome[MAX + 1];
    char nome_guerra[MAX + 1];
    char cidade[MAX + 1];
    char cargo[MAX + 1];
    char cpf[15];
    char senha[MAX + 1];
    int idade;
    struct policia *prox;
};

//Função que imprime no terminal o menu principal
void general_menu();

//Função que adiciona novas viaturas no fim da lista
void add_viatura(viatura *&lista, char codigo[], char tipo[]);

//Função que remove a última viatura da lista
void remove_viatura(viatura *&lista);

//Função que lê os dados do arquivo viaturas.txt
void ler_viaturas(viatura *&viaturas);

//Função que imprime o código e tipo de todas as viaturas armazenadas na lista
void printf_viaturas(viatura *lista);

//Função que adiciona um policial no fim da lista
void add_policial(policia *&lista, char nome[], char cpf[], char nome_guerra[], char cidade[], int idade, char cargo[], char senha[]);

//Função que remove o último policial da lista
void remove_policial(policia *&lista);

//Função que lê os policiais que estão contidos no arquivo policiais.txt
void ler_policiais(policia *&lista);

//Função que imprime os policiais armazenados na lista
void printf_policiais(policia *lista);

//Função que adiciona pessoas ao fim da lista
void add_pessoa(pessoa *&lista, char nome[], char cidade[], char cpf[], char *pass, char *inad, int idade, int q_pass, int q_inad);

//Função que remove a última pessoa da lista
void remove_pessoa(pessoa *&lista);

//Função que lê as pessoas que estão contidas no arquivo pessoas.txt
void ler_pessoas(pessoa *&lista);

//Função que imprime no terminal as pessoas armazenadas
void printf_pessoas(pessoa *lista);