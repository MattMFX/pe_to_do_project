#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tarefa{
    long id;
    char descricao[50];
    struct tm *data;
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

//void consulta_tarefas()