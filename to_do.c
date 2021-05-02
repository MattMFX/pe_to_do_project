#include <stdio.h>
#include <stdlib.h>
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

void salva_tarefa(struct tarefa *lista){
    printf("%s", lista->descricao);

    FILE *bin_ptr = fopen("tarefas.bin", "ab+");

    struct tarefa *tar = (struct tarefa *) malloc(8);

    fwrite(lista, 8, 1, bin_ptr);
    fread(tar, 8, 1, bin_ptr);

    printf("%s", tar->descricao);

    fclose(bin_ptr);
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

    printf("Digite o número relacionado a prioridade de seu compromisso(Urgente=1, Alta_prioridade=2, Normal=3, Baixa_prioridade=4):\n");
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

    /* Se o fopen retornar nulo, o arquivo não existe */

    if(bin_prt == NULL){
        printf("Erro ao abrir, o arquivo binário está vazio!!\n");
        exit(1);
    }

    while((indicador = fgetc(bin_ptr)) != EOF){

    }


    fclose(bin_ptr);
}

void main(){
    /*struct tarefa *tarefas1 = (struct tarefa *) malloc(8);
    struct tarefa *tarefas2 = (struct tarefa *) malloc(8);
    struct tarefa *tarefas3 = (struct tarefa *) malloc(8);
    struct tarefa *tarefas4 = (struct tarefa *) malloc(8);

    tarefas1->descricao = "tarefa";
    tarefas2->descricao = "tarefa";
    tarefas3->descricao = "tarefa";
    tarefas4->descricao = "tarefa";

    salva_tarefa(tarefas1);
    salva_tarefa(tarefas2);
    salva_tarefa(tarefas3);
    salva_tarefa(tarefas4);*/
}


//struct tarefa *lista cria_tarefa(void)


