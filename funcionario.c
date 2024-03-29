#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "general.h"

int cadastroFuncionario(FILE *ff,FILE *fd,FILE *fhf,FILE *fhs){
    TFuncionario tf;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    geral g;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char uf[4];

    do{
        limpaTela();

        do{
            getMatricula(tf.matricula);
            removeBarraN(tf.matricula);
        }while(verificaMatricula(ff,tf.matricula) == 0);

        /*Garante que o campo nome do arquivo de funcion�rio n�o seja vazio.*/
        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a o nome do funcion�rio:\n");
            fgets(tf.nome,60,stdin);
            setbuf(stdin,NULL);
            removeBarraN(tf.nome);
        }while(strlen(tf.nome) == 0);

        tf.id = geraID(verificaUltimoID(ff,1));

        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a a data de nascimento:\n");
            printf("Dia: ");
            fgets(g.dia,3,stdin);
            setbuf(stdin,NULL);

            setbuf(stdin,NULL);
            promptUniversal();
            printf("\nM�s: ");
            fgets(g.mes,3,stdin);
            setbuf(stdin,NULL);

            setbuf(stdin,NULL);
            promptUniversal();
            printf("\nAno: ");
            fgets(g.ano,6,stdin);
            setbuf(stdin,NULL);

            sprintf(tf.dataNascimento,"%s/%s/%s",g.dia,g.mes,g.ano);
        }while(validaData(tf.dataNascimento)==0);

        sprintf(hf.data,"%s/%s/%s",g.dia,g.mes,g.ano);

        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a o CPF:\n");
            fgets(tf.CPF,12,stdin);
            setbuf(stdin,NULL);
            removeBarraN(tf.CPF);
        }while(validaCPF(tf.CPF) == 0);


        /*Verificando se existe um departamento cadastrado pois, se n�o houver nenhum
          cadastrado n�o � obrigat�rio registrar os funcion�rios  em  um departamento.
        */
        if(arquivoVazio(fd) == 0){
            tf.id_depatamento = 0;
        }
        else{
            printf("\nForne�a o ID de um departamento para adicionar este funcion�rio ao departamento:\n");
            scanf("%li",&tf.id_depatamento);
            setbuf(stdin,NULL);

            if(buscaId(fd,2,tf.id_depatamento) == 0)
                do{
                    printf("\nC�digo de departamento inexistente ou inv�lido.Forne�a um correto:\n");
                    scanf("%li",&tf.id_depatamento);
                    setbuf(stdin,NULL);
                }while(buscaId(fd,2,tf.id_depatamento) == 0);
            hf.id_departamento = tf.id_depatamento;
        }

        do{
            setbuf(stdin,NULL);
            printf("\nForne�a o sal�rio do funcion�rio:\n");
            scanf("%f",&tf.salario);
            setbuf(stdin,NULL);
            if(tf.salario < 0.2f)
                printf("\nValor Inv�lido.");
        }while(tf.salario <= 0.2f);

        hs.salario = tf.salario;

        setbuf(stdin,NULL);
        printf("\nForne�a a rua:\n");
        fgets(tf.rua,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.rua);

        setbuf(stdin,NULL);
        printf("\nForne�a o bairro:\n");
        fgets(tf.bairro,30,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.bairro);

        do{
            setbuf(stdin,NULL);
            printf("\nForne�a o n�mero da casa ou apartamento:\n");
            scanf("%d",&tf.Numero);
            setbuf(stdin,NULL);
            if(tf.Numero < 0)
                printf("\nValor Inv�lido.");
        }while(tf.Numero < 0);

        setbuf(stdin,NULL);
        printf("\nForne�a um complemento:\n");
        fgets(tf.complemento,30,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.complemento);

        setbuf(stdin,NULL);
        printf("\nForne�a a cidade:\n");
        fgets(tf.cidade,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.cidade);

        setbuf(stdin,NULL);
        printf("\nForne�a a UF:\n");
        fgets(uf,4,stdin);
        setbuf(stdin,NULL);
        removeBarraN(uf);
        strcpy(tf.UF,uf);

        setbuf(stdin,NULL);
        printf("\nForne�a o CEP:\n");
        fgets(tf.CEP,9,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.CEP);

        setbuf(stdin,NULL);
        printf("\nForne�a um email:\n");
        fgets(tf.email,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.email);

        data = localtime(&dataAtual);

        ///Adicionando a data do sistema no registro do hist�rico de sal�rio.
        hs.mes = ++data->tm_mon;
        hs.ano = data->tm_year+1900;

        ///Adicionando a data do sistema no registro do hist�rico de funcion�rio.
        sprintf(hf.data,"%d/%d/%d",data->tm_mday,++data->tm_mon,data->tm_year+1900);

        hf.id_funcionario = tf.id;
        hs.id_funcionario = tf.id;

        salvaHistoricoSalario(fhs,hs);
        salvaHistoricoFunc(fhf,hf);
        salvaDadosFunc(ff,tf);

    }while(coletaOpcao() == 1);

    return -1;
}

