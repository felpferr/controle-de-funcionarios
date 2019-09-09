#ifndef HISTORICOS_H_INCLUDED
#define HISTORICOS_H_INCLUDED

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

typedef struct{
    long id_departamento, id_gerente;
    char data[11];

    /*Chave Primária: id_departamento, id_gerente, data.*/
    /*Chaves Estrangeiras: id_funcionario, id_departamento.*/
}HistoricoDepartamento;

int geraHistoricoPeriodo(FILE *, FILE *);///Incompleta;
void salvaHistoricoFunc(FILE *, HistoricoFuncionario);
void salvaHistoricoDep(FILE *, HistoricoDepartamento);
void salvaHistoricoSalario(FILE *, HistoricoSalario);
#endif // HISTORICOS_H_INCLUDED
