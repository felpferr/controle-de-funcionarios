#include <stdio.h>
#include "general.h"
#include "telas.h"
#include "funcionario.h"
#include "departamento.h"

void inicio(){
    unsigned short int opcao;
    geral g;
    HistoricoDepartamento hd;
    HistoricoFuncionario hf;
    HistoricoSalario hs;
    TDepartamento dep;
    TFuncionario func;

    setlocale(LC_ALL,"Portuguese");

    printf("\t\t\t\tBem Vindo\n");

    do{
        printf("Escolha uma das op��es abaixo:1-Cadastro.\n2-Altera��o.\n3-Consultas.\n4-Sair.");
        scanf("%d",&opcao);

        switch{
            case 1:
                telaCadastros(&g,&dep,&func);
                break;

            case 2:
                telaAlteracoes(&g,&dep,&func);
                break;

            case 3:
                telaConsulta(&g,&dep,&func,&hd,&hf,&hs);
                break;

            case 4:
                sair();
                break;

            default:
                break;
        };
    }while(opcao < 1 || opcao > 4);
}

int telaCadastros(geral *g, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das op��es abaixo:\n1-Cadastrar Funcion�rio.\n2-Cadastrar Departamento.\n3-Voltar.");
        scanf("%d",&opcao);

        switch{
            case 1:

                cadastroFuncionario(g);
                break;

            case 2:
                cadastroDepartamento();
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

int telaAlteracoes(geral *g, TDepartamento *dep, TFuncionario *func){
    unsigned short int opcao;

    limpaTela();

    do{
        printf("Escolha uma das op��es abaixo:\n1-Alterar Dados do Funcion�rio.\n2-Alterar Sal�rio do Funcion�rio.\
        \n3-Alterar Departamento de Funcion�rio.\n4-Alterar Gerente do Departamento.\n5-Voltar.\n\n");
        scanf("%d",&opcao);

        switch{
            case 1:
                alterarFuncionario();
                break;

            case 2:
                alterarSalario();
                break;

            case 3:
                alterarDepartamentoFunc();
                break;

            case 4:
                alterarGerenteDep();
                break;

            case 5;
                return 0; /*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/

            default:
                printf("\nOp��o inv�lida!!");
                break;
        };
    }while(opcao < 1 || opcao > 5);

    return 0; /*� retornado um valor que fa�a o loop(do/while) da fun��o inicio() seja reiniciado.*/
}

int telaConsulta(geral *g, TDepartamento *dep, TFuncionario *func, HistoricoDepartamento *hd, HistoricoFuncionario *hf, HistoricoSalario *hs){
    unsigned short int opcao;

    openFile(g.funcionario)
    limpaTela();

    do{
        printf("Escolha uma das op��es abaixo:\n1-Consultar dados do Funcion�rio.\n2-Consultar Dados dos Gerentes.\n3-Gerar Folha de pagamento.\
        \n4-Gerar hist�rico de um per�odo.\n5-Gerar relat�rio de funcion�rios por departamento.\n6-Voltar.\n\n");

        switch(opcao){
            case 1:
                consultaFuncionario();
                break;
            case 2:
                dadosDosGerentes();
                break;
            case 3:
                gerarFolhaPagamento();
                break;
            case 4:
                geraHistoricoPeriodo();
                break;
            case 5:
                relatorioFuncionario();
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


