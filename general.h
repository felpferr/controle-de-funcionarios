#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char dia[3],mes[3],ano[5];
}geral;

void sair();
void limpaTela();
int openFile(FILE *,char [],char []);
int removeBarraN(char []);
int pesquisaMat(char [],FILE *);
long geraID(long);
long verificaUltimoID(FILE *,int);

///VERIFICAR SE FUNCIONA...
int validaData(char data[]);

///VERIFICAR SE FUNCIONA...
int validaCPF(char []);
int coletaOpcao();
int arquivoVazio(FILE *);
long buscaId(FILE *,int ,long );
void promptUniversal();
int msg01();
int msg02();
int msg03();
int msg04();
int msg05();
int msg06();

#endif // GENERAL_H_INCLUDED
