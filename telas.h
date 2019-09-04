#ifndef TELAS_H_INCLUDED
#define TELAS_H_INCLUDED

#include "general.h"
#include "funcionario.h"
#include "departamento.h"
#include <stdio.h>

void inicio();
int telaCadastros(FILE *,FILE *,FILE *,FILE *, TDepartamento *, TFuncionario *);
int telaAlteracoes(FILE *,FILE *, TDepartamento *, TFuncionario *);
int telaConsulta(FILE *, FILE *, TDepartamento *, TFuncionario *, HistoricoDepartamento *, HistoricoFuncionario *, HistoricoSalario *);

#endif // TELAS_H_INCLUDED
