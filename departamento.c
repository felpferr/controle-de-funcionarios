#include <stdio.h>
#include "departamento.h"
#include "general.h"
#include "funcionario.h"
#include "historicos.h"

int cadastroDepartamento(FILE *ff,FILE *fd,FILE *fhd){
    TDepartamento td;
    HistoricoDepartamento hd;
    struct tm *data;
    time_t dataAtual = time(NULL);
    char ramal[6];///String que pode representar o número de caracteres do tipo unsigned short int.

    do{
        limpaTela();

        td.id = geraID(verificaUltimoID(fd,2));
        hd.id_departamento = td.id;

        setbuf(stdin,NULL);
        printf("* Forneça o nome do departamento:\n");
        fgets(td.nome,40,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça uma sigla para o departamento:\n");
        fgets(td.sigla,10,stdin);

        do{
            setbuf(stdin,NULL);
            printf("\n* Forneça um Ramal válido:\n");
            fgets(ramal,6,stdin);

            if(sizeof(ramal) == 0){
                do{
                    setbuf(stdin,NULL);
                    printf("\n* Por favor meu consagrado forneça um Ramal válido:\n");
                    fgets(ramal,6,stdin);
                }while(sizeof(ramal) == 0);
            }
        }while(verificaRamal(ramal) == 0);

        if(arquivoVazio(ff) == 0){
            continue;
        }
        else{
            setbuf(stdin,NULL);
            printf("\nForneça o ID de um funcionário para designá-lo como gerente deste departamento:\n");
            scanf("%li",&td.id_gerente);
            if(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0){
                do{
                    setbuf(stdin,NULL);
                    printf("\nID inválido forneça um correto:");
                    scanf("%li",&td.id_gerente);
                }while(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0);
            }
        }
        hd.id_gerente = td.id_gerente;

        data = localtime(&dataAtual);
        sprintf(hd.data,"%s/%s/%s",data->tm_mday,data->tm_mon++,data->tm_year);///VERIFICAR DEPOIS SE A COERÇÃO DE TIPO NÃO ESTÁ GERANDO INCONSISTÊNCIA

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
            printf("Não há departamentos cadastrados no momento.");
            return 0;
        }

        limpaTela();

        setbuf(stdin,NULL);
        printf("\nForneça o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                setbuf(stdin,NULL);
                printf("\nID inexistente ou inválido. Forneça um novo ID:\n");
                scanf("%li",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == id)
                break;
        }

        printf("\nCódigo do Departamento: %li\nNome: %s\n",td.id,td.nome);
        printf("Matrícula\tNome\tSalario\n");
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
            printf("Não há departamentos cadastrados no momento.");
            return 0;
        }

        limpaTela();
        setbuf(stdin,NULL);
        printf("Forneça o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                setbuf(stdin,NULL);
                printf("\nID inexistente ou inválido. Forneça um novo ID:\n");
                scanf("%li",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(tf.id_depatamento == id){
                printf("\n\nNome: %s\tCPF: %s\tID: %li\tMatrícula: %s\nSalário: %f\tEmail: %s",
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

    for(i = 0; i < 6/*<-tamanho da string ramal*/;i++){
        if(isalpha(ramal[i]) == 1)///Se existir um caractere alfabético na string é retornado 0.
            return 0;
        if(isalnum(ramal[i]) == 0)///Se existir um caractere especial na string é retornado 0.
        ///Verificando se o caractere não é especial pois a função isalpha() retorna o mesmo valor para números e caracteres especiais.
            return 0;
    }
    return 1;///Caso o ramal seja composto apenas por números é retornado 1.
}
