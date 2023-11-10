//Aqui estão todas as funções referentes às viaturas
#include "spm_functions.h"

//Função que apresenta o menu para ação policial em relação a uma chamada
void ocorrencia(chamada *&chama, viatura *&v, pessoa *&pessoas){
    int op, op2;
    char cpf[MAX];
    pessoa *p = NULL;

    printf("\n====== SPM - Viatura Chamada Policial ======\n");
    printf("Descrição: %s \n", chama->descricao);
    printf("Localidade: %s \n", chama->localidade);
    printf("Confirmar Ação Policial - 1     Ação Policial Dispensada - 2\n");
    scanf("%d", &op);

    if(op == 2){
        chama->concluida = true;
        v->chamada = NULL;
        v->q_chamadas += 1;

    } else if(op == 1){

        do{
            printf("\n====== SPM - Viatura Ocorrência ======\n");
            printf("1 - Pesquisar por CPF\n");
            printf("2 - Soliciar Reforços\n");
            printf("3 - Prisão em Andamento\n");
            printf("4 - Encerrar Ocorrência\n");

            printf("Escolha uma das opções: ");
            scanf("%d", &op);

            if(op == 1){
                printf("\n====== SPM - Viatura: Pesquisar por CPF ======\n");
                printf("CPF: ");
                scanf("%s", cpf);

                p = busca_por_cpf(pessoas, cpf);

                if(p != NULL){
                    printf("Nome: %s\n", p->nome);
                    printf("CPF: %s\n", p->cpf);
                    printf("Idade: %d\n", p->idade);
                    printf("Passagens(%d):\n", p->q_pass);
                    printf_crime(p->pass);
                    printf("Inadiplências(%d):\n", p->q_inad);
                    printf_crime(p->inad);

                    do{
                        printf("1 - Encerrar Visualização\n");
                        scanf("%d", &op2);
                    }while(op2 != 1);
                }
                else{
                    printf("Pessoa não cadastrada. Tente novamente!\n");
                }

            } else if(op == 2){
                printf("\n====== SPM - Viatura: Solicitar Reforços ======\n");
                printf("1 - Confirmar Solicitação de Reforços\n");
                printf("2 - Cancelar\n");

                do{
                    scanf("%d", &op2);

                    if(op2 != 1 && op2 != 2)
                        printf("Opção inválida. Tente novamente!\n");
                    else if(op2 == 1){
                        //Será adicionado um pedido de reforço à uma lista
                        //encadeada responsável por armazenar os pedidos de reforços
                    }
                }while(op2 != 1 && op2 != 2);
            }
        }while(op != 4);
    }
}

//Função que imprime o menu viatura login e executa suas funcionalidades
void viatura_login(pessoa *&pessoas, viatura *&viaturas, policia *&policiais, chamada *&chamada_p, chamada *&chamada_np){
    char cod[4], nome_guerra[MAX + 1];
    int quant_pol, op = 0, cont = 0, tipo = 0;
    bool c = true, find = false;
    viatura *carro = NULL;
    policia *pm = NULL;
    chamada *chama = NULL;

    printf("====== SPM - Viatura Login ======\n");

    do{
        printf("\nPolícia (1 - regular / 2 - expecializada): ");
        scanf("%d", &tipo);
        if(tipo != 1 && tipo != 2) printf("Código inválido, tente novamente! \n");

    }while(tipo != 1 && tipo != 2);

    do{
        printf("\nCódigo da Viatura: ");
        scanf("%s", cod);

        carro = busca_viatura(viaturas, cod);

        if(carro == NULL)
            printf("Este carro não está disponível. Tente novamente! \n");

        else if(strcmp(carro->tipo, "regular") == 0 && tipo == 1 || strcmp(carro->tipo, "especializada") == 0 && tipo == 2){
            carro->disponivel = false;
            c = false;
        }
        
        else
            printf("O tipo de viatura requerido não coincide com o tipo de polícia informado. Tente novamente.\n");

    }while(c);

    c = true;
    do{
        printf("\nQuantidade de PMs: ");
        scanf("%d", &quant_pol);

        if(tipo == 1){
            if(quant_pol >= 2 && quant_pol <= 4)
                c = false;
            else
                printf("Quantidade inválida. Tente novamente!\n");
        } else{
            if(quant_pol == 4)
                c = false;
            else
                printf("Quantidade inválida. Tente novamente!\n");
        }

    }while(c);

    printf("\nIdentificação dos PMs: ");
    while(cont < quant_pol){
        printf("\nNome Guerra: ");
        scanf("%s", nome_guerra);

        pm = busca_policial(policiais, nome_guerra);

        if(pm == NULL)
            printf("O PM inserido não está disponível. Tente novamente!\n");
        else{
            strcpy(pm->cod_viat, cod);
            cont++;
        }
    }

    do{
        printf("\nPara finalizar escolha uma das opções: \n");
        printf("1 - Apto para atender ocorrência\n");
        printf("2 - Cancelar Embarcação\n");
        printf("Escolha uma das opções: ");

        scanf("%d", &op);

        if(op != 2 && op != 1)
            printf("Opção inválida. Tente novamente!\n");

        else if(op == 2){
            carro->disponivel = true;
            cont = 0;

            while(cont < quant_pol){
                policia *p = policiais;
                while(p != NULL){
                    if(strcmp(p->cod_viat, cod) == 0)
                        strcpy(p->cod_viat, "");

                    p = p->prox;
                }

                cont++;
            }
        }

        else if(op == 1){
            if(chamada_p != NULL){
                chama = chamada_p;

                while(chama != NULL && !find){
                    if(!(chama->atribuida) && chama->t_pol == tipo){
                        find = true;
                        carro->chamada = chama;
                        chama->atribuida = true;
                        ocorrencia(chama, carro, pessoas);
                    }
                    else
                        chama = chama->prox;
                }
            }

            if(chamada_np != NULL){
                chama = chamada_np;

                while(chama != NULL && !find){
                    if(!(chama->atribuida) && chama->t_pol == tipo){
                        find = true;
                        carro->chamada = chama;
                        chama->atribuida = true;
                        ocorrencia(chama, carro, pessoas);
                    }
                }
            }

            if(chamada_p == NULL && chamada_np == NULL || carro->chamada == NULL){
                printf("\n====== SPM - Viatura em Modo Ronda ======\n");
                printf("Viatura direcionada para rondas, no aguardo de chamadas policiais\n");
                printf("1 - Voltar para o Menu Principal\n");
                scanf("%d", &op);
                op = 2;
            }
        }

    }while(op != 1 && op != 2);
    
    printf("\n");
}