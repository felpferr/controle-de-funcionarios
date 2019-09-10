#include <stdio.h>
#include <string.h>
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"
#include "general.h"
#include "time.h"


int alterarFuncionario(FILE *ff, FILE *fd, FILE *fhf, FILE *fhs){
    TFuncionario tf;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    char mat[10];
    struct tm *data;
    time_t dataAtual = time(NULL);
    geral g;

    if(arquivoVazio(ff) == 0){
        printf("\nNão há funcionários cadastrados no momento.");
        return -1;
    }

    do{
        limpaTela();

        msg01();

        getMatricula(mat);
        removeBarraN(mat);

        if(pesquisaMat(mat,ff) == 0){
            do{
                printf("\nNúmero de Matrícula inexistente. Forneça um válido:");
                getMatricula(mat);
                removeBarraN(mat);
            }while(pesquisaMat(mat,ff) == 0);
        }

        ///Posicionando o arquivo no registro que será alterado.
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(strcmp(mat,tf.matricula) == 1){
                fseek(ff,0,SEEK_CUR);
                break;
            }
        }

        data = localtime(&dataAtual);

        /*Garante que o campo nome do arquivo de funcionário não seja vazio.*/
        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça o nome do funcionário:\n");
            fgets(tf.nome,60,stdin);
            removeBarraN(tf.nome);
        }while(strlen(tf.nome) == 0);

        hf.id_funcionario = tf.id;
        hs.id_funcionario = tf.id;

        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça a data de nascimento:\n");
            printf("Dia: ");
            fgets(g.dia,3,stdin);
            setbuf(stdin,NULL);
            promptUniversal();
            printf("\nMês: ");
            fgets(g.mes,3,stdin);
            setbuf(stdin,NULL);
            promptUniversal();
            printf("\nAno: ");
            fgets(g.ano,5,stdin);
            setbuf(stdin,NULL);

            sprintf(tf.dataNascimento,"%s/%s/%s",g.dia,g.mes,g.ano);
        }while(validaData(tf.dataNascimento)==0);

        sprintf(hf.data,"%s/%s/%s",g.dia,g.mes,g.ano);

        do{
            setbuf(stdin,NULL);
            promptUniversal();
            printf("* Forneça o CPF:\n");
            fgets(tf.CPF,12,stdin);
        }while(validaCPF(tf.CPF) == 0);

        /*Verificando se existe um departamento cadastrado pois, se não houver nenhum
          cadastrado não é obrigatório registrar os funcionários  em  um departamento.
        */
        if(arquivoVazio(fd) == 0){
            continue;
        }
        else{
            promptUniversal();
            printf("\nForneça o ID de um departamento para adicionar este funcionário ao departamento:\n");
            scanf("%li",&tf.id_depatamento);

            if(buscaId(fd,2,tf.id_depatamento) == 0)
                do{
                    printf("\nCódigo de departamento inexistente ou inválido.Forneça um correto:\n");
                    scanf("%li",&tf.id_depatamento);
                }while(buscaId(fd,2,tf.id_depatamento) == 0);
            hf.id_departamento = tf.id_depatamento;
        }

        do{
            setbuf(stdin,NULL);
            printf("Forneça o salário do funcionário:\n");
            scanf("%f",&tf.salario);
            if(tf.salario < 0.2f)
                printf("\nValor Inválido.");
        }while(tf.salario <= 0.2f);

        hs.salario = tf.salario;

        setbuf(stdin,NULL);
        printf("\nForneça a rua:\n");
        fgets(tf.rua,40,stdin);
        removeBarraN(tf.rua);

        setbuf(stdin,NULL);
        printf("\nForneça o bairro:\n");
        fgets(tf.bairro,30,stdin);
        removeBarraN(tf.bairro);

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
        removeBarraN(tf.complemento);

        setbuf(stdin,NULL);
        printf("\nForneça a cidade:\n");
        fgets(tf.cidade,40,stdin);
        removeBarraN(tf.cidade);

        setbuf(stdin,NULL);
        printf("\nForneça a UF:\n");
        fgets(tf.UF,3,stdin);
        removeBarraN(tf.UF);

        setbuf(stdin,NULL);
        printf("\nForneça o CEP:\n");
        fgets(tf.CEP,9,stdin);
        removeBarraN(tf.CEP);

        setbuf(stdin,NULL);
        printf("\nForneça um email:\n");
        fgets(tf.email,40,stdin);
        removeBarraN(tf.email);

        ///Adicionando a data do sistema no registro do histórico de salário.
        hs.mes = data->tm_mon;
        hs.ano = data->tm_year;

        ///Adicionando a data do sistema no registro do histórico de funcionário.
        sprintf(hf.data,"%d/%d/%d",data->tm_mday,data->tm_mon++,data->tm_year);

        salvaHistoricoSalario(fhs,hs);
        salvaHistoricoFunc(fhf,hf);

        /*
          Salvando a alteração no arquivo de funcionários.
          OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
          (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
          arquivo pelo registro recém modificado.
        */
        fwrite(&tf,sizeof(tf),1,ff);

    }while(coletaOpcao() == 1);

    return -1;
}

int alterarSalario(FILE *ff,FILE *fhs){
    TFuncionario tf;
    HistoricoSalario hs;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char mat[10];

    fseek(ff,0,SEEK_SET);
    fseek(fhs,0,SEEK_SET);

    data = localtime(&dataAtual);

    if(arquivoVazio(ff) == 0){
        limpaTela();
        printf("\nNenhum há nenhum funcionário cadastrado no momento meu consagrado!!");
        return 1;
    }

    getMatricula(mat);
    removeBarraN(mat);

    if(pesquisaMat(mat,ff) == 0){
        do{
            printf("\nNúmero de Matrícula inexistente.");
            getMatricula(mat);
            removeBarraN(mat);
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

    hs.mes = data->tm_mon;
    hs.ano = data->tm_year;

    /*Salvando a alteração no arquivo de funcionários.
      OBS: Não é utilizada a função salvaDadosFunc pois ela salva novos registros no final do arquivo
      (criando réplicas dos dados de um funcionário), neste caso é sobrescrito  o  registro atual  do
      arquivo pelo registro recém modificado.*/
    fwrite(&tf,sizeof(tf),1,ff);

    ///Salvando a alteração no arquivo de histórico de salário do funcionário.
    salvaHistoricoSalario(fhs,hs);

    return -1;
}

int alterarDepartamentoFunc(FILE *ff,FILE *fd,FILE *fhf){
    TFuncionario tf;
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
        sprintf(hf.data,"%d/%d/%d",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COERÇÃO DE TIPO NÃO ESTÁ GERANDO INCONSISTÊNCIA

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

        msg01();

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
        sprintf(hd.data,"%d/%d/%d",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COERÇÃO DE TIPO NÃO ESTÁ GERANDO INCONSISTÊNCIA

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
