#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "general.h"

///Fazer depois uma função para printar na tela uma mensagem de erro.

int cadastroFuncionario(FILE *ff,FILE *fd,FILE *fhf,FILE *fhs){
    TFuncionario tf;
    HistoricoFuncionario hf;
    geral g;
    int opcao;

    do{
        limpaTela();
        do{
            setbuf(stdin,NULL);
            printf("* Forneça o número de matrícula do funcionário:\n");
            fgets(tf.matricula,10,stdin);
        }while(pesquisaMat(tf.matricula,f) == 1);

        /*Garante que o campo nome do arquivo de funcionário não seja vazio.*/
        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça o nome do funcionário:\n");
            fgets(tf.nome,60,stdin);
        }while(strlen(tf.nome) == 0);

        tf.id = geraID(verificaUltimoID(f,1));
        hf.id_funcionario = tf.id;

        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça a data de nascimento:\n");
            printf("Dia: ");
            fgets(g.dia,3,stdin);
            setbuf(stdin,NULL);
            printf("Mês: ");
            fgets(g.mes,3,stdin);
            setbuf(stdin,NULL);
            printf("Ano: ");
            fgets(g.ano,5,stdin);
            setbuf(stdin,NULL);

            sprintf(tf.dataNascimento,"%s/%s/%s",g.dia,g.mes,g.ano);
        }while(validaData(tf.dataNascimento)==0);

        sprintf(hf.data,"%s/%s/%s",g.dia,g.mes,g.ano);

        do{
            setbuf(stdin,NULL);
            printf("* Forneça o CPF:\n");
            fgets(tf.CPF,12,stdin);
        }while(validaCPF(tf.CPF) == 0);

        if(arquivoVazio(fd) == 0){
            continue;
        }
        else{
            printf("\nForneça o ID de um departamento para adicionar este funcionário ao departamento:\n");
            scanf("%li",&tf.id_depatamento);

        }

        do{
            setbuf(stdin,NULL);
            printf("Forneça o salário do funcionário:\n");
            scanf("%f",&tf.salario);
            if(tf.salario < 0.2f)
                printf("\nValor Inválido.");
        }while(tf.salario <= 0.2f);

        setbuf(stdin,NULL);
        printf("\nForneça a rua:\n");
        fgets(tf.rua,40,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça o bairro:\n");
        fgets(tf.bairro,30,stdin);

        do{
            setbuf(stdin,NULL);
            printf("\nForneça o número da casa ou apartamento:\n");
            scanf("%d",&tf.Numero);
            if(tf.Numero < 0)
                printf("\nValor Inválido.");
        }while(tf.Numero < 0);

        setbuf(stdin,NULL);
        printf("\nForneça um complemento:\n");
        fgets(tf.complemento,30,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça a cidade:\n");
        fgets(tf.cidade,40,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça a UF:\n");
        fgets(tf.UF,3,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça o CEP:\n");
        fgets(tf.CEP,9,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça um email:\n");
        fgets(tf.email,40,stdin);

        salvaDadosFunc(f,tf);
        opcao = coletaOpcao();
    }while(opcao == 1);

    return 1;
}

int consultaFuncionario(FILE *ff,FILE *fd, char mat[]){
    TFuncionario tf;
    TDepartamento td;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 1){
            while(fread(&td,sizeof(td),1,fd) == 1)
                if(tf.id_depatamento == td.id)
                    printf("%s",td.nome);
            printf("\nNome: %s\nMatrícula: %s\nID: %li\nData de Nascimento: %s\nCPF: %s\nID Departamento: %li\
                   \nSalário: %f\nRua: %s\nBairro: %s\nNúmero: %d\nComplemento: %s\nCidade: %s\nUF: %s\nCEP: %s\nEMAIL: %s",tf.nome,tf.matricula,tf.id,tf.dataNascimento,tf.CPF,td.id,tf.salario,tf.rua,tf.bairro,tf.Numero,tf.complemento,tf.cidade,
                   tf.UF,tf.CEP,tf.email);
            break;
        }
    }

    return 1;
}

void salvaDadosFunc(FILE *f, TFuncionario tf){
    fseek(f,0,SEEK_END);
    fwrite(&tf,sizeof(tf),1,f);
}

char coletaMatricula(){
    char mat[10];

    printf("\nForneça um número de matrícula:\n");
    fgets(mat,10,stdin);
    return mat;
}
