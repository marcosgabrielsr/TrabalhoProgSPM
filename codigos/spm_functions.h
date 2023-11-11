//Biblioteca geral para as funções do sistema

//Funcionalidades:
//Ler e armazenar pessoas -- feito
//Ler e armazenar policiais -- feito
//Ler e armazenar viaturas -- feito
//Sistema de criptografia dos policiais -- feito
//Viatura Login -- ainda não concluído
//Viatura em Uso -- ainda não concluído
//COPOM -- feito
//Sistema de distribuição de chamadas -- ainda não concluído
//PM -- ainda não concluído

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct chamada{
    bool concluida, atribuida;
    int t_pol, prioridade;
    char descricao[MAX + 1];
    char localidade[MAX + 1];
    struct chamada *prox;
};

struct viatura{
    bool disponivel, prisao_and;
    int q_chamadas;
    struct chamada *chamada;
    char codigo[4];
    char tipo[MAX];
    struct viatura *prox;
};

struct crime{
    char crime[MAX + 1];
    struct crime *prox;
};

struct pessoa{
    bool preso;
    char nome[MAX + 1], cidade[MAX + 1], cpf[15];
    int idade;
    crime *pass, *inad;
    struct pessoa *prox;
};

struct policia{
    char nome[MAX + 1], nome_guerra[MAX + 1];
    char cidade[MAX + 1], cargo[MAX + 1];
    char cpf[15], senha[MAX + 1], cod_viat[4];
    int idade;
    struct policia *prox;
};

/*--- Funções responsáveis pela manipulação de dados do sistema --------------------------------------------------------------------------------------------*/

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

//Função que imprime todos os crimes da lista
void printf_crime(crime *lista);

//Função que imprime no terminal as pessoas armazenadas
void printf_pessoas(pessoa *lista);

//Função de criptografia para senhas
void criptografar(char word[]);

//Função que remove a última chamada da lista
void desenfileirar_chamada(chamada *&fila, chamada *&end);

//Função que imprime na tela todas as chamadas cadastradas
void printf_chamadas(chamada *lista);

//Função que imprime o menu para cadastro de chamadas, ou seja, menu copom
void menu_copom(chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end, viatura *&viaturas);

//Função que busca uma viatura disponível e que corresponde às especificações da chamada
viatura *busca_viatura(viatura *&viaturas, char cod[]);

//Função que busca um policial segundo o nome de guerra informado
policia *busca_policial(policia *&policiais, char nome_guerra[]);

//Função que busca uma pessoa por CPF e retorna seu ponteiro
pessoa *busca_por_cpf(pessoa *pessoas, char cpf[]);

//Função que apresenta o menu para ação policial em relação a uma chamada
void ocorrencia(chamada *&chama, viatura *&v, pessoa *&pessoas);

//Função responsável pela funcionalidade de viatura em uso
void viatura_uso(viatura *&viaturas, pessoa *&pessoas);

//Função que imprime o menu viatura login e executa suas funcionalidades
void viatura_login(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&chamada_p, chamada *&chamada_np);

/*--- Funções responsáveis pela execução do sistema --------------------------------------------------------------------------------------------*/

//Função que inicializa o sistema pegando todos os dados dos arquivos e armazenando nas listas passadas por parâmetro
void iniciar_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais);

//Função que limpa a memória alocada dinamicamente
void encerra_sistema(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end);

//Função que imprime o menu principal na tela
void menu_principal(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&p_begin, chamada *&p_end, chamada *&np_begin, chamada *&np_end);