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
        printf("\nNenhum há nenhum funcionário cadastrado no momento meu consagrado!!");
        return 1;
    }

    getMatricula(mat);
    if(pesquisaMat(mat,ff) == 0){
        do{
            printf("\nNúmero de Matrícula inexistente. Forneça um válido:");
            getMatricula(mat);
        }while(pesquisaMat(mat,ff) == 0);
    }

    ///Buscando primeiramente no arquivo de funcionários o registro que possui a matrícula fornecida
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 1){
            do{
                setbuf(stdin,NULL);
                printf("Forneça o salário do funcionário:\n");
                scanf("%f",&tf.salario);
                if(tf.salario <= 0.2f)
                    printf("\nValor Inválido.");
            }while(tf.salario <= 0.2f);
            fseek(ff,0,SEEK_CUR);///Posicionando o arquivo na posição referente ao registro do funcionário para não criar réplicas de dados.
            break;
        }
    }

    hs.id_funcionario = tf.id;
    hs.salario = tf.salario;

    data = localtime(&dataAtual);
    hs.mes = data.tm_mon++;
    hs.ano = data.tm_year;

    /*Salvando a alteração no arquivo de funcionários.
      OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
      (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
      arquivo pelo registro recém modificado.*/
    fwrite(&tf,sizeof(tf),1,f);

    ///Salvando a alteração no arquivo de histórico de salário do funcionário.
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
        printf("\nNenhum há nenhum funcionário cadastrado no momento!!");
        return 1;
    }

    if(arquivoVazio(fd) == 0){
        limpaTela();
        printf("\nNão há departamentos cadastrados.");
        return 1;
    }

    do{
        limpaTela();
        getMatricula(matricula);

        if(verificaMatricula(ff,matricula) == 0)
            do{
                printf("\nNúmero de matrícula repetido.");
                getMatricula(matricula);
            }while(verificaMatricula(ff,matricula) == 0);

        ///Posicionando o arquivo na posição referente ao registro do funcionário para não criar réplicas de dados.
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(strcmp(matricula,tf.matricula) == 1){
                fseek(ff,0,SEEK_CUR);
                break;
            }
        }

        printf("\nForneça o id do novo departamento:");
        scanf("%li",&tf.id_depatamento);
        if(buscaId(fd,2,tf.id_depatamento) == 0){
            do{
                printf("\nID de departamento inexistente.Por favor meu consagrado, forneça um válido:\n");
                scanf("%li",&tf.id_depatamento);
            }while(buscaId(fd,2,tf.id_depatamento) == 0);
        }

        data = localtime(&dataAtual);

        ///Adicionando os novos dados deste funcionário em um registro.
        hf.id_funcionario = tf.id;
        hf.id_departamento = tf.id_depatamento;
        sprintf(hf.data,"%s/%s/%s",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COERÇÃO DE TIPO NÃO ESTÁ GERANDO INCONSISTÊNCIA

        /*Salvando a alteração no arquivo de funcionários.
          OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
          (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
          arquivo pelo registro recém modificado.*/
        fwrite(&tf,sizeof(tf),1,ff);

        ///Salvando a alteração no arquivo de histórico do funcionário.
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
        printf("Não há departamentos cadastrados no momento!!");
        return 1;
    }

    do{
        limpaTela();
        printf("Forneça o ID do departamento:\n");
        scanf("%li",&idDep);
        ///Verificando se o ID fornecido existe no arquivo de departamento.
        if(buscaId(fd,2,idDep) == 0){
            do{
                printf("\nID inexistente, forneça um válido:\n");
                scanf("%li",&idDep);
            }while(buscaId(fd,2,idDep) == 0);
        }

        printf("\nForneça o ID do novo gerente:");
        scanf("%li",&novoId);
        ///Verificando se o ID fornecido existe no arquivo de funcionários.
        if(buscaId(ff,1,novoId) == 0){
            do{
                printf("\nID inexistente, forneça um válido:\n");
                scanf("%li",&novoId);
            }while(buscaId(ff,1,novoId) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == idDep){
                td.id_gerente = novoId;
                fseek(fd,0,SEEK_CUR);///Posicionando o arquivo na posição referente ao registro do departamento para não criar réplicas de dados.
                break;
            }
        }

        hd.id_gerente = novoId;
        hd.id_departamento = td.id;
        data = localtime(&dataAtual);
        sprintf(hd.data,"%s/%s/%s",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COERÇÃO DE TIPO NÃO ESTÁ GERANDO INCONSISTÊNCIA

        ///Salvando a alteração no histórico do departamento.
        salvaHistoricoDep(fhd,hd);

        /*Salvando a alteração no arquivo de departamento.
          OBS: Não é utilizada a função salvaDadosDep pois ela salva novos registros no final do arquivo
          (criando réplicas dos dados de um departamento), neste caso é sobrescrito  o  registro atual  do
          arquivo pelo registro recém modificado.*/
        fwrite(&td,sizeof(td),1,fd);

    }while(coletaOpcao() == 1);

    return -1;
}
