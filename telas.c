#include <stdio.h>
#include <string.h>
#include "general.h"
#include "telas.h"
#include "funcionario.h"
#include "departamento.h"

void inicio(){
    unsigned short int opcao;
    FILE *ff,*fd,*fhf,*fhs,*fhd;
    HistoricoDepartamento hd;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    TDepartamento dep;
    TFuncionario func;

    setlocale(LC_ALL,"Portuguese");

    ff = fopen("funcionario.dat","wr");
    fd = fopen("departamento.dat","wr");
    fhf = fopen("historicoFuncionario.dat","wr");
    fhs = fopen("historicoSalario.dat","wr");
    fhd = fopen("historicoDepartamento.dat","wr");

    printf("\t\t\t\tBem Vindo\n");

    do{
        printf("Escolha uma das opções abaixo:1-Cadastro.\n2-Alteração.\n3-Consultas.\n4-Sair.");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                telaCadastros(ff,fd,fhf,fhs,fhd,&dep,&func);
                break;

            case 2:
                telaAlteracoes(ff,fd,&dep,&func);
                break;

            case 3:
                telaConsulta(ff,fd,&dep,&func,&hd,&hf,&hs);
                break;

            case 4:
                sair();
                break;

            default:
                break;
        };
    }while(opcao < 1 || opcao > 4);
}

int telaCadastros(FILE *ff,FILE *fd,FILE *fhf,FILE *fhs,FILE *fhd, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Cadastrar Funcionário.\n2-Cadastrar Departamento.\n3-Voltar.");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                opcao = cadastroFuncionario(ff,fd,fhf,fhs);
                break;

            case 2:
                opcao = cadastroDepartamento(ff,fd,fhd);
                break;

            case 3:
                return 0;/*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/

            default:
                printf("\nOpção inválida!!\n");
                break;
        };
    }while(opcao < 1 || opcao > 3);

    return 0;/*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
}

int telaAlteracoes(FILE *ff,FILE *fd, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Alterar Dados do Funcionário.\n2-Alterar Salário do Funcionário.\
        \n3-Alterar Departamento de Funcionário.\n4-Alterar Gerente do Departamento.\n5-Voltar.\n\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = alterarFuncionario();
                break;

            case 2:
                opcao = alterarSalario(ff,fhs);
                break;

            case 3:
                opcao = alterarDepartamentoFunc(ff,fd,fhf);
                break;

            case 4:
                opcao = alterarGerenteDep(ff,fd,fhd);
                break;

            case 5:
                return 0; /*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/

            default:
                printf("\nOpção inválida!!");
                break;
        };
    }while(opcao < 1 || opcao > 5);

    return 0; /*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
}

int telaConsulta(FILE *ff,FILE *fd, TDepartamento *dep, TFuncionario *func, HistoricoDepartamento *hd, HistoricoFuncionario *hf, HistoricoSalario *hs){
    unsigned short int opcao;
    char mat[10];
    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Consultar dados do Funcionário.\n2-Consultar Dados dos Gerentes.\n3-Gerar Folha de pagamento.\
        \n4-Gerar histórico de um período.\n5-Gerar relatório de funcionários por departamento.\n6-Voltar.\n\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                getMatricula(mat);
                opcao = consultaFuncionario(ff,fd,mat);
                break;
            case 2:
                opcao = dadosDosGerentes(ff,fd);
                break;
            case 3:
                opcao = gerarFolhaPagamento(ff);
                break;
            case 4:
                opcao = geraHistoricoPeriodo();
                break;
            case 5:
                opcao = relatorioFuncionario(ff,fd);
                break;
            case 6:
                return 0; /*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
            default:
                printf("\nOpção inválida!!");
                break;
        };
    }while(opcao < 1 || opcao > 6);

    return 0;/*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
}


