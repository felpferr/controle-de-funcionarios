#ifndef DEPARTAMENTO_H_INCLUDED
#define DEPARTAMENTO_H_INCLUDED

#include <ctype.h>

typedef struct{
    long id, id_gerente;
    char nome[40], sigla[10];
    unsigned short int Ramal;

    /*Chave Primária: id.*/
    /*Chave Estrangeira: id_gerente.*/
}TDepartamento;

///TESTAR A VERIFICAÇÃO DE RAMAL.
int cadastroDepartamento(FILE *,FILE *,FILE *);
int relatorioFuncionario(FILE *,FILE *);
int dadosDosGerentes(FILE *,FILE *);
void salvaDadosDep(TDepartamento, FILE *);
int verificaRamal(char []);

#endif // DEPARTAMENTO_H_INCLUDED
