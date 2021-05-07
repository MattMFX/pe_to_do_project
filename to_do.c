//STABLE 1.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
int particiona(long **tarefa_ptr, int comeco, int fim){
    int pivot = comeco;
    int l=comeco, r=fim;
    bool troca_sentido = false;

    while(l<=r){
        if(!troca_sentido){
            if(tarefa_ptr[pivot][1]>tarefa_ptr[r][1]){
                long *aux_ptr = tarefa_ptr[pivot];
                tarefa_ptr[pivot] = tarefa_ptr[r];
                tarefa_ptr[r] = aux_ptr;
                pivot=r;
                troca_sentido = true;
            }
            r--;
        }else{
            if(tarefa_ptr[pivot][1]<tarefa_ptr[l][1]){
                long *aux_ptr = tarefa_ptr[pivot];
                tarefa_ptr[pivot] = tarefa_ptr[l];
                tarefa_ptr[l] = aux_ptr;
                pivot=l;
                troca_sentido = false;
            }
            l++;
        }
    }
    
    return pivot;
}

void quicksort(long **tarefa_ptr, int comeco, int fim){
    int pivot =0;

    if(comeco<fim){
        pivot = particiona(tarefa_ptr, comeco, fim);
        quicksort(tarefa_ptr, comeco, pivot-1);
        quicksort(tarefa_ptr, pivot+1, fim);
    }
}
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





void consulta_ordenada(int params, int ordem){
    FILE *bin_ptr;
    bin_ptr = fopen("tarefas.bin", "ab");
    int num_de_tarefas = ftell(bin_ptr);
    num_de_tarefas = num_de_tarefas/sizeof(struct tarefa);
    fclose(bin_ptr);

    FILE *bin_ptr2;
    bin_ptr2 = fopen("tarefas.bin", "rb");

    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    long **tarefa_ptr = (long **) malloc(sizeof(long *)*num_de_tarefas);
    
    if(bin_ptr2 == NULL){
        printf("Erro ao abrir, não existe nenhuma tarefa!!\n");
    }else{
        int cont=0;
        while(cont<num_de_tarefas){
            fread(tarefa, sizeof(struct tarefa), 1, bin_ptr2);
            long *tarefa_id = (long *) malloc(sizeof(long)*2);
            tarefa_id[0] = tarefa->id;
            if(params==0){
                tarefa_id[1] = (long) (tarefa->ano*10000 + tarefa->mes*100 + tarefa->dia);
            }else if(params==1){
                tarefa_id[1] = (long) tarefa->prioridade;
            }
            tarefa_ptr[cont] = tarefa_id;
            cont++;
        }

        quicksort(tarefa_ptr, 0, num_de_tarefas-1);
        
        bool iterou = false;
        int i;
        if(ordem==0){
            i=0;
        }else{
            i=cont-1;
        }

        while(!iterou){
            fseek(bin_ptr2, (tarefa_ptr[i][0]*sizeof(struct tarefa)), SEEK_SET);
            fread(tarefa, sizeof(*tarefa), 1, bin_ptr2);
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            printf("- Categoria: %s\n", tarefa->categoria);
            printf("- Descrição: %s\n", tarefa->descricao);
            printf("- Prioridade: %d\n\n", tarefa->prioridade);
            printf("- Data: %02d/%02d/%d\n\n", tarefa->dia, tarefa->mes, tarefa->ano);
            if(ordem==0 && i==cont-1){
                iterou=true;
            }else if(ordem==1 && i==0){
                iterou=true;
            }else if(ordem==0 && i<cont-1){
                i++;
            }else if(ordem==1 && i>0){
                i--;
            }
        }

        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fclose(bin_ptr2);
    }
}
/*--------------------------------------------------------------------------------------------*/










void main(){

    int input=0;
    printf("%ld", sizeof(long));
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
            printf("Selecione uma das consultas para realizar (digite o número da ação):\n1 -> Consultar todas tarefas\n2 -> Consultar tarefas ordenadas\n3 -> Consultar tarefas filtradas\n4 -> Voltar\n");
            scanf("%d", &input);
            while ((getchar()) != '\n');
            if(input==1){
                consulta_tarefas();
            }else if(input==2){
                printf("Selecione o que você quer ordenar (digite o número da ação):\n1 -> Data (ordem crescente)\n2 -> Data (ordem decrescente)\n3 -> Prioridade (crescente)\n4 -> Prioridade (decrescente)\n5 -> Voltar\n");
                scanf("%d", &input);
                while ((getchar()) != '\n');
                if(input==1){
                    consulta_ordenada(0, 0);
                }else if(input==2){
                    consulta_ordenada(0, 1);
                }else if(input==3){
                    consulta_ordenada(1, 0);
                }else if(input==4){
                    consulta_ordenada(1, 1);
                }
            }else if(input==3){
                
            }else if(input==4){
                main();
            }
        }
    }
}
