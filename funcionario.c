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

    do{
        limpaTela();

        do{
            getMatricula(tf.matricula);
            removeBarraN(tf.matricula);
        }while(verificaMatricula(ff,tf.matricula) == 0);

        /*Garante que o campo nome do arquivo de funcionário não seja vazio.*/
        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça o nome do funcionário:\n");
            fgets(tf.nome,60,stdin);
            setbuf(stdin,NULL);
            removeBarraN(tf.nome);
        }while(strlen(tf.nome) == 0);

        tf.id = geraID(verificaUltimoID(ff,1));
        hf.id_funcionario = tf.id;
        hs.id_funcionario = tf.id;

        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça a data de nascimento:\n");
            printf("Dia: ");
            fgets(g.dia,3,stdin);
            setbuf(stdin,NULL);

            setbuf(stdin,NULL);
            setbuf(stdin,NULL);
            printf("\nMês: ");
            fgets(g.mes,3,stdin);
            setbuf(stdin,NULL);

            setbuf(stdin,NULL);
            printf("\nAno: ");
            fgets(g.ano,6,stdin);
            setbuf(stdin,NULL);

            sprintf(tf.dataNascimento,"%s/%s/%s",g.dia,g.mes,g.ano);
        }while(validaData(tf.dataNascimento)==0);

        sprintf(hf.data,"%s/%s/%s",g.dia,g.mes,g.ano);

        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça o CPF:\n");
            fgets(tf.CPF,12,stdin);
            setbuf(stdin,NULL);
            removeBarraN(tf.CPF);
        }while(validaCPF(tf.CPF) == 0);


        /*Verificando se existe um departamento cadastrado pois, se não houver nenhum
          cadastrado não é obrigatório registrar os funcionários  em  um departamento.
        */
        if(arquivoVazio(fd) == 0){
            ;
        }
        else{
            printf("\nForneça o ID de um departamento para adicionar este funcionário ao departamento:\n");
            scanf("%li",&tf.id_depatamento);
            setbuf(stdin,NULL);

            if(buscaId(fd,2,tf.id_depatamento) == 0)
                do{
                    printf("\nCódigo de departamento inexistente ou inválido.Forneça um correto:\n");
                    scanf("%li",&tf.id_depatamento);
                    setbuf(stdin,NULL);
                }while(buscaId(fd,2,tf.id_depatamento) == 0);
            hf.id_departamento = tf.id_depatamento;
        }

        do{
            setbuf(stdin,NULL);
            printf("\nForneça o salário do funcionário:\n");
            scanf("%f",&tf.salario);
            setbuf(stdin,NULL);
            if(tf.salario < 0.2f)
                printf("\nValor Inválido.");
        }while(tf.salario <= 0.2f);

        hs.salario = tf.salario;

        setbuf(stdin,NULL);
        printf("\nForneça a rua:\n");
        fgets(tf.rua,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.rua);

        setbuf(stdin,NULL);
        printf("\nForneça o bairro:\n");
        fgets(tf.bairro,30,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.bairro);

        do{
            setbuf(stdin,NULL);
            printf("\nForneça o número da casa ou apartamento:\n");
            scanf("%d",&tf.Numero);
            setbuf(stdin,NULL);
            if(tf.Numero < 0)
                printf("\nValor Inválido.");
        }while(tf.Numero < 0);

        setbuf(stdin,NULL);
        printf("\nForneça um complemento:\n");
        fgets(tf.complemento,30,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.complemento);

        setbuf(stdin,NULL);
        printf("\nForneça a cidade:\n");
        fgets(tf.cidade,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.cidade);

        setbuf(stdin,NULL);
        printf("\nForneça a UF:\n");
        fgets(tf.UF,3,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.UF);

        setbuf(stdin,NULL);
        printf("\nForneça o CEP:\n");
        fgets(tf.CEP,9,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.CEP);

        setbuf(stdin,NULL);
        setbuf(stdin,NULL);
        printf("\nForneça um email:\n");
        fgets(tf.email,40,stdin);
        setbuf(stdin,NULL);
        removeBarraN(tf.email);

        data = localtime(&dataAtual);

        ///Adicionando a data do sistema no registro do histórico de salário.
        hs.mes = data->tm_mon++;
        hs.ano = data->tm_year;

        ///Adicionando a data do sistema no registro do histórico de funcionário.
        sprintf(hf.data,"%d/%d/%d",data->tm_mday,data->tm_mon++,data->tm_year);

        salvaHistoricoSalario(fhs,hs);
        salvaHistoricoFunc(fhf,hf);
        salvaDadosFunc(ff,tf);

    }while(coletaOpcao() == 1);

    return -1;
}

int consultaFuncionario(FILE *ff,FILE *fd, char mat[]){
    TFuncionario tf;
    TDepartamento td;

    if(arquivoVazio(ff) == 0){
        printf("\nNão há funcionários cadastrados no momento.");
        return -1;
    }


    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    removeBarraN(mat);

    while(fread(&tf,sizeof(tf),1,ff)){
        removeBarraN(tf.matricula);
        if(strcmp(mat,tf.matricula) == 0){
            while(fread(&td,sizeof(td),1,fd) == 1)
                if(tf.id_depatamento == td.id)
                    printf("%s",td.nome);
            printf("\nNome: %s\nMatrícula: %s\nID: %li\nData de Nascimento: %s\nCPF: %s\nID Departamento: %li\
                   \nSalário: %.2f\nRua: %s\nBairro: %s\nNúmero: %d\nComplemento: %s\nCidade: %s\nUF: %s\nCEP: %s\nEMAIL: %s\n",tf.nome,tf.matricula,tf.id,tf.dataNascimento,tf.CPF,td.id,tf.salario,tf.rua,tf.bairro,tf.Numero,tf.complemento,tf.cidade,
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
        printf("\nNão há nenhum funcionário cadastrado no momento.");
        return 0;
    }

    getMatricula(mat);

    ///Verificando se o número de matrícula fornecido existe.
    if(verificaMatricula(ff,mat) == 0){
        do{
            printf("\nNúmero de matrícula inexistente.Forneça um válido:\n");
            getMatricula(mat);
        }while(verificaMatricula(ff,mat) == 0);
    }

    fseek(ff,0,SEEK_SET);
    ///Buscando o registro equivalente a matrícula fornecida para mostrar os dados na tela.
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 1){
            printf("\nDetalhes da Folha de Pagamento:");
            printf("\nNúmero de Matrícula: %s\tNome do Funcionário: %s\tSalário: %.2f\n\n",tf.matricula,tf.nome,tf.salario);
            return -1;
        }
    }
    return -1;
}

void getMatricula(char matricula[]){
    setbuf(stdin,NULL);
    msg01();
    printf("* Forneça o número de matrícula do funcionário:\n");
    fgets(matricula,10,stdin);
}

///Verifica se a matrícula fornecida é válida. Se for válida é retornado 1 senão é retornado 0.
int verificaMatricula(FILE *ff,char matricula[]){
    TFuncionario tf;
    fseek(ff, 0, SEEK_SET);
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(tf.matricula,matricula) == 0)
            return 0;
    }
    return 1;
}

