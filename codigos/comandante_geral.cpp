#include "spm_functions.h"

//Função responsável por criar o ofício
void oficio_ocorrencia(chamada *p_chamadas, chamada *np_chamadas, pessoa *pessoas, policia *policiais){
    FILE *c;

    chamada *chama_p = p_chamadas;
    chamada *chama_np = np_chamadas;
    pessoa *p = pessoas;
    policia *pm = policiais;

    c = fopen("arquivos_saida/oficio_ocorrencias.txt", "a");

    if (c == NULL){
        printf("Erro na abertura do arquivo");

    }else{
        fprintf(c, "%s", "Ocorrencias - \n");

        while(chama_p != NULL){
            if(chama_p->concluida){

                fprintf(c, "%s", "       Tipo Policia: ");
                (chama_p->t_pol == 1) ? fprintf(c, "%s\n", "Regular."): fprintf(c, "%s\n", "Especializada.");

                fprintf(c, "        Descricao: %s - %s.\n", chama_p->descricao, chama_p->localidade);
                fprintf(c, "        Policiais:\n");

                while(pm != NULL){

                    if(strcmp(pm->cod_viat, chama_p->cod) == 0)
                        fprintf(c, "            - %s;\n", pm->nome_guerra);
                    pm = pm->prox;
                }

                fprintf(c, "        Presos:\n");

                while(p != NULL){

                    if(p->chamada == chama_p)
                        fprintf(c, "            - %s, %s;\n", p->nome, p->cpf);
                    p = p->prox;
                }

                printf("\n");
            }

            chama_p = chama_p->prox;
        } 

        pm = policiais;
        p = pessoas;

        while(chama_np != NULL){
            if(chama_np->concluida){

                fprintf(c, "%s", "       Tipo Policia: ");
                (chama_np->t_pol == 1) ? fprintf(c, "%s\n", "Regular."): fprintf(c, "%s\n", "Especializada.");

                fprintf(c, "        Descricao: %s - %s.\n", chama_np->descricao, chama_np->localidade);
                fprintf(c, "        Policiais:\n");

                while(pm != NULL){

                    if(strcmp(pm->cod_viat, chama_np->cod) == 0)
                        fprintf(c, "            - %s;\n", pm->nome_guerra);
                    pm = pm->prox;
                }

                fprintf(c, "        Presos:\n");

                while(p != NULL){

                    if(p->chamada == chama_np)
                        fprintf(c, "            - %s, %s;\n", p->nome, p->cpf);
                    p = p->prox;
                }

                printf("\n");
            }

            chama_np = chama_np->prox;
        }

        fclose(c);
    }

    printf("Dados salvos com sucesso!");

}

//Função responsável por verificar o login do comandante geral
void comand_geral(policia *&policiais, pessoa *&pessoas, chamada *&chamadas_p, chamada *&chamadas_np){

    char nome_guerra[MAX+1], senha[MAX + 1];
    policia *comandante = NULL;

    printf("\n====== SPM Comandante Geral ======\n");

    printf("\nNome Guerra: ");
    scanf("%s", nome_guerra);

    printf("\nSenha: ");
    scanf("%s", senha);

    comandante = verifica_login(policiais, nome_guerra, senha);

    if(comandante != NULL){
        if (strcmp(comandante->cargo, "Comandante Geral") == 0){
            printf("Gerando ofício...\n");
            oficio_ocorrencia(chamadas_p, chamadas_np, pessoas, policiais);
        }else
            printf("patente inválida, digite novamente\n");
    }else
        printf("Erro login, digite novamente\n");
}