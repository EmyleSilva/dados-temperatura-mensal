#ifndef RELATORIOS_H_INCLUDED
#define RELATORIOS_H_INCLUDED
#define INDICE_MAIOR 0
#define INDICE_MENOR 1

typedef struct temp{
    int mes;
    int dia;
    float temp_max;
    float temp_min;
}Temp;

/*
** A função lê o arquivo com os dados, e os armazena
** na struct de temperatura
*/
Temp* recuperarDados(char *nomeArq, Temp *t, int *indice_t);

/*
** Define a string do mês correspondente ao recuperado do arquivo
*/
char *recuperaMes(int mes);

/*
** Calcula as médias das temperaturas
*/
float* calcularMediasTemp(Temp *t, float *mediaMes, int indice_t);

/*
** Busca a maior e a menor temperatura
*/
float* maiorMenorTemp(Temp *t, int indice_t);

/*
** Gera o relatório final
*/
void criaRelatorio(char *mes, int indice_t, float *medias, float mediaGeral, float *maiorMenor);


#endif // RELATORIOS_H_INCLUDED