int consultaFuncionario(FILE *ff,FILE *fd, char mat[]){
    TFuncionario tf;
    TDepartamento td;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    removeBarraN(mat);

    while(fread(&tf,sizeof(tf),1,ff)){
        removeBarraN(tf.matricula);
        if(strcmp(mat,tf.matricula) == 0){
            while(fread(&td,sizeof(td),1,fd) == 1)
                if(tf.id_depatamento == td.id)
                    printf("Nome do departamento: %s",td.nome);
            printf("\nNome: %s\nMatr�cula: %s\nID: %li\nData de Nascimento: %s\nCPF: %s\nID Departamento: %li\
                   \nSal�rio: %.2f\nRua: %s\nBairro: %s\nN�mero: %d\nComplemento: %s\nCidade: %s\nUF: %s\nCEP: %s\nEMAIL: %s\n",tf.nome,tf.matricula,tf.id,tf.dataNascimento,tf.CPF,td.id,tf.salario,tf.rua,tf.bairro,tf.Numero,tf.complemento,tf.cidade,
                   tf.UF,tf.CEP,tf.email);
            break;
        }
    }

    return -1;
}

void salvaDadosFunc(FILE *f, TFuncionario tf){
    fseek(f,0,SEEK_END);
    fwrite(&tf,sizeof(tf),1,f);
}

int gerarFolhaPagamento(FILE *ff){
    TFuncionario tf;
    char mat[10];

    if(arquivoVazio(ff) == 0){
        printf("\nN�o h� nenhum funcion�rio cadastrado no momento.\n");
        return -1;
    }

    getMatricula(mat);
    removeBarraN(mat);

    ///Verificando se o n�mero de matr�cula fornecido existe.
    if(verificaMatricula(ff,mat) == 1){
        do{
            printf("\nN�mero de matr�cula inexistente.Forne�a um v�lido:\n");
            getMatricula(mat);
        }while(verificaMatricula(ff,mat) == 1);
    }

    fseek(ff,0,SEEK_SET);
    ///Buscando o registro equivalente a matr�cula fornecida para mostrar os dados na tela.
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 0){
            printf("\nDetalhes da Folha de Pagamento:\n");
            printf("\nN�mero de Matr�cula: %s\tNome do Funcion�rio: %s\tSal�rio: %.2f\n\n",tf.matricula,tf.nome,tf.salario);
            return -1;
        }
    }
    return -1;
}

void getMatricula(char matricula[]){
    setbuf(stdin,NULL);
    msg01();
    printf("* Forne�a o n�mero de matr�cula do funcion�rio:\n");
    fgets(matricula,10,stdin);
}

///Verifica se a matr�cula fornecida � v�lida. Se for v�lida � retornado 1 sen�o � retornado 0.
int verificaMatricula(FILE *ff,char matricula[]){
    TFuncionario tf;
    fseek(ff, 0, SEEK_SET);
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(tf.matricula,matricula) == 0)
            return 0;
    }
    return 1;
}

