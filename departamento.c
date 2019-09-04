#include <stdio.h>
#include "departamento.h"
#include "general.h"
#include "funcionario.h"

int cadastroDepartamento(FILE *ff,FILE *fd){
    TDepartamento td;

    do{
        limpaTela();

        td.id = geraID(verificaUltimoID(fd,2));

        setbuf(stdin,NULL);
        printf("* Forne�a o nome do departamento:\n");
        fgets(td.nome,40,stdin);

        setbuf(stdin,NULL);
        printf("\nForne�a uma sigla para o departamento:\n");
        fgets(td.sigla,10,stdin);

        setbuf(stdin,NULL);
        printf("\nForne�a um Ramal:\n");
        scanf("%hu",&td.Ramal);


        printf("\nForne�a o ID de um funcion�rio para design�-lo como gerente deste departamento:\n");
        scanf("%li",&td.id_gerente);
        if(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0){
            do{
                printf("\nID inv�lido forne�a um correto:");
                scanf("%li",&td.id_gerente);
            }while(td.id_gerente <= 0 || buscaId(fd,2,td.id_gerente) == 0);
        }

        salvaDadosDep(td,fd);
    }while(coletaOpcao() == 1);

    return 1;
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

        printf("\nForne�a o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                printf("\nID inexistente ou inv�lido. Forne�a um novo ID:\n");
                scanf("%li",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == id)
                break;
        }

        printf("\nC�digo do Departamento: %li\nNome: %s\n",td.id,td.nome);
        printf("Matr�cula\tNome\tSalario\n");
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(tf.id_depatamento == id){
                printf("%s\t%s\t%f",tf.matricula,tf.nome,tf.salario);
                soma += tf.salario;
            }
        }
        printf("\nTotal da folha de pagamento: %f",soma);
    }while(coletaOpcao() == 1);

    return 1;
}

int dadosDosGerentes(FILE *ff,FILE *fd){
    TFuncionario tf;
    long id;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    do{
        if(arquivoVazio(fd) == 0){
            printf("N�o h� departamentos cadastrados no momento.");
            return 0;
        }

        limpaTela();
        printf("Forne�a o ID de um departamento:\n");
        scanf("%li",&id);

        if(buscaId(fd,2,id) == 0){
            do{
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

    return 1;
}

long buscaId(FILE *f, int modo,long id){
    TFuncionario tf;
    TDepartamento td;

    fseek(f,0,SEEK_SET);

    if(modo == 1){
        while(fread(&tf,sizeof(tf),1,f) == 1){
            if(tf.id == id)
                return 1;
        }
        return 0;
    }
    else{
        while(fread(&td,sizeof(td),1,f) == 1){
            if(td.id == id)
                return 1;
        }
        return 0;
    }
}

void salvaDadosDep(TDepartamento td, FILE *fd){
    fseek(fd,0,SEEK_END);
    fwrite(&td,sizeof(td),1,fd);
}
