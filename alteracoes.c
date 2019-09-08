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
    /*Adicionar aqui a data da alteração ultilizando (strcmp(data,hs.ano/mes);), porém, não
      foi implementada uma função  que  coleta  a  data atual  do  sistema automáticamente.
    */


    /*Salvando a alteração no arquivo de funcionários.
      OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
      (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
      arquivo pelo registro recém modificado.*/
    fwrite(&tf,sizeof(tf),1,f);

    ///Salvando a alteração no arquivo de histórico de salário do funcionário.
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
        printf("\nNenhum há nenhum funcionário cadastrado no momento meu consagrado!!");
        return 1;
    }

    if(arquivoVazio(fd) == 0){
        limpaTela();
        printf("\nNão há departamentos cadastrados meu consagrado.");
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

        ///Adicionando os novos dados deste funcionário em um registro.
        hf.id_funcionario = tf.id;
        hf.id_departamento = tf.id_depatamento;
        /*Adicionar aqui a data da alteração ultilizando (strcmp(data,hf.data);), porém não
          foi implementada uma função que coleta  a  data atual do sistema automáticamente.
          */

        /*Salvando a alteração no arquivo de funcionários.
          OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
          (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
          arquivo pelo registro recém modificado.*/
        fwrite(&tf,sizeof(tf),1,ff);

        ///Salvando a alteração no arquivo de histórico do funcionário.
        salvaHistoricoFunc(fhf,hf);

    }while(coletaOpcao() == 1);
    return 1;
}

int alterarGerenteDep(){

}
