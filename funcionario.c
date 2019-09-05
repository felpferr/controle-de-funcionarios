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
    HistoricoSalario hs;
    geral g;
    int opcao;

    do{
        limpaTela();

        getMatricula(tf.matricula);

        /*Garante que o campo nome do arquivo de funcionário não seja vazio.*/
        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça o nome do funcionário:\n");
            fgets(tf.nome,60,stdin);
        }while(strlen(tf.nome) == 0);

        tf.id = geraID(verificaUltimoID(f,1));
        hf.id_funcionario = tf.id;
        hs.id_funcionario = tf.id;

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
        sprintf(hs.mes,"%s",g.mes);
        sprintf(hs.ano,"%s",g.ano);

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

        salvaHistoricoSalario(fhs,hs);
        salvaHistoricoFunc(fhf,hf);
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

int gerarFolhaPagamento(FILE *ff){
    TFuncionario tf;
    char mat[10];

    if(arquivoVazio(ff) == 0){
        printf("\nNão há nenhum funcionário cadastrado no momento!!");
        return 0;
    }

    getMatricula(ff,mat);

    ///Verificando se o número de matrícula fornecido existe.
    if(pesquisaMat(mat,ff) == 0){
        do{
            printf("\nNúmero de matrícula inexistente.Forneça um válido:\n");
            getMatricula(mat);
        }while(pesquisaMat(mat,ff) == 0);
    }

    ///Buscando o registro equivalente a matrícula fornecida para mostrar os dados na tela.
    while(fread(&tf,sizeof(tf),1,ff) == 1){
        if(strcmp(mat,tf.matricula) == 1){
            printf("\nDetalhes da Folha de Pagamento:");
            printf("\nNúmero de Matrícula: %s\tNome do Funcionário: %s\tSalário: %f",tf.matricula,tf.nome,tf.salario);
            return 1;
        }
    }
    return 0;
}

void getMatricula(char mat[]){
    setbuf(stdin,NULL);
    printf("* Forneça o número de matrícula do funcionário:\n");
    fgets(mat,10,stdin);
}
