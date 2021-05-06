#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct tarefa{
    long id;
    char descricao[200];
    int dia;
    int mes;
    int ano;
    int prioridade;
    char categoria[200];
};









/*---------------------------------------- I/O Binário ----------------------------------------*/
void exclui_tarefa(){

}





void edita_tarefa(){

}





void salva_tarefa(struct tarefa *tarefa){
    FILE *bin_ptr = NULL;
    bin_ptr = fopen("tarefas.bin", "ab");

    if(bin_ptr == NULL){
        printf("Erro ao salvar as mudan�as, tente novamente");
    }else{
        int tamanho_arquivo = ftell(bin_ptr);
        tarefa->id = tamanho_arquivo/424;
        fwrite(tarefa, sizeof(*tarefa), 1, bin_ptr);
        fclose(bin_ptr);
    }
}
/*---------------------------------------------------------------------------------------------*/



/*---------------------------------------- Comparações de String -------------------------------*/
char * remove_espacos(char * saida, char * entrada){
    int k=0;
    int i=0;
    for (i=0; i <= strlen(entrada) ; i++){
        if(!isspace(entrada[i])){
            saida[k++]=entrada[i];
        }
    }
    saida[k]=0;
    return saida;
}

int compara_string(char * primeira, char * segunda){
    int i=0;
    int ind=0;

    char primeira_limpa [200] = {0};
    char segunda_limpa [200] = {0};

    remove_espacos(primeira_limpa, primeira);
    remove_espacos(segunda_limpa, segunda);

    for (i=0; i <= strlen(primeira_limpa) ; i++){
        if((tolower(primeira_limpa[i])) != (tolower(segunda_limpa[i]))){
            ind=1;
        }
    }
    return ind;
}





/*---------------------------------------- Validações -----------------------------------------*/
int valida_inteiro(char *entrada){
    int i;
    int verif;
    int retorno = 0;
    for(i = 0; i < strlen(entrada); i++){
        if(entrada[i] >= '0' && entrada[i] <='9'){
            verif = entrada[i] - '0';
        }else{
            retorno = 1;
        }
    }
    return retorno;
}
/*---------------------------------------------------------------------------------------------*/










