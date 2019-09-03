#ifndef DEPARTAMENTO_H_INCLUDED
#define DEPARTAMENTO_H_INCLUDED

typedef struct{
    long id, id_gerente;
    char nome[40], sigla[10];
    unsigned short int Ramal;

    /*Chave Primária: id.*/
    /*Chave Estrangeira: id_gerente.*/
}TDepartamento;

typedef struct{
    long id_departamento, id_gerente;
    char data[11];

    /*Chave Primária: id_departamento, id_gerente, data.*/
    /*Chaves Estrangeiras: id_funcionario, id_departamento.*/
}HistoricoDepartamento;

int cadastroDepartamento(FILE *,FILE *);
int relatorioFuncionario(FILE *,FILE *);
int dadosDosGerentes();
int buscaId(FILE *,int);
void salvaDadosDep(TDepartamento, FILE *);

#endif // DEPARTAMENTO_H_INCLUDED
