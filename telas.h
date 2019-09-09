#ifndef TELAS_H_INCLUDED
#define TELAS_H_INCLUDED

#include "general.h"
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"

void inicio();
int telaCadastros(FILE *,FILE *,FILE *,FILE *,FILE*, TDepartamento *, TFuncionario *);
int telaAlteracoes(FILE *,FILE *,FILE *,FILE *,FILE *, TDepartamento *, TFuncionario *);
int telaConsulta(FILE *, FILE *,FILE *, TDepartamento *, TFuncionario *, HistoricoDepartamento *, HistoricoFuncionario *, HistoricoSalario *);

#endif // TELAS_H_INCLUDED
