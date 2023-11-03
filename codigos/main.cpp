#include "spm_functions.h"

int main(){
    viatura *carros = NULL;
    policia *policiais = NULL;
    pessoa *pessoas = NULL;
    char word[MAX + 1];

    scanf("%s", word);

    criptografar(word);

    printf("%s \n", word);

    return 0;
}