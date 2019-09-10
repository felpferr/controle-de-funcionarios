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
        if(strcmp(tf.matricula,mat) == 1)
            return 1;
        }
    return 0;
}

///Gera um valor de ID automaticamente para departamento e funcionário.
int geraID(long id){
    return id ++;
}

/*Essa função garante que o programa não reinicie a contagem de ID's do zero sempre que for executado.
  Ela verifica se há registros no arquivo, se não houver nenhum a contagem seguirá conforme o parâmetro recebido
  na função geraID().*/
long verificaUltimoID(FILE *f,int m/*usado para indicar qual arquivo em que será buscado o ID.*/){
    TFuncionario tf;
    TDepartamento td;
    if(m == 1){
        if(sizeof(f) == 0)
            return 0;
        fseek(f,-sizeof(tf),SEEK_END);
        fread(&tf,sizeof(tf),1,f);
        return tf.id;
    }
    else{
        if(sizeof(f) == 0)
            return 0;
        fseek(f,-sizeof(td),SEEK_END);
        fread(&td,sizeof(td),1,f);
        return tf.id;
    }
}

///Verificar se essa função funciona depois.
int validaData(char data[]){
    char token[11];
    unsigned short int dia,mes,ano;
    /*
    strcpy(dia,strtok(data,"/"));
    strcpy(mes,strtok(data,"/"));
    strcpy(ano,strtok(data,"/"));
    */
    //Caso o sprintf não funcione descomentar e usar o cast normal usando a função itoa().
    dia = (int)strtok(data,"/");
    strcpy(token,strtok(data,"/"));
    mes = (int)strtok(token,"/");
    strcpy(token,strtok(token,"/"));
    ano = (int)strtok(token,"/");

    //Verificar se essa verificação funciona depois.
    if( (dia >= 1 && dia <= 31)  && (mes >= 1 && mes <= 12) && (ano >= 1960)){
        if(dia <= 20 && mes <= 6 && ano <=1960)
            return 0;
        if(ano > 2019)
            return 0;
    }
    return 1;
}

int validaCPF(char cpf[]){
    int icpf[11];
    int i,somador = 0,digi1,result1,result2,digi2,valor;

    //Efetua a conversao de array de char para um array de int.
    for(i = 0; i < 11; i++)  {
        icpf[i] = cpf[i]-48;
    }
    for(i = 0; i < 10; i++){
        if((icpf[i] == icpf[i+1]) && (icpf[i+1] == icpf[i+2]))
            return 0;
    }
    //PRIMEIRO DIGITO.
    for(i = 0; i < 9; i++){
        somador += icpf[i] * (10-i);
    }
    result1=somador%11;
    if( (result1==0) || (result1==1) ){
        digi1=0;
    }
    else{
        digi1 = 11 - result1;
    }
    //SEGUNDO DIGITO.
    somador = 0;
    for(i = 0; i < 10; i++){
        somador += icpf[i] * (11-i);
    }

    valor = (somador/11) * 11;
    result2 = somador - valor;

    if( (result2 == 0) || (result2 == 1) ){
        digi2 = 0;
    }
    else{
        digi2 = 11 - result2;
    }
    //RESULTADOS DA VALIDACAO.
    if((digi1 == icpf[9]) && (digi2 == icpf[10])){///CPF Válido.
            return 1;
    }
    else{///CPF Inválido.
        return 2;
    }

}

int coletaOpcao(){
    int op;
    printf("\nDeseja continuar?\n1-Sim\n2-Não");
    scanf("%d",&op);
    if(op < 1 || op > 2)
        do{
            printf("\nOpção inválida. Forneça uma correta:");
            scanf("%d",&op);
        }while(op < 1 || op > 2);
    return op;
}

int arquivoVazio(FILE *f){
    fseek(f,0,SEEK_END);
    if(ftell(f)-1 == 0)
        return 0;
    else
        return 1;
}

///Verifica se um id(de funcionário ou departamento) existe. Retorna 1 caso existir e 0 caso não exista.
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

void msg01(){
    printf("Campos precedidos por * são obrigatórios!!\n\n");
}
