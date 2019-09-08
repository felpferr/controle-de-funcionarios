#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"


int alterarFuncionario(){

}

///INCOMPLETA...
int alterarSalario(FILE *ff,FILE *fhs){
    TFuncionario tf;
    HistoricoSalario hs;
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
    /*Adicionar aqui a data da altera��o ultilizando (strcmp(data,hs.ano/mes);), por�m, n�o
      foi implementada uma fun��o  que  coleta  a  data atual  do  sistema autom�ticamente.
    */


    /*Salvando a altera��o no arquivo de funcion�rios.
      OBS: N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo
      (criando r�plicas dos dados de um funcion�rio), neste caso � sobrescrito  o  registro atual  do
      arquivo pelo registro rec�m modificado.*/
    fwrite(&tf,sizeof(tf),1,f);

    ///Salvando a altera��o no arquivo de hist�rico de sal�rio do funcion�rio.
    salvaHistoricoSalario(fhs,hs);

    return 1;
}

int alterarDepartamentoFunc(FILE *ff,FILE *fd,FILE *fhf){
    TFuncionario tf;
    TDepartamento td;
    HistoricoFuncionario hf;
    char matricula[10];

    if(arquivoVazio(ff) == 0){
        limpaTela();
        printf("\nNenhum h� nenhum funcion�rio cadastrado no momento meu consagrado!!");
        return 1;
    }

    if(arquivoVazio(fd) == 0){
        limpaTela();
        printf("\nN�o h� departamentos cadastrados meu consagrado.");
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

        ///Adicionando os novos dados deste funcion�rio em um registro.
        hf.id_funcionario = tf.id;
        hf.id_departamento = tf.id_depatamento;
        /*Adicionar aqui a data da altera��o ultilizando (strcmp(data,hf.data);), por�m n�o
          foi implementada uma fun��o que coleta  a  data atual do sistema autom�ticamente.
          */

        /*Salvando a altera��o no arquivo de funcion�rios.
          OBS: N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo
          (criando r�plicas dos dados de um funcion�rio), neste caso � sobrescrito  o  registro atual  do
          arquivo pelo registro rec�m modificado.*/
        fwrite(&tf,sizeof(tf),1,ff);

        ///Salvando a altera��o no arquivo de hist�rico do funcion�rio.
        salvaHistoricoFunc(fhf,hf);

    }while(coletaOpcao() == 1);
    return 1;
}

int alterarGerenteDep(){

}
