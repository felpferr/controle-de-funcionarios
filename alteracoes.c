#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"
#include "general.h"


int alterarFuncionario(){

}

int alterarSalario(FILE *ff,FILE *fhs){
    TFuncionario tf;
    HistoricoSalario hs;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char mat[10];

    fseek(ff,0,SEEK_SET);
    fseek(fhs,0,SEEK_SET);

    if(arquivoVazio(ff) == 0){
        limpaTela();
        printf("\nNenhum h� nenhum funcion�rio cadastrado no momento meu consagrado!!");
        return 1;
    }

    getMatricula(mat);
    if(pesquisaMat(mat,ff) == 0){
        do{
            printf("\nN�mero de Matr�cula inexistente. Forne�a um v�lido:");
            getMatricula(mat);
        }while(pesquisaMat(mat,ff) == 0);
    }

    ///Buscando primeiramente no arquivo de funcion�rios o registro que possui a matr�cula fornecida
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 1){
            do{
                setbuf(stdin,NULL);
                printf("Forne�a o sal�rio do funcion�rio:\n");
                scanf("%f",&tf.salario);
                if(tf.salario <= 0.2f)
                    printf("\nValor Inv�lido.");
            }while(tf.salario <= 0.2f);
            fseek(ff,0,SEEK_CUR);///Posicionando o arquivo na posi��o referente ao registro do funcion�rio para n�o criar r�plicas de dados.
            break;
        }
    }

    hs.id_funcionario = tf.id;
    hs.salario = tf.salario;

    data = localtime(&dataAtual);
    hs.mes = data.tm_mon++;
    hs.ano = data.tm_year;

    /*Salvando a altera��o no arquivo de funcion�rios.
      OBS: N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo
      (criando r�plicas dos dados de um funcion�rio), neste caso � sobrescrito  o  registro atual  do
      arquivo pelo registro rec�m modificado.*/
    fwrite(&tf,sizeof(tf),1,f);

    ///Salvando a altera��o no arquivo de hist�rico de sal�rio do funcion�rio.
    salvaHistoricoSalario(fhs,hs);

    return -1;
}

int alterarDepartamentoFunc(FILE *ff,FILE *fd,FILE *fhf){
    TFuncionario tf;
    TDepartamento td;
    HistoricoFuncionario hf;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char matricula[10];

    if(arquivoVazio(ff) == 0){
        limpaTela();
        printf("\nNenhum h� nenhum funcion�rio cadastrado no momento!!");
        return 1;
    }

    if(arquivoVazio(fd) == 0){
        limpaTela();
        printf("\nN�o h� departamentos cadastrados.");
        return 1;
    }

    do{
        limpaTela();
        getMatricula(matricula);

        if(verificaMatricula(ff,matricula) == 0)
            do{
                printf("\nN�mero de matr�cula repetido.");
                getMatricula(matricula);
            }while(verificaMatricula(ff,matricula) == 0);

        ///Posicionando o arquivo na posi��o referente ao registro do funcion�rio para n�o criar r�plicas de dados.
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(strcmp(matricula,tf.matricula) == 1){
                fseek(ff,0,SEEK_CUR);
                break;
            }
        }

        printf("\nForne�a o id do novo departamento:");
        scanf("%li",&tf.id_depatamento);
        if(buscaId(fd,2,tf.id_depatamento) == 0){
            do{
                printf("\nID de departamento inexistente.Por favor meu consagrado, forne�a um v�lido:\n");
                scanf("%li",&tf.id_depatamento);
            }while(buscaId(fd,2,tf.id_depatamento) == 0);
        }

        data = localtime(&dataAtual);

        ///Adicionando os novos dados deste funcion�rio em um registro.
        hf.id_funcionario = tf.id;
        hf.id_departamento = tf.id_depatamento;
        sprintf(hf.data,"%s/%s/%s",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COER��O DE TIPO N�O EST� GERANDO INCONSIST�NCIA

        /*Salvando a altera��o no arquivo de funcion�rios.
          OBS: N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo
          (criando r�plicas dos dados de um funcion�rio), neste caso � sobrescrito  o  registro atual  do
          arquivo pelo registro rec�m modificado.*/
        fwrite(&tf,sizeof(tf),1,ff);

        ///Salvando a altera��o no arquivo de hist�rico do funcion�rio.
        salvaHistoricoFunc(fhf,hf);

    }while(coletaOpcao() == 1);
    return -1;
}

int alterarGerenteDep(FILE *ff,FILE *fd, FILE *fhd){
    TDepartamento td;
    HistoricoDepartamento hd;
    struct tm *data;
    time_t dataAtual = time(NULL);
    long idDep,novoId;


    if(arquivoVazio(fd) == 0){
        printf("N�o h� departamentos cadastrados no momento!!");
        return 1;
    }

    do{
        limpaTela();
        printf("Forne�a o ID do departamento:\n");
        scanf("%li",&idDep);
        ///Verificando se o ID fornecido existe no arquivo de departamento.
        if(buscaId(fd,2,idDep) == 0){
            do{
                printf("\nID inexistente, forne�a um v�lido:\n");
                scanf("%li",&idDep);
            }while(buscaId(fd,2,idDep) == 0);
        }

        printf("\nForne�a o ID do novo gerente:");
        scanf("%li",&novoId);
        ///Verificando se o ID fornecido existe no arquivo de funcion�rios.
        if(buscaId(ff,1,novoId) == 0){
            do{
                printf("\nID inexistente, forne�a um v�lido:\n");
                scanf("%li",&novoId);
            }while(buscaId(ff,1,novoId) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == idDep){
                td.id_gerente = novoId;
                fseek(fd,0,SEEK_CUR);///Posicionando o arquivo na posi��o referente ao registro do departamento para n�o criar r�plicas de dados.
                break;
            }
        }

        hd.id_gerente = novoId;
        hd.id_departamento = td.id;
        data = localtime(&dataAtual);
        sprintf(hd.data,"%s/%s/%s",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COER��O DE TIPO N�O EST� GERANDO INCONSIST�NCIA

        ///Salvando a altera��o no hist�rico do departamento.
        salvaHistoricoDep(fhd,hd);

        /*Salvando a altera��o no arquivo de departamento.
          OBS: N�o � utilizada a fun��o salvaDadosDep pois ela salva novos registros no final do arquivo
          (criando r�plicas dos dados de um departamento), neste caso � sobrescrito  o  registro atual  do
          arquivo pelo registro rec�m modificado.*/
        fwrite(&td,sizeof(td),1,fd);

    }while(coletaOpcao() == 1);

    return -1;
}
