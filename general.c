#include <stdio.h>
#include <string.h>
#include "general.h"
#include "funcionario.h"
#include "departamento.h"

void sair(){
    exit(0);
}

void limpaTela(){
    system("cls || clear");
}

int openFile(FILE *arq,char nome[], char MODO[]){
    arq = fopen(nome,MODO);
    if(!arq){
        /*printf("\nErro na abertura do arquivo. Com %s.",&MODO);*/
        return 0;
    }
    else
        return 1;
}

int removeBarraN(char palavra[]){
    if(palavra[strlen(palavra)-1] == '\n')
       palavra[strlen(palavra)-1] = '\0';
    return 1;
}

int pesquisaMat(char mat[], FILE *arq){
    TFuncionario tf;

    fseek(arq,0,SEEK_SET);
    while(fread(&tf,sizeof(tf),1,arq) == 1){
        if(strcmp(tf.matricula,mat) == 0)
            return 1;
        }
    return 0;
}

///Gera um valor de ID automaticamente para departamento e funcion�rio.
long geraID(long id){
    return ++id;
}

/*Essa fun��o garante que o programa n�o reinicie a contagem de ID's do zero sempre que for executado.
  Ela verifica se h� registros no arquivo, se n�o houver nenhum a contagem seguir� conforme o par�metro recebido
  na fun��o geraID().*/
long verificaUltimoID(FILE *f,int m/*usado para indicar qual arquivo em que ser� buscado o ID.*/){
    TFuncionario tf;
    TDepartamento td;
    long contador = 0;
    fseek(f,1,SEEK_SET);
    if(m==1){
        while(fread(&tf, sizeof(tf), 1,f) == 1)
            contador++;
    }
    else
        while(fread(&td, sizeof(td), 1,f))
            contador++;
    return contador;
}

///Verificar se essa fun��o funciona depois.(n�o funciona)
int validaData(char data[]){
    char token[11];
    unsigned short int dia,mes,ano;
    /*
    strcpy(dia,strtok(data,"/"));
    strcpy(mes,strtok(data,"/"));
    strcpy(ano,strtok(data,"/"));
    */
    //Caso o sprintf n�o funcione descomentar e usar o cast normal usando a fun��o itoa().
    dia = (int)strtok(data,"/");
    strcpy(token,strtok(data,"/"));
    mes = (int)strtok(token,"/");
    strcpy(token,strtok(token,"/"));
    ano = (int)strtok(token,"/");

    //Verificar se essa verifica��o funciona depois.
    if( (dia >= 1 && dia <= 31)  && (mes >= 1 && mes <= 12) && (ano >= 1960)){
        if(dia <= 20 && mes <= 6 && ano <=1960)
            return 0;
        if(ano > 2019)
            return 0;
    }
    return 1;
}

int validaCPF(char cpf[]){
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os n�meros iguais ele � inv�lido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os n�meros de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 n�o for o mesmo que o da valida��o CPF � inv�lido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os n�meros de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 n�o for o mesmo que o da valida��o CPF � inv�lido
        }
    }
    return 1;
}

int coletaOpcao(){
    int op;

    promptUniversal();
    printf("\nDeseja continuar?\n1-Sim\n2-N�o");
    scanf("%d",&op);
    if(op < 1 || op > 2)
        do{
            promptUniversal();
            printf("\nOp��o inv�lida. Forne�a uma correta:");
            scanf("%d",&op);
        }while(op < 1 || op > 2);
    return op;
}

int arquivoVazio(FILE *f){
    fseek(f,0,SEEK_END);
    if(ftell(f) == 0)
        return 0;
    else
        return 1;
}

///Verifica se um id(de funcion�rio ou departamento) existe. Retorna 1 caso existir e 0 caso n�o exista.
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

void promptUniversal(){
    getchar();
    setbuf(stdin,NULL);
}

int msg01(){
    printf("Campos precedidos por * s�o obrigat�rios!!\n\n");
    return 1;
}

int msg02(){
    printf("\nN�o h� funcion�rios cadastrados no momento.");
    return 1;
}

int msg03(){
    printf("\nN�o h� departamentos cadastrados no momento.");
    return 1;
}
