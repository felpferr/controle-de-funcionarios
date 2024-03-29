#include <stdio.h>
#include "listagens.h"
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "general.h"

int l_Funcionarios(FILE *ff){
    TFuncionario tf;

    if(arquivoVazio(ff) == 0){
        return msg02();
    }
    fseek(ff,0,SEEK_SET);
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        msg04();
        printf("--------------------------------------------------------------------------------------------");
        printf("\nNome: %s\nMatr�cula: %s\nID: %li\nData de Nascimento: %s\nCPF: %s\nID Departamento: %li\
                \nSal�rio: %.2f\nRua: %s\nBairro: %s\nN�mero: %d\nComplemento: %s\nCidade: %s\nUF: %s\nCEP: %s\nEMAIL: %s\n\n",
                tf.nome,tf.matricula,tf.id,tf.dataNascimento,tf.CPF,tf.id,tf.salario,tf.rua,tf.bairro,tf.Numero,tf.complemento,tf.cidade,
                tf.UF,tf.CEP,tf.email);
    }
    return 1;
}

int l_Departamentos(FILE *fd){
    TDepartamento td;

    if(arquivoVazio(fd) == 0)
        return msg03();
    fseek(fd,0,SEEK_SET);
    while(fread(&td,sizeof(td),1,fd)){
        msg05();
        printf("--------------------------------------------------------------------------------------------");
        printf("\nNome: %s\nSigla: %s\nID: %li\nID do Gerente: %li\nRamal: %hu\n\n",td.nome,td.sigla,td.id,td.id_gerente,td.Ramal);
    }
    return 1;
}

int l_HistoricoSalario(FILE *fhs){
    HistoricoSalario hs;

    if(arquivoVazio(fhs) == 0)
        return msg02();

    fseek(fhs,0,SEEK_SET);
    while(fread(&hs,sizeof(hs),1,fhs) == 1){
        msg07();
        printf("--------------------------------------------------------------------------------------------");
        printf("\nID do Funcion�rio: %li\nSal�rio: %.2f\nM�s: %hu\nAno: %hu\n\n",hs.id_funcionario,hs.salario,hs.mes,hs.ano);
    }
    return 1;
}

int l_HistoricoDepartamento(FILE *fhd){
    HistoricoDepartamento hd;

    if(arquivoVazio(fhd) == 0)
        return msg03();
    fseek(fhd,0,SEEK_SET);
    while(fread(&hd,sizeof(hd),1,fhd) == 1){
        msg08();
        printf("--------------------------------------------------------------------------------------------");
        printf("\nID do departamento: %li\nID do Gerente: %li\nData: %s\n\n",hd.id_departamento,hd.id_gerente,hd.data);
    }
    return 1;
}

int l_HistoricoFuncionario(FILE *fhf){
    HistoricoFuncionario hf;

    if(arquivoVazio(fhf) == 0)
        return msg02();

    fseek(fhf,0,SEEK_SET);
    while(fread(&hf,sizeof(hf),1,fhf) == 1){
        msg06();
        printf("--------------------------------------------------------------------------------------------");
        printf("\nID do Funcion�rio: %li\nID do Departamento: %li\nData: %s\n\n",hf.id_funcionario,hf.id_departamento,hf.data);
    }
    return 1;
}
