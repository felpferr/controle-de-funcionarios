#ifndef TELAS_H_INCLUDED
#define TELAS_H_INCLUDED

#include "general.h"

void inicio();
int telaCadastros(geral *, TDepartamento *, TFuncionario *);
int telaAlteracoes(geral *, TDepartamento *, TFuncionario *);
int telaConsulta(geral *, TDepartamento *, TFuncionario *, HistoricoDepartamento *, HistoricoFuncionario *, HistoricoSalario *);

#endif // TELAS_H_INCLUDED
