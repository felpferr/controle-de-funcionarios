#ifndef FUNCIONARIO_C_INCLUDED
#define FUNCIONARIO_C_INCLUDED

#include "general.h"

typedef struct{
    long id, id_depatamento;
    unsigned int Numero;
    char matricula[10], nome[60], dataNascimento[11], CPF[12], rua[40],
    bairro[30], complemento[30], cidade[40], UF[3], CEP[9], email[40];
    float salario;

    /*Chave Primária: id.*/
    /*Chave extrangeira: id_departamento.*/
}TFuncionario;

int cadastroFuncionario(FILE *,FILE *,FILE *,FILE *);/*criar uma função de pesquisa de funcionário ou adaptar a função de consulta.*/
int consultaFuncionario(FILE *,FILE *,char []);/*Nesta função deverá ocorrer uma pesquisa geral no arquivo do campo matrícula
(para verificar a sua existência ou não) no momento em que o usuário fornecer uma matrícula para cadastro.*/
void salvaDadosFunc(FILE *,TFuncionario);
int gerarFolhaPagamento(FILE *);
void getMatricula(char []);
int verificaMatricula(FILE *,char []);

#endif // FUNCIONARIO_C_INCLUDED
