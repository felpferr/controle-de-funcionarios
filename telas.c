#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "general.h"
#include "telas.h"
#include "funcionario.h"
#include "departamento.h"
#include "historicos.h"
#include "alteracoes.h"

void inicio(){
    unsigned short int opcao;
    FILE *ff,*fd,*fhf,*fhs,*fhd;
    HistoricoDepartamento hd;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    TDepartamento dep;
    TFuncionario func;

    setlocale(LC_ALL,"Portuguese");

    ff = fopen("funcionario.dat","r+");
    if(ff == NULL){
        ff = fopen("funcionario.dat","w+");
    }

    fd = fopen("departamento.dat","r+");
    if(fd == NULL){
        fd = fopen("departamento.dat","w+");
    }

    fhf = fopen("historicoFuncionario.dat","r+");
    if(fhf == NULL){
        fhf = fopen("historicoFuncionario.dat","w+");
    }

    fhs = fopen("historicoSalario.dat","r+");
    if(fhs == NULL){
        fhs = fopen("historicoSalario.dat","w+");
    }

    fhd = fopen("historicoDepartamento.dat","r+");
    if(fhd == NULL){
        fhd = fopen("historicoDepartamento.dat","w+");
    }

    printf("\t\t\t\tBem Vindo...\n\n");

    do{
        printf("Escolha uma das op��es abaixo:\n1-Cadastro.\n2-Altera��o.\n3-Consultas.\n4-Sair.\n");
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
                opcao = telaConsulta(ff,fd,fhs,&dep,&func,&hd,&hf,&hs);
                limpaTela();
                break;

            case 4:
                sair();
                break;

            default:
                printf("\nOp��o inv�lida.");
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
        printf("Escolha uma das op��es abaixo:\n1-Cadastrar Funcion�rio.\n2-Cadastrar Departamento.\n3-Voltar.\n");
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
                return 0;/*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/

            default:
                printf("\nOp��o inv�lida!!\n");
                break;
        };
    }while(opcao < 1 || opcao > 3);

    return 0;/*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/
}

int telaAlteracoes(FILE *ff,FILE *fd,FILE *fhd,FILE *fhs,FILE *fhf, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das op��es abaixo:\n1-Alterar Dados do Funcion�rio.\n2-Alterar Sal�rio do Funcion�rio.\
        \n3-Alterar Departamento de Funcion�rio.\n4-Alterar Gerente do Departamento.\n5-Voltar.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                opcao = alterarFuncionario(ff,fd,fhf,fhs);
                limpaTela();
                break;

            case 2:
                opcao = alterarSalario(ff,fhs);
                limpaTela();
                break;

            case 3:
                opcao = alterarDepartamentoFunc(ff,fd,fhf);
                limpaTela();
                break;

            case 4:
                opcao = alterarGerenteDep(ff,fd,fhd);
                limpaTela();
                break;

            case 5:
                return 0; /*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/

            default:
                printf("\nOp��o inv�lida!!");
                break;
        };
    }while(opcao < 1 || opcao > 5);

    return 0; /*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/
}

int telaConsulta(FILE *ff, FILE *fd, FILE *fhs, TDepartamento *dep, TFuncionario *func, HistoricoDepartamento *hd, HistoricoFuncionario *hf, HistoricoSalario *hs){
    unsigned short int opcao;
    char mat[10];
    limpaTela();

    do{
        printf("Escolha uma das op��es abaixo:\n1-Consultar dados do Funcion�rio.\n2-Consultar Dados dos Gerentes.\n3-Gerar Folha de pagamento.\
        \n4-Gerar hist�rico de um per�odo.\n5-Gerar relat�rio de funcion�rios por departamento.\n6-Voltar.\n");
        scanf("%hu",&opcao);

        switch(opcao){
            case 1:
                getMatricula(mat);
                opcao = consultaFuncionario(ff,fd,mat);
                limpaTela();
                break;
            case 2:
                opcao = dadosDosGerentes(ff,fd);
                limpaTela();
                break;
            case 3:
                opcao = gerarFolhaPagamento(ff);
                limpaTela();
                break;
            case 4:
                opcao = geraHistoricoPeriodo(ff,fhs);
                limpaTela();
                break;
            case 5:
                opcao = relatorioFuncionario(ff,fd);
                limpaTela();
                break;
            case 6:
                return 0; /*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/
            default:
                printf("\nOp��o inv�lida!!");
                break;
        };
    }while(opcao < 1 || opcao > 6);

    return 0;/*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/
}


