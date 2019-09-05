#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"


int alterarFuncionario(){

}

int alterarSalario(FILE *ff,FILE *fhs){
    TFuncionario tf;
    HistoricoSalario hs;
    char mat[10];

    fseek(ff,0,SEEK_SET);
    fseek(fhs,0,SEEK_SET);

    if(arquivoVazio(ff) == 0){
        printf("\nNenhum h� nenhum funcion�rio cadastrado no momento!!");
        return 0;
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
            break;
        }
    }

    ///Buscando o id do funcion�rio correspondente ao encontrado na busca anterior atr�ves da matr�cula.
    while(fread(&hs,sizeof(hs),1,fhs) == 1){
        if(hs.id_funcionario == tf.id){
            hs.salario = tf.salario;
            break;
        }
    }

    /*N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo,
      neste caso � sobrescrito o registro atual do arquivo pelo registro rec�m modificado.*/
    fseek(f,0,SEEK_CUR);
    fwrite(&tf,sizeof(tf),1,f);

    /*N�o � utilizada a fun��o salvaDadosFunc pois ela salva novos registros no final do arquivo,
      neste caso � sobrescrito o registro atual do arquivo pelo registro rec�m modificado.*/
    fseek(fhs,0,SEEK_CUR);
    fwrite(&hs,sizeof(hs),1,fhs);

    return 1;
}

int alterarDepartamentoFunc(){

}

int alterarGerenteDep(){

}
