#include "spm_functions.h"

int main(){
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;
    chamada *chamadas = NULL;

    iniciar_sistema(pessoas, carros, policiais);

    viatura_login(carros, policiais);

    encerra_sistema(pessoas, carros, policiais);

    return 0;
}