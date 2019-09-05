#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char dia[3],mes[3],ano[5];
}geral;

void sair();
void limpaTela();
int openFile(FILE *,char [],char []);
int removeBarraN(char []);
int pesquisaMat(char [],FILE *);
int geraID(long);
long verificaUltimoID(FILE *,int);
int validaData(char data[]);
int validaCPF(char []);
int coletaOpcao();
int arquivoVazio(FILE *);
long buscaId(FILE *,int ,long );

#endif // GENERAL_H_INCLUDED
