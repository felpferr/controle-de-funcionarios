#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char dia[3],mes[3],ano[5];
}geral;

struct tm {
    unsigned short int tm_sec; //representa os segundos de 0 a 59
    unsigned short int tm_min; //representa os minutos de 0 a 59
    unsigned short int tm_hour; //representa as horas de 0 a 24
    unsigned short int tm_mday: //dia do mês de 1 a 31
    unsigned short int tm_mon; //representa os meses do ano de 0 a 11
    unsigned short int tm_year; //representa o ano a partir de 1900
    unsigned short int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
    unsigned short int tm_yday; // dia do ano de 1 a 365
    unsigned short int tm_isdst; //indica horário de verão se for diferente de zero
};

void sair();
void limpaTela();
int openFile(FILE *,char [],char []);
int removeBarraN(char []);
int pesquisaMat(char [],FILE *);
int geraID(long);
long verificaUltimoID(FILE *,int);

///VERIFICAR SE FUNCIONA...
int validaData(char data[]);

///VERIFICAR SE FUNCIONA...
int validaCPF(char []);
int coletaOpcao();
int arquivoVazio(FILE *);
long buscaId(FILE *,int ,long );

#endif // GENERAL_H_INCLUDED
