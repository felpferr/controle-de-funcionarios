#include <stdio.h>
#include "departamento.h"
#include "general.h"

int cadastroDepartamento(FILE *ff,FILE *fd){
    TDepartamento td;
    int opcao;

    do{
        limpaTela();

        td.id = geraID(verificaID(f,2));

        setbuf(stdin,NULL);
        printf("* Forneça o nome do departamento:\n");
        fgets(td.nome,40,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça uma sigla para o departamento:\n");
        fgets(td.sigla,10,stdin);

        setbuf(stdin,NULL);
        printf("\nForneça um Ramal:\n");
        scanf("%d",&td.Ramal);

        printf("\nForneça o ID de um funcionário para designá-lo como gerente deste departamento:\n");
        scanf("%d",&td.id_gerente);
        if(td.id_gerente <= 0 || buscaIdFunc(fd) == 0){
            do{
                printf("\nID inválido forneça um correto:");
                scanf("%d",&td.id_gerente);
            }while(td.id_gerente <= 0 || buscaIdFunc(fd) == 0);
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
            printf("Não há departamentos cadastrados no momento.");
            return 0;
        }

        limpaTela();

        printf("\nForneça o ID de um departamento:\n");
        scanf("%d",&id);

        if(buscaId(fd,2,id) == 0){
            do{
                printf("\nID inexistente ou inválido. Forneça um novo ID:\n");
                scanf("%d",&id);
            }while(buscaId(fd,2,id) == 0);
        }

        while(fread(&td,sizeof(td),1,fd) == 1){
            if(td.id == id)
                break;
        }

        printf("\nCódigo do Departamento: %d\nNome: %s\n",td.id,td.nome);
        printf("Matrícula\tNome\tSalario\n");
        while(fread(&tf,sizeof(tf),1,ff) == 1){
            if(tf.id_depatamento == id){
                printf("%s\t%s\t%f",tf.matricula,tf.nome,tf.salario);
                soma += tf.salario;
            }
        }
        printf("\nTotal da folha de pagamento: %f",&soma);
    }while(coletaOpcao() == 1);

    return 1;
}

int dadosDosGerentes(FILE *ff,FILE *fd){


    return 1;
}

long buscaId(FILE *f, int modo,long id){
    TFuncionario tf;
    TDepartamento td;

    fseek(ff,0,SEEK_SET);
    fseek(fd,0,SEEK_SET);

    if(modo == 1){
        while(fread(&tf,sizeof(tf),1,f) == 1){
            if(tf.id == id)
                return 1;
        }
        return 0;
    }
    else
        while(fread(&td,sizeof(td),1,f) == 1){
            if(td.id == id)
                return 1;
        }
        return 0;
}
