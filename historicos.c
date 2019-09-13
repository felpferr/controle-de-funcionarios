#include <stdio.h>
#include <string.h>
#include "general.h"
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"

int geraHistoricoPeriodo(FILE *ff, FILE *fhs){
    TFuncionario tf;
    HistoricoSalario hs;
    geral gInicial,gFinal;
    char mat[10],dInicial[11]/*Usado para verificar se � uma data v�lida.*/,dFinal[11]/*Usado para verificar se � uma data v�lida.*/;

    if(arquivoVazio(ff) == 0){
        printf("\nN�o h� funcion�rios cadastrados no momento.\n");
        return -1;
    }

    do{
        limpaTela();

        getMatricula(mat);
        removeBarraN(mat);

        if(pesquisaMat(mat,ff) == 0){
            do{
                printf("\nN�mero de Matr�cula inexistente. Forne�a um v�lido:");
                getMatricula(mat);
                removeBarraN(mat);
            }while(pesquisaMat(mat,ff) == 0);
        }

        ///Buscando o id do funcion�rio que possui a matr�cula fornecida.
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(strcmp(mat,tf.matricula) == 0)
                break;
        }

        ///Coletando o intervalo de datas do usu�rio.
        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a a data inicial:\n");
            strcpy(gInicial.dia,"01");///Colocando um valor default para o dia para fazer a pesquisa.
            setbuf(stdin,NULL);
            printf("\nM�s: ");
            fgets(gInicial.mes,3,stdin);
            setbuf(stdin,NULL);
            printf("\nAno: ");
            fgets(gInicial.ano,5,stdin);
            setbuf(stdin,NULL);

            sprintf(dInicial,"%s/%s/%s",gInicial.dia,gInicial.mes,gInicial.ano);
        }while(validaData(dInicial) == 0);

        ///Coletando o intervalo de datas do usu�rio.
        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a a data Final:\n");
            strcpy(gFinal.dia,"28");///Colocando um valor default para o dia para fazer a pesquisa.
            setbuf(stdin,NULL);
            printf("\nM�s: ");
            fgets(gFinal.mes,3,stdin);
            setbuf(stdin,NULL);
            printf("\nAno: ");
            fgets(gFinal.ano,5,stdin);
            setbuf(stdin,NULL);

            sprintf(dFinal,"%s/%s/%s",gFinal.dia,gFinal.mes,gFinal.ano);
        }while(validaData(dInicial) == 0);

        if(  ((int)gFinal.mes < (int)gInicial.mes) || ((int)gFinal.ano < (int)gInicial.ano)){
            printf("\nPer�odo inv�lido.");
            do{
                ///Coletando o intervalo de datas do usu�rio.
                do{
                    setbuf(stdin,NULL);
                    printf("\n* Forne�a a data inicial:\n");
                    strcpy(gInicial.dia,"01");///Colocando um valor default para o dia para fazer a pesquisa.
                    setbuf(stdin,NULL);
                    printf("\nM�s: ");
                    fgets(gInicial.mes,3,stdin);
                    setbuf(stdin,NULL);
                    printf("\nAno: ");
                    fgets(gInicial.ano,5,stdin);
                    setbuf(stdin,NULL);

                    sprintf(dInicial,"%s/%s/%s",gInicial.dia,gInicial.mes,gInicial.ano);
                }while(validaData(dInicial) == 0);

                ///Coletando o intervalo de datas do usu�rio.
                do{
                    setbuf(stdin,NULL);
                    printf("\n* Forne�a a data Final:\n");
                    strcpy(gFinal.dia,"28");///Colocando um valor default para o dia para fazer a pesquisa.
                    setbuf(stdin,NULL);
                    printf("\nM�s: ");
                    fgets(gFinal.mes,3,stdin);
                    setbuf(stdin,NULL);
                    printf("\nAno: ");
                    fgets(gFinal.ano,5,stdin);
                    setbuf(stdin,NULL);

                    sprintf(dFinal,"%s/%s/%s",gFinal.dia,gFinal.mes,gFinal.ano);
                }while(validaData(dInicial) == 0);
            }while(((int)gFinal.mes < (int)gInicial.mes) || ((int)gFinal.ano < (int)gInicial.ano));
        }

        while(fread(&hs,sizeof(hs),1,fhs) == 1){
            if(hs.id_funcionario == tf.id){
                ;
            }
        }

    }while(coletaOpcao() == 1);

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
