#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relatorio.h"

//-------------------------------------------------
// A função recebe o mês (valor inteiro) e retorna
// a string que representa o mês correspondente
//-------------------------------------------------
char* recuperaMes(int mes){
    char *meses[] = {"", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
                      "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    if(mes >= 1 && mes <= 12){
        return meses[mes];
    }else{
        printf("Erro Interno: Mês inválido");
        exit(1);
    }
}

//--------------------------------------------------
// Lê os dados do arquivo, e armazena as informações
// na struct de temperaturas
//--------------------------------------------------
Temp* recuperarDados(char *nomeArq, Temp *t, int *indice_t){
    char *linha = (char *)malloc(25 * sizeof(char));
    char linha2[4][10];
    char *pttok;
    FILE *fp;

    if((fp = fopen(nomeArq, "r")) == NULL){
        printf("Erro Interno: Não foi possivel abrir o arquivo para leitura.");
        exit(1);
    }

    while(fgets(linha, 25, fp)){
        int cont = 0;
        pttok = strtok(linha, ", ");
        while(pttok){
            strcpy(linha2[cont], pttok);
            cont++;
            pttok = strtok(NULL, ", ");
        }
        t[(*indice_t)].temp_min = atof(linha2[--cont]);
        t[(*indice_t)].temp_max = atof(linha2[--cont]);
        t[(*indice_t)].dia = atoi(linha2[--cont]);
        t[(*indice_t)].mes = atoi(linha2[--cont]);

        (*indice_t)++;
        t = (Temp *)realloc(t, ((*indice_t)+1) * sizeof(Temp));
    }

    fclose(fp);
    free(linha);

    return t;
}

//--------------------------------------------------
// Calcula as médias mensais, e as armazena em um
// vetor. A média geral do mês também é calculada.
// A função retorna o vetor com as médias diárias.
//--------------------------------------------------
float* calcularMediasTemp(Temp *t, float *mediaMes, int indice_t){
    float *medias = (float *)malloc(indice_t * sizeof(float));

    for(int i = 0; i < indice_t; i++){
        medias[i] = (t[i].temp_min + t[i].temp_max) / 2;
        (*mediaMes) += medias[i];
    }
    (*mediaMes) /= indice_t;

    return medias;
}

//--------------------------------------------------
// Compara as temperaturas e retorna um vetor com
// os a maior e menor temperatura.
//--------------------------------------------------
float *maiorMenorTemp(Temp *t, int indice_t){
    float *compara = (float *)malloc(2 * sizeof(float));
    float maior, menor;


    if(t[0].temp_min > t[0].temp_max){
        maior = t[0].temp_min;
        menor = t[0].temp_max;
    }else{
        maior = t[0].temp_max;
        menor = t[0].temp_min;
    }

    for(int i = 1; i < indice_t; i++){
        if(t[i].temp_min > maior) maior = t[i].temp_min;
        else if(t[i].temp_min < menor) menor = t[i].temp_min;

        if(t[i].temp_max > maior) maior = t[i].temp_max;
        else if(t[i].temp_max < menor) menor = t[i].temp_max;
    }

    compara[INDICE_MAIOR] = maior;
    compara[INDICE_MENOR] = menor;

    return compara;
}

//--------------------------------------------------
// Gera o relatório final, com as medias, e a maior
// e menor temperatura.
//--------------------------------------------------
void criaRelatorio(char *mes, int indice_t, float *medias, float mediaGeral, float *maiorMenor){
    FILE *fp;
    if((fp = fopen("relatório.txt", "w")) == NULL){
        printf("Erro Interno: Não foi possivel criar o relatório.");
        exit(1);
    }

    fprintf(fp, "Prezada comunidade,\n\n");
    fprintf(fp, "Informamos que no mês de %s tivemos as seguintes temperaturas médias:\n", mes);
    for(int i = 0; i < indice_t; i++){
        fprintf(fp, "Dia %d: %.2f\n", i+1, medias[i]);
    }
    fprintf(fp, "\nSendo que a temperatura média do mês ficou em %.2f.\n", mediaGeral);
    fprintf(fp, "A maior temperatura registrada foi de %.2f e a menor temperatura foi de %.2f.\n\n",
            maiorMenor[INDICE_MAIOR], maiorMenor[INDICE_MENOR]);
    fprintf(fp, "Atenciosamente,\n\nCentro de Metrologia Metrologic");

    fclose(fp);
}
