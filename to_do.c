//STABLE 1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tarefa{
    long id;
    char descricao[200];
    int dia;
    int mes;
    int ano;
    int prioridade;
    char categoria[200];
};

void salva_tarefa(struct tarefa *tarefa);










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










/*---------------------------------------- I/O Binário ----------------------------------------*/
long int seleciona_tarefa(){
    long id;
    consulta_tarefas();
    printf("\n\nDigite o ID da tarefa: ");
    scanf("%ld", &id);
    fflush(stdin);
    return id-1;
}



void exclui_tarefa(){
    long id = seleciona_tarefa();

    rename("tarefas.bin", "tarefas_deprecated.bin");

    FILE *bin_ptr_temp = fopen("tarefas.bin", "wb+");
    FILE *bin_ptr = fopen("tarefas_deprecated.bin", "rb");

    struct tarefa task;
    while(fread(&task, sizeof(struct tarefa), 1, bin_ptr)){
        if(task.id!=id){
            salva_tarefa(&task);
        }
    }

    fclose(bin_ptr);
    fclose(bin_ptr_temp);
    remove("tarefas_deprecated.bin");
}


void edita_tarefa(){
    long id = seleciona_tarefa();

    FILE *bin_ptr_temp = fopen("tarefas_temp.bin", "wb+");
    FILE *bin_ptr = fopen("tarefas.bin", "rb");

    struct tarefa task;
    while(fread(&task, sizeof(struct tarefa), 1, bin_ptr)){
        if(task.id!=id){
            fwrite(&task, sizeof(struct tarefa), 1, bin_ptr_temp);
        }
        else{
            struct tarefa *edit = cria_tarefa();
            fprintf(stderr, " PONTO 1 ");
            edit->id = task.id;
            fprintf(stderr, " PONTO 2 ");
            fwrite(edit, sizeof(struct tarefa), 1, bin_ptr_temp);
            fprintf(stderr, " PONTO 3 ");
            free(edit);
            fprintf(stderr, " PONTO 4 ");
        }
    }

    fclose(bin_ptr);
    fclose(bin_ptr_temp);
    remove("tarefas.bin");
    rename("tarefas_temp.bin", "tarefas.bin");
}





void salva_tarefa(struct tarefa *tarefa){
    FILE *bin_ptr = NULL;
    bin_ptr = fopen("tarefas.bin", "ab");

    if(bin_ptr == NULL){
        printf("Erro ao salvar as mudan�as, tente novamente");
    }else{
        fseek(bin_ptr, 0L, SEEK_END);
        long tamanho_arquivo = ftell(bin_ptr);
        tarefa->id = tamanho_arquivo/sizeof(struct tarefa);
        fwrite(tarefa, sizeof(*tarefa), 1, bin_ptr);
        fclose(bin_ptr);
    }
}
/*---------------------------------------------------------------------------------------------*/










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







/*---------------------------------------- Ordenações ----------------------------------------*/

/*--------------------------------------------------------------------------------------------*/










/*---------------------------------------- Consultas -----------------------------------------*/
void consulta_tarefas(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;

    //Se o fopen retornar nulo, o arquivo n�o existe

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
        }else if(input==7){
            exclui_tarefa();
        }else if(input==8){
            edita_tarefa();
        }
    }
}