/*---------------------------------------- I/O Usuário ----------------------------------------*/
struct tarefa * cria_tarefa(){
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(*tarefa));
    char buffer[100];
    int ind;

    printf("Digite a categoria de seu compromisso (apenas os 200 primeiros caracteres serão salvos):\n");
    fgets(tarefa->categoria, 1000, stdin);
    fflush(stdin);

    if(strlen(tarefa->categoria) > 200){
        do{
            printf("PUTS! Você gosta de escrever, hein... sua categoria deve ser menor!:(\nDigite uma nova categoria:\n");
            fgets(tarefa->categoria, 600, stdin);
            fflush(stdin);
        }while(strlen(tarefa->categoria) > 200);
    }


    printf("Digite a descrição de seu compromisso:\n");
    fgets(tarefa->descricao, 1000, stdin);
    fflush(stdin);

   if(strlen(tarefa->descricao) > 200){
        do{
            printf("PUTS! Você gosta de escrever, hein... sua descrição deve ser menor!:(\nDigite uma nova descrição:\n");
            fgets(tarefa->descricao, 1000, stdin);
            fflush(stdin);
        }while(strlen(tarefa->descricao) > 200);
    }


    printf("Digite um número de 1 a 5 relacionado a prioridade (1 --> Urgente / 5 --> Baixa Import�ncia)\n");
    scanf("%s", buffer);
    fflush(stdin);
    ind = valida_inteiro(buffer);
    tarefa->prioridade = atoi(buffer);

    if ((ind == 1)||(tarefa->prioridade<1 || tarefa->prioridade>5)){
        do{
            printf("PUTS! Parece que sua entrada n�o � v�lida para essa categoria! :(\nVocê deve digitar um número de 1 a 5! :)\n");
            scanf("%s", buffer);
            fflush(stdin);
            ind = valida_inteiro(buffer);
            tarefa->prioridade = atoi(buffer);
        }while ((ind == 1)||(tarefa->prioridade<1 || tarefa->prioridade>5));
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










/*---------------------------------------- Ordenações ----------------------------------------*/

/*--------------------------------------------------------------------------------------------*/










/*---------------------------------------- Consultas -----------------------------------------*/
void consulta_tarefas(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;



    if(bin_ptr == NULL){
        printf("Erro ao abrir, não existe nenhuma tarefa!!\n");
    }else{
        while(fread(tarefa, sizeof(*tarefa), 1, bin_ptr) != 0){
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf("---> %ld\n\n", tarefa->id+1);
            printf("- Categoria: %s\n", tarefa->categoria);
            printf("- Descrição: %s\n", tarefa->descricao);
            printf("- Prioridade: %d\n\n", tarefa->prioridade);
            printf("- Data: %02d/%02d/%d\n\n", tarefa->dia, tarefa->mes, tarefa->ano);
        }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(bin_ptr);
    }
}

void consulta_prioridade(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;
    char buffer[100];
    int ind;
    int entrada;
    int cont=0;

    printf("Digite a prioridade da(s) tarefa(s) que você deseja pesquisar (1 --> Urgente / 5 --> Baixa Import�ncia):\n");
    scanf("%s", buffer);
    fflush(stdin);
    ind = valida_inteiro(buffer);
    entrada = atoi(buffer);
    if ((ind == 1)||(entrada<1 || entrada>5)){
        do{
            printf("PUTS! Parece que essa prioridade não é válida...! :(\nVocê deve digitar um número de 1 a 5! :)\n");
            scanf("%s", buffer);
            fflush(stdin);
            ind = valida_inteiro(buffer);
            entrada = atoi(buffer);
        }while ((ind == 1)||(entrada<1 || entrada>5));
    }

    printf("Seu resultado da busca:\n");
    if(bin_ptr == NULL){
        printf("Erro ao abrir, não existe nenhuma tarefa!!\n");
    }else{
        while(fread(tarefa, sizeof(*tarefa), 1, bin_ptr) != 0){
            if (entrada == tarefa->prioridade){
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
                printf("- Categoria: %s\n", tarefa->categoria);
                printf("- Descrição: %s\n", tarefa->descricao);
                printf("- Prioridade: %d\n\n", tarefa->prioridade);
                printf("- Data: %02d/%02d/%d\n\n", tarefa->dia, tarefa->mes, tarefa->ano);
                cont++;
            }
        }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if(cont == 0){
        printf("Parece que sua busca não obteve resultados, amigão... :(\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else if(cont==1){
        printf("Sua  busca obteve 1 único resultado!\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else{
        printf("Sua busca obteve %d resultados!\n", cont);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(bin_ptr);
    }
}

void consulta_data(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;
    char buffer[100];
    int ind;
    int entrada_dia;
    int entrada_mes;
    int entrada_ano;
    int cont=0;

    printf("Digite a data da(s) tarefa(s) que você deseja pesquisar (no formato dd/mm/aaaa):\n");
    scanf("%s", buffer);
    fflush(stdin);

    entrada_dia = atoi(buffer);
    entrada_mes = atoi(buffer+3);
    entrada_ano = atoi(buffer+6);

    if ((entrada_dia<1 ||entrada_dia>31)  || (entrada_mes<1 || entrada_mes>12)  || (entrada_ano<1)){
        do{
            printf("PUTS! Parece que essa data não é válida...! :(\nVocê deve digitar uma data no formato dd/mm/aaaa! :)\n");
            scanf("%s", buffer);
            fflush(stdin);
            ind = valida_inteiro(buffer);
            entrada_dia = atoi(buffer);
            entrada_mes = atoi(buffer+3);
            entrada_ano = atoi(buffer+6);
        }while ((entrada_dia<1 ||entrada_dia>31)  || (entrada_mes<1 || entrada_mes>12)  || (entrada_ano<1));
    }

    printf("Seu resultado da busca:\n");
    if(bin_ptr == NULL){
        printf("Erro ao abrir, não existe nenhuma tarefa!!\n");
    }else{
        while(fread(tarefa, sizeof(*tarefa), 1, bin_ptr) != 0){
            if ((entrada_dia == tarefa->dia)&&(entrada_mes == tarefa->mes)&&(entrada_ano == tarefa->ano)){
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
                printf("- Categoria: %s\n", tarefa->categoria);
                printf("- Descrição: %s\n", tarefa->descricao);
                printf("- Prioridade: %d\n\n", tarefa->prioridade);
                printf("- Data: %02d/%02d/%d\n\n", tarefa->dia, tarefa->mes, tarefa->ano);
                cont++;
            }
        }

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if(cont == 0){
        printf("Parece que sua busca não obteve resultados, amigão... :(\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else if(cont==1){
        printf("Sua  busca obteve 1 único resultado!\n");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    else{
        printf("Sua busca obteve %d resultados!\n", cont);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    fclose(bin_ptr);
    }
}
/*--------------------------------------------------------------------------------------------*/











void main(){

    int input=0;
    while(input!=5){
        printf("Selecione uma das ações para realizar (digite o número da ação):\n1 -> Inserir nova tarefa\n2 -> Editar uma tarefa\n3 -> Excluir uma tarefa\n4 -> Consultar tarefas\n5 -> Encerrar sessão\n");
        scanf("%d", &input);
        while ((getchar()) != '\n');
        if(input==1){
            struct tarefa *tarefa = cria_tarefa();
            salva_tarefa(tarefa);
        }else if(input==2){
            edita_tarefa();
        }else if(input==3){
            exclui_tarefa();
        }else if(input==4){
            consulta_tarefas();
        }
        else if(input==7){
            consulta_data();
        }
    }
}
