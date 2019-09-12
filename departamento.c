#include <stdio.h>
#include <string.h>
#include "departamento.h"
#include "general.h"
#include "funcionario.h"
#include "historicos.h"

int cadastroDepartamento(FILE *ff,FILE *fd,FILE *fhd){
    TDepartamento td;
    HistoricoDepartamento hd;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char ramal[6];///String que pode representar o n�mero de caracteres do tipo unsigned short int.

    do{
        limpaTela();

        msg01();

        td.id = geraID(verificaUltimoID(fd,2));
        hd.id_departamento = td.id;

        setbuf(stdin,NULL);
        printf("* Forne�a o nome do departamento:\n");
        fgets(td.nome,40,stdin);
        if(strlen(td.nome) == 0){
            do{
                setbuf(stdin,NULL);
                promptUniversal();
                printf("* Forne�a o nome do departamento:\n");
                fgets(td.nome,40,stdin);
                removeBarraN(td.nome);
            }while(strlen(td.nome) == 0);
        }


        setbuf(stdin,NULL);
        printf("\nForne�a uma sigla para o departamento:\n");
        fgets(td.sigla,10,stdin);

        do{
            setbuf(stdin,NULL);
            printf("\n* Forne�a um Ramal v�lido:\n");
            fgets(ramal,6,stdin);

            if(strlen(ramal) == 0){
                do{
                    setbuf(stdin,NULL);
                    printf("\n* Por favor forne�a um Ramal v�lido:\n");
                    fgets(ramal,6,stdin);
                }while(sizeof(ramal) == 0);
            }
        }while(verificaRamal(ramal) == 0);

        td.Ramal = atoi(ramal);

        if(arquivoVazio(ff) == 0){
            td.id_gerente = 0;
        }
        else{
            setbuf(stdin,NULL);
            printf("\nForne�a o ID de um funcion�rio para design�-lo como gerente deste departamento:\n");
            scanf("%li",&td.id_gerente);
            if(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0){
                do{
                    setbuf(stdin,NULL);
                    promptUniversal();
                    printf("\nID inv�lido forne�a um correto:");
                    scanf("%li",&td.id_gerente);
                }while(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0);
            }
        }
        hd.id_gerente = td.id_gerente;

        data = localtime(&dataAtual);
        sprintf(hd.data,"%d/%d/%d",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COER��O DE TIPO N�O EST� GERANDO INCONSIST�NCIA

        salvaHistoricoDep(fhd,hd);
        salvaDadosDep(td,fd);
    }while(coletaOpcao() == 1);

    return -1;
}

int relatorioFuncionario(FILE *ff,FILE *fd){
    TFuncionario tf;
    TDepartamento td;
    long id;
    float soma = 0.0;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    do{
        if(arquivoVazio(fd) == 0){
            printf("N�o h� departamentos cadastrados no momento.");
            return 0;
        }

        limpaTela();

        msg01();

        setbuf(stdin,NULL);
        printf("\n* Forne�a o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                setbuf(stdin,NULL);
                printf("\nID inexistente ou inv�lido. Forne�a um novo ID:\n");
                scanf("%li",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == id)
                break;
        }

        printf("\n* C�digo do Departamento: %li\nNome: %s\n",td.id,td.nome);
        printf("Matr�cula\tNome\tSalario\n");
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(tf.id_depatamento == id){
                printf("%s\t%s\t%f",tf.matricula,tf.nome,tf.salario);
                soma += tf.salario;
            }
        }
        printf("\nTotal da folha de pagamento: %f",soma);
    }while(coletaOpcao() == 1);

    return -1;
}

int dadosDosGerentes(FILE *ff,FILE *fd){
    TFuncionario tf;
    long id;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    do{
        if(arquivoVazio(fd) == 0){
            printf("N�o h� departamentos cadastrados no momento.");
            return -1;
        }

        limpaTela();

        msg01();

        setbuf(stdin,NULL);
        printf("\n* Forne�a o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                setbuf(stdin,NULL);
                printf("\nID inexistente ou inv�lido. Forne�a um novo ID:\n");
                scanf("%li",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(tf.id_depatamento == id){
                printf("\n\nNome: %s\tCPF: %s\tID: %li\tMatr�cula: %s\nSal�rio: %f\tEmail: %s",
                tf.nome,tf.CPF,tf.id,tf.matricula,tf.salario,tf.email);
            }
        }

    }while(coletaOpcao() == 1);

    return -1;
}

void salvaDadosDep(TDepartamento td, FILE *fd){
    fseek(fd,0,SEEK_END);
    fwrite(&td,sizeof(td),1,fd);
}

int verificaRamal(char ramal[]){
    int i;

    removeBarraN(ramal);

    for(i = 0; i < strlen(ramal)/*<-tamanho da string ramal*/;i++){
        ///iRamal[i] = ramal[i];
        if(isalpha(ramal[i]) != 0){///Se existir um caractere alfab�tico na string � retornado 0.
            return 0;
        }
        ///Verificando se o caractere n�o � especial pois a fun��o isalpha() retorna o mesmo valor para n�meros e caracteres especiais.
        if(isalnum(ramal[i]) == 0)///Se existir um caractere especial na string � retornado 0.
            return 0;
    }
    return 1;///Caso o ramal seja composto apenas por n�meros � retornado 1.
}
