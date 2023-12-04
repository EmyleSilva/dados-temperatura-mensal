/*
** O programa tem como finalidade ler um arquivo com dados
** relacionados a temperatura extraidos por uma estação
** metereológica. A partir disso, gera um relatório contendo
** as medias de cada dia do mês, a media geral, e a maior e
** menor temperatura.
**
** Autora: Emyle Silva
** Última atualização: 03/12/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"

int main()
{
    Temp *t = (Temp *)malloc(sizeof(Temp));
    char nomeArq[] = "temperaturas.dat";
    int indice_t = 0;
    t = recuperarDados(nomeArq, t, &indice_t);

    float mediaMes = 0.0;
    float *medias;
    float *maiorMenor;
    char *mes;

    mes = recuperaMes(t[0].mes);
    medias = calcularMediasTemp(t, &mediaMes, indice_t);
    maiorMenor = maiorMenorTemp(t, indice_t);

    criaRelatorio(mes, indice_t, medias, mediaMes, maiorMenor);
    printf("\n\n\tRelatório criado com sucesso!\n\n");

    free(t);
    free(medias);
    free(maiorMenor);
    return 0;
}
