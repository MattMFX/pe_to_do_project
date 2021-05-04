#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tarefa{
    long id;
    char descricao[50];
    int dia;
    int mes;
    int ano;
    int prioridade;
    char categoria[50];
};

/*---------------------------------------- I/O Binário ----------------------------------------*/

void exclui_tarefa(long id){

}

void edita_tarefa(long id){

}

void salva_tarefa(struct tarefa *tarefa){
    FILE *bin_ptr = NULL;
    bin_ptr = fopen("tarefas.bin", "ab");

    if(bin_ptr == NULL){
        printf("Erro ao salvar as mudanças, tente novamente");
    }else{
        int tamanho_arquivo = ftell(bin_ptr);
        tarefa->id = tamanho_arquivo/128;
        fwrite(tarefa, sizeof(*tarefa), 1, bin_ptr);
        fclose(bin_ptr);
    }
}



/*---------------------------------------------------------------------------------------------*/


/*---------------------------------------- I/O Usuário ----------------------------------------*/


struct tarefa * cria_tarefa(){
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(*tarefa));
    char buffer[100];
    int ind;

//Recebe Categoria
    printf("Digite a categoria de seu compromisso:\n");
    scanf("%s", tarefa->categoria);
    fflush(stdin);

//Recebe Descrição
    printf("Digite a descrição de seu compromisso:\n");
    scanf("%s", tarefa->descricao);
    fflush(stdin);

//Recebe Prioridade
    printf("Digite um número de 1 a 5 relacionado a prioridade (1 --> Urgente / 5 --> Baixa Importância)\n");
    char *entrada = gets(buffer);
    fflush(stdin);
    ind = valida_inteiro(entrada);
    tarefa->prioridade = atoi(buffer);

    if ((ind == NULL)||(tarefa->prioridade<1 || tarefa->prioridade>5)){
        do{
            printf("PUTS! Parece que sua entrada não é válida para essa categoria! :(\nVocê deve digitar um número de 1 a 5! :)\n");
            entrada = gets(buffer);
            fflush(stdin);
            ind = valida_inteiro(entrada);
            tarefa->prioridade = atoi(buffer);
        }while ((ind == NULL)||(tarefa->prioridade<1 || tarefa->prioridade>5));
    }

//Recebe Data
    printf("Digite a data do compromisso com o seguinte formato: dd/mm/aaaa\n");
    scanf("%s", buffer);
    fflush(stdin);

    tarefa->dia = atoi(buffer);
    tarefa->mes = atoi(buffer+3);
    tarefa->ano = atoi(buffer+6);

    if ( (tarefa->dia<1 || tarefa->dia>31)  || (tarefa->mes<1 || tarefa->mes>12)  || (tarefa->ano<1) ){
        do{
            printf("PUTS! Parece que sua entrada não é válida para essa categoria! :(\nVocê deve digitar uma data existente com o seguinte formato: dd/mm/aaaa! :)\n");
            scanf("%s", buffer);
            fflush(stdin);
            tarefa->dia = atoi(buffer);
            tarefa->mes = atoi(buffer+3);
            tarefa->ano = atoi(buffer+6);

        }while ( (tarefa->dia<1 || tarefa->dia>31)  || (tarefa->mes<1 || tarefa->mes>12)  || (tarefa->ano<1) );
    }

    return tarefa;
}

/*--------------------------------------------------------------------------------------------*/




/*---------------------------------------- Validações ----------------------------------------*/
int valida_inteiro(char *entrada){

int i;
int verif;
for(i = 0; i < strlen(entrada); i++){
    if(entrada[i] >= '0' && entrada[i] <='9'){
        verif = entrada[i] - '0';
    }else{
        return NULL;
    }
}

}



/*---------------------------------------- Ordenações ----------------------------------------*/





/*--------------------------------------------------------------------------------------------*/


/*---------------------------------------- Consultas -----------------------------------------*/

void consulta_tarefas(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;

    //Se o fopen retornar nulo, o arquivo não existe

    if(bin_ptr == NULL){
        printf("Erro ao abrir, o arquivo binário está vazio!!\n");
        exit(1);
    }

    printf("         %-50s%-50s%-50s%-12s\n", "Categoria", "Descrição", " Prioridade", "  Data");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while(fread(tarefa, sizeof(*tarefa), 1, bin_ptr) != 0){
        printf("-> %ld", tarefa->id+1);
        printf("     %-50s", tarefa->categoria);
        printf("%-50s", tarefa->descricao);
        printf("%-50d", tarefa->prioridade);
        printf("%d/%d/%d\n", tarefa->dia, tarefa->mes, tarefa->ano);
    }

    fclose(bin_ptr);
}

/*--------------------------------------------------------------------------------------------*/

void main(){
    //struct tarefa *tarefa = cria_tarefa();
    //salva_tarefa(tarefa);
    //consulta_tarefas();
    //cria_tarefa();
}


//struct tarefa *tarefa cria_tarefa(void)


