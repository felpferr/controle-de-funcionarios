#include <stdio.h>
#include <string.h>
#include "historicos.h"

int geraHistoricoPeriodo(){

    return -1;
}

void salvaHistoricoFunc(FILE *fhf,HistoricoFuncionario hf){
    fseek(fhf,0,SEEK_END);
    fwrite(&hf,sizeof(hf),1,fhf);
}

void salvaHistoricoDep(FILE *fhd, HistoricoDepartamento hd){
    fseek(fhd,0,SEEK_END);
    fwrite(&hd,sizeof(hd),1,fhd);
}

void salvaHistoricoSalario(FILE *fhs, HistoricoSalario hs){
    fseek(fhs,0,SEEK_END);
    fwrite(&hs,sizeof(hs),1,fhs);
}
