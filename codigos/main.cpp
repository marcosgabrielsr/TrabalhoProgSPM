//Biblioteca principal que contém todas as funcionalidades do sistema
#include "spm_functions.h"

int main(){
    //Ponteiros para listas simplesmente encadeadas para viaturas, policiais e pessoas
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;

    //Ponteiros para filas de chamadas prioritárias
    chamada *p_begin = NULL;
    chamada *p_end = NULL;

    //Ponteiros para filas de chamadas não prioritárias
    chamada *np_begin = NULL;
    chamada *np_end = NULL;

    //Ponteiro para fila de chamadas de reforços
    chamada *reforco = NULL;
    chamada *end_reforco = NULL;

    iniciar_sistema(pessoas, carros, policiais);

    menu_principal(pessoas, carros, policiais, p_begin, p_end, np_begin, np_end, reforco, end_reforco);

    encerra_sistema(pessoas, carros, policiais, p_begin, p_end, np_begin, np_end);

    return 0;
}