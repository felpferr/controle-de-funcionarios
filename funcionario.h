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

typedef struct{
    long id_funcionario,id_departamento;
    char data[11];

    /*Chave Primária: id_funcionario, id_departamento, data.*/
    /*Chaves extrangeiras: id_funcionario, id_departamento.*/
}HistoricoFuncionario;

typedef struct{
    long id_funcionario;
    float salario;
    unsigned short int mes,ano;

    /*Chave Primária: id_funcionario, ano, mes.*/
    /*Chave Extrangeira: id_funcionario.*/
}HistoricoSalario;

int cadastroFuncionario(FILE *);/*criar uma função de pesquisa de funcionário ou adaptar a função de consulta.*/
int consultaFuncionario(FILE *,char []);/*Nesta função deverá ocorrer uma pesquisa geral no arquivo do campo matrícula
(para verificar a sua existência ou não) no momento em que o usuário fornecer uma matrícula para cadastro.*/
int alterarFuncionario();
int alterarSalario();
int gerarFolhaPagamento();
int alterarDepartamentoFunc();
int alterarGerenteDep();
int geraHistoricoPeriodo();

#endif // FUNCIONARIO_C_INCLUDED
