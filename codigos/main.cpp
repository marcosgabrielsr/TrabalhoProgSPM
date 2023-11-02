#include "spm_functions.h"

int main(){
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;

    ler_pessoas(pessoas);

    printf_pessoas(pessoas);

    while(pessoas != NULL) remove_pessoa(pessoas);

    if(pessoas != NULL)
        printf("A lista não está vazia\n");

    return 0;
}