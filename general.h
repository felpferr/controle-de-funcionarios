#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "funcionario.h"

typedef struct{
    char modo[4]/*String que armazena o modo de abertura do arquivo que pretende-se ser aberto.*/,dia[3],mes[3],ano[5];
    long idf=0, idd=0; // Campos usados para poder incrementar os campos id através da função geraID().
    FILE *funcionario, *historicoFun, *historicoSalario, *departamento;
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
void salvaDadosFunc(TFuncionario,FILE *);
int coletaOpcao();
int arquivoVazio(FILE *);

#endif // GENERAL_H_INCLUDED
