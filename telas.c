#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "general.h"
#include "telas.h"
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"
#include "listagens.h"

void inicio(){
    unsigned short int opcao;
    FILE *ff,*fd,*fhf,*fhs,*fhd;
    HistoricoDepartamento hd;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    TDepartamento dep;
    TFuncionario func;

    setlocale(LC_ALL,"Portuguese");

    ff = fopen("funcionario.dat","rb+");
    if(ff == NULL){
        ff = fopen("funcionario.dat","wb+");
    }

    fd = fopen("departamento.dat","rb+");
    if(fd == NULL){
        fd = fopen("departamento.dat","wb+");
    }

    fhf = fopen("historicoFuncionario.dat","rb+");
    if(fhf == NULL){
        fhf = fopen("historicoFuncionario.dat","wb+");
    }

    fhs = fopen("historicoSalario.dat","rb+");
    if(fhs == NULL){
        fhs = fopen("historicoSalario.dat","wb+");
    }

    fhd = fopen("historicoDepartamento.dat","rb+");
    if(fhd == NULL){
        fhd = fopen("historicoDepartamento.dat","wb+");
    }

    printf("\t\t\t\tBem Vindo...\n\n");

    do{
        printf("Escolha uma das opções abaixo:\n1-Cadastro.\n2-Alteração.\n3-Consultas.\n4-Sair.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = telaCadastros(ff,fd,fhf,fhs,fhd,&dep,&func);
                limpaTela();
                break;

            case 2:
                opcao = telaAlteracoes(ff,fd,fhd,fhs,fhf,&dep,&func);
                limpaTela();
                break;

            case 3:
                opcao = telaConsulta(ff,fd,fhs,fhd,fhf,&dep,&func,&hd,&hf,&hs);
                limpaTela();
                break;

            case 4:
                sair();
                break;

            default:
                printf("\nOpção inválida.");
                break;
        };
    }while(opcao < 1 || opcao > 4);

    fclose(ff);
    fclose(fd);
    fclose(fhf);
    fclose(fhs);
    fclose(fhd);
}

int telaCadastros(FILE *ff,FILE *fd,FILE *fhf,FILE *fhs,FILE *fhd, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Cadastrar Funcionário.\n2-Cadastrar Departamento.\n3-Voltar.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = cadastroFuncionario(ff,fd,fhf,fhs);
                limpaTela();
                break;

            case 2:
                opcao = cadastroDepartamento(ff,fd,fhd);
                limpaTela();
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

int telaAlteracoes(FILE *ff,FILE *fd,FILE *fhd,FILE *fhs,FILE *fhf, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Alterar Dados do Funcionário.\n2-Alterar Salário do Funcionário.\
        \n3-Alterar Departamento de Funcionário.\n4-Alterar Gerente do Departamento.\n5-Voltar.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = alterarFuncionario(ff,fd,fhf,fhs);
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

int telaConsulta(FILE *ff, FILE *fd, FILE *fhs,FILE *fhd, FILE *fhf, TDepartamento *dep, TFuncionario *func, HistoricoDepartamento *hd, HistoricoFuncionario *hf, HistoricoSalario *hs){
    unsigned short int opcao;
    limpaTela();

    do{
        printf("Escolha uma das opções abaixo:\n1-Listagens.\n2-Gerar Folha de pagamento.\
        \n3-Gerar histórico de um período.\n4-Gerar relatório de funcionários por departamento.\n5-Voltar.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = telaListagens(ff,fd,fhs,fhd,fhf);
                //limpaTela();
                break;

            case 2:
                opcao = gerarFolhaPagamento(ff);
                break;

            case 3:
                opcao = geraHistoricoPeriodo(ff,fhs);
                break;

            case 4:
                opcao = relatorioFuncionario(ff,fd);
                break;

            case 5:
                return 0; /*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/

            default:
                printf("\nOpção inválida!!");
                break;
        };
    }while(opcao < 1 || opcao > 5);

    return 0;/*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
}


int telaListagens(FILE *ff, FILE *fd, FILE *fhs, FILE *fhd, FILE *fhf){
    unsigned short int opcao;
    char mat[10];

    do{
        limpaTela();
        printf("Escolha uma das opções abaixo:\n1-Consultar os Dados de Um Funcionário.\n2-Consultar Dados dos Gerentes.\n3-Listar Todos os Funcionários.\
                \n4-Listar Todos os Departamentos.\n5-Listar o Histórico de Funcionários Completo.\n6-Listar o Histórico de Departamentos Completo\
                \n7-Listar o Histórico de Salários Completo\n8-Voltar.\n");
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
                opcao = l_Funcionarios(ff);
               // limpaTela();
                break;

            case 4:
                opcao = l_Departamentos(fd);
                break;

            case 5:
                opcao = l_HistoricoFuncionario(fhf);
                break;

            case 6:
                opcao  = l_HistoricoDepartamento(fhd);
                break;

            case 7:
                opcao = l_HistoricoSalario(fhs);
                break;

            case 8:
                return -1;

            default:
                printf("\nOpção Inválida!!");
                break;
        }
    }while(opcao < 1 || opcao > 7);

    return 0;/*É retornado um valor que faça o loop(do/while) da função inicio() seja reiniciado.*/
}
