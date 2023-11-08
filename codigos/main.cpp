#include "spm_functions.h"

int main(){
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;
    chamada *begin = NULL;
    chamada *end = NULL;

    iniciar_sistema(pessoas, carros, policiais);

    menu_principal(pessoas, carros, policiais, begin, end);

    encerra_sistema(pessoas, carros, policiais, begin, end);

    return 0;
}