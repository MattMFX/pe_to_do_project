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
    enum prioridade {Urgente=1, Alta_prioridade=2, Normal=3, Baixa_prioridade=4} prioridade;
    char categoria[50];
};

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
        tarefa->id = tamanho_arquivo/120;
        fwrite(tarefa, sizeof(*tarefa), 1, bin_ptr); 
        fclose(bin_ptr);
    }
}

void cria_tarefa(){

    struct tarefa *tarefa_local = (struct tarefa *) malloc(sizeof (struct tarefa));
    char descricao_local[50];
    enum prioridade_local {Urgente=1, Alta_prioridade=2, Normal=3, Baixa_prioridade=4} prioridade_local;
    char categoria_local [50];
    char *data = (char *)malloc (20);
    int dia_local=0;
    int mes_local=0;
    int ano_local=0;

    printf("Digite a categoria de seu compromisso:\n ");
    scanf("%s ", categoria_local);

    printf("Digite a descricao de seu compromisso:\n ");
    scanf("%s ", descricao_local);

    printf("Digite o n�mero relacionado a prioridade de seu compromisso(Urgente=1, Alta_prioridade=2, Normal=3, Baixa_prioridade=4):\n");
    scanf("%d ", prioridade_local);

    printf("Digite a data do compromisso com o seguinte formato: dd/mm/aaaa\n");
    scanf("%s", data);

    dia_local = atoi(data);
    mes_local = atoi(data+3);
    ano_local = atoi(data+6);

    tarafas1->categoria = categoria_local;
    tarafas1->descricao = descricao_local;
    tarafas1->prioridade = prioridade_local;
    tarafas1->dia = dia_local;
    tarafas1->mas = mes_local;
    tarafas1->ano = ano_local;
}

void consulta_tarefas(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    char indicador;

    /* Se o fopen retornar nulo, o arquivo n�o existe */

    if(bin_prt == NULL){
        printf("Erro ao abrir, o arquivo bin�rio est� vazio!!\n");
        exit(1);
    }

    while((indicador = fgetc(bin_ptr)) != EOF){

    }


    fclose(bin_ptr);
}

void main(){
    struct tarefa tarefas1;

    strcpy(tarefas1.descricao, "tarefa");
    tarefas1.prioridade = 2;
    strcpy(tarefas1.categoria, "cat1");

    salva_tarefa(&tarefas1);
}


//struct tarefa *tarefa cria_tarefa(void)


