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
        printf("\nNenhum há nenhum funcionário cadastrado no momento!!");
        return 0;
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
            break;
        }
    }

    ///Buscando o id do funcionário correspondente ao encontrado na busca anterior atráves da matrícula.
    while(fread(&hs,sizeof(hs),1,fhs) == 1){
        if(hs.id_funcionario == tf.id){
            hs.salario = tf.salario;
            break;
        }
    }

    /*Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo,
      neste caso é sobrescrito o registro atual do arquivo pelo registro recém modificado.*/
    fseek(f,0,SEEK_CUR);
    fwrite(&tf,sizeof(tf),1,f);

    /*Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo,
      neste caso é sobrescrito o registro atual do arquivo pelo registro recém modificado.*/
    fseek(fhs,0,SEEK_CUR);
    fwrite(&hs,sizeof(hs),1,fhs);

    return 1;
}

int alterarDepartamentoFunc(){

}

int alterarGerenteDep(){

}
