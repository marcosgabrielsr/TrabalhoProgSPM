#include "spm_functions.h"

int main(){
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;
    chamada *chamadas = NULL;

    menu_copom(chamadas);

    while(chamadas != NULL) remove_chamada(chamadas);
    
    return 0;
}