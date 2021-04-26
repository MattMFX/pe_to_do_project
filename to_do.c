#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct to_do_list{
    //long id ou char *titulo;
    char *descricao;
    struct tm *data;
    enum prioridade {Urgente=1, Alta_prioridade=2, Normal=3, Baixa_prioridade=4} prioridade;
    char *categoria;
};

//void salva_tarefa(struct to_do_list *lista)

//void exclui_tarefa(id ou titulo)

//struct to_do_list *lista cria_tarefa(void)

//void consulta_tarefas()





























/*void salva_lista(){
    //FILE *fptr = fopen("lista.bin", "ab");
}

void main(){
    struct to_do_list list;
    time_t tempo;
    char *data;

    time(&tempo);
    list.data = localtime(&tempo);
    strftime(data, 11, "%d/%m/%Y", list.data);

    printf("Current local time and date: %s", list.data);
}
*/