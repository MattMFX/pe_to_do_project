#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tarefa{
    char descricao[50];
    long id;
    //struct tm *data;
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

void main(){
    struct tarefa tarefas1;

    strcpy(tarefas1.descricao, "tarefa");
    tarefas1.prioridade = 2;
    strcpy(tarefas1.categoria, "cat1");

    salva_tarefa(&tarefas1);
}


//struct tarefa *tarefa cria_tarefa(void)

//void consulta_tarefas()