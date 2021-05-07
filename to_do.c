//STABLE 1.43

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
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

void salva_tarefa(struct tarefa *tarefa);
struct tarefa * cria_tarefa();
void consulta_tarefas();
int valida_inteiro(char *entrada);







/*---------------------------------------- I/O Binário ----------------------------------------*/
long int seleciona_tarefa(){
    long id;
    consulta_tarefas();
    printf("\n\nDigite o ID da tarefa (número que aparece acima): ");
    scanf("%ld", &id);
    while ((getchar()) != '\n');
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
            //fprintf(stderr, " PONTO 1 ");
            edit->id = task.id;
            //fprintf(stderr, " PONTO 2 ");
            fwrite(edit, sizeof(struct tarefa), 1, bin_ptr_temp);
            //fprintf(stderr, " PONTO 3 ");
            free(edit);
            //fprintf(stderr, " PONTO 4 ");
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
        printf("Erro ao salvar as mudanças, tente novamente");
    }else{
        fseek(bin_ptr, 0L, SEEK_END);
        long tamanho_arquivo = ftell(bin_ptr);
        tarefa->id = tamanho_arquivo/sizeof(struct tarefa);
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
/*---------------------------------------------------------------------------------------------*/











/*---------------------------------------- I/O Usuário ----------------------------------------*/
struct tarefa * cria_tarefa(){
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(*tarefa));
    char buffer[100];
    int ind;

    printf("Digite a categoria de seu compromisso (apenas os 190 primeiros caracteres serão salvos):\n");
    fgets(tarefa->categoria, 200, stdin);
    if(strlen(tarefa->categoria) >190){
        while ((getchar()) != '\n');
        fflush(stdin);
    }


    if(strlen(tarefa->categoria) > 190){
        do{
            printf("PUTS! Você gosta de escrever, hein... sua categoria deve ser menor!:(\nDigite uma nova categoria:\n");
            fgets(tarefa->categoria, 200, stdin);
            if(strlen(tarefa->categoria) >190){
                while ((getchar()) != '\n');
                fflush(stdin);
            }
        }while(strlen(tarefa->categoria) > 190);
    }

    printf("Digite a descrição de seu compromisso (apenas os 190 primeiros caracteres serão salvos):\n");
    fgets(tarefa->descricao, 200, stdin);
    if(strlen(tarefa->descricao) >190){
        while ((getchar()) != '\n');
        fflush(stdin);
    }

   if(strlen(tarefa->descricao) > 190){
        do{
            printf("PUTS! Você gosta de escrever, hein... sua descrição deve ser menor!:(\nDigite uma nova descrição:\n");
            fgets(tarefa->descricao, 200, stdin);
            if(strlen(tarefa->descricao) >190){
                while ((getchar()) != '\n');
                fflush(stdin);
            }
        }while(strlen(tarefa->descricao) > 190);
    }


    printf("Digite um número de 1 a 5 relacionado a prioridade (1 --> Urgente / 5 --> Baixa Import�ncia)\n");
    scanf("%s", buffer);
    while ((getchar()) != '\n');
    fflush(stdin);
    ind = valida_inteiro(buffer);
    tarefa->prioridade = atoi(buffer);

    if ((ind == 1)||(tarefa->prioridade<1 || tarefa->prioridade>5)){
        do{
            printf("PUTS! Parece que sua entrada não é válida para essa categoria! :(\nVocê deve digitar um número de 1 a 5! :)\n");
            scanf("%s", buffer);
            while ((getchar()) != '\n');
            fflush(stdin);
            ind = valida_inteiro(buffer);
            tarefa->prioridade = atoi(buffer);
        }while ((ind == 1)||(tarefa->prioridade<1 || tarefa->prioridade>5));
    }

//Recebe Data
    printf("Digite a data do compromisso com o seguinte formato: dd/mm/aaaa\n");
    scanf("%s", buffer);
    while ((getchar()) != '\n');
    fflush(stdin);

    tarefa->dia = atoi(buffer);
    tarefa->mes = atoi(buffer+3);
    tarefa->ano = atoi(buffer+6);

    if ( (tarefa->dia<1 || tarefa->dia>31)  || (tarefa->mes<1 || tarefa->mes>12)  || (tarefa->ano<1) ){
        do{
            printf("PUTS! Parece que sua entrada não é válida para essa categoria! :(\nVocê deve digitar uma data existente com o seguinte formato: dd/mm/aaaa! :)\n");
            scanf("%s", buffer);
            while ((getchar()) != '\n');
            fflush(stdin);
            tarefa->dia = atoi(buffer);
            tarefa->mes = atoi(buffer+3);
            tarefa->ano = atoi(buffer+6);

        }while ( (tarefa->dia<1 || tarefa->dia>31)  || (tarefa->mes<1 || tarefa->mes>12)  || (tarefa->ano<1) );
    }

    return tarefa;
}
/*--------------------------------------------------------------------------------------------*/










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
    long num_de_tarefas = ftell(bin_ptr);
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
        while(cont<(int) num_de_tarefas){
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

        quicksort(tarefa_ptr, 0, (int) (num_de_tarefas-1));
        
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
            printf("---> %ld\n\n", tarefa->id+1);
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





void consulta_prioridade(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
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
                printf("---> %ld\n\n", tarefa->id+1);
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
                printf("---> %ld\n\n", tarefa->id+1);
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





void consulta_categoria(){

    FILE *bin_ptr = fopen("tarefas.bin", "rb");
    struct tarefa *tarefa = (struct tarefa *) malloc(sizeof(struct tarefa));
    char indicador;
    char entrada[200];
    int cont=0;


    printf("Digite a categoria da(s) tarefa(s) que você deseja pesquisar:\n");
    fgets(entrada, 200, stdin);
    if(strlen(entrada) >190){
        while ((getchar()) != '\n');
        fflush(stdin);
    }


    printf("Seu resultado da busca:\n");
    if(bin_ptr == NULL){
        printf("Erro ao abrir, não existe nenhuma tarefa!!\n");
    }else{
        while(fread(tarefa, sizeof(*tarefa), 1, bin_ptr) != 0){
            if (compara_string(entrada,tarefa->categoria)==0){
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
                printf("---> %ld\n\n", tarefa->id+1);
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
            printf("Selecione uma das consultas para realizar (digite o número da ação):\n1 -> Consultar todas tarefas\n2 -> Consultar tarefas ordenadas\n3 -> Consultar tarefas filtradas\n9 -> Voltar\n");
            scanf("%d", &input);
            while ((getchar()) != '\n');
            if(input==1){
                consulta_tarefas();
            }else if(input==2){
                printf("Selecione o que você quer ordenar (digite o número da ação):\n1 -> Data (ordem crescente)\n2 -> Data (ordem decrescente)\n3 -> Prioridade (crescente)\n4 -> Prioridade (decrescente)\n9 -> Voltar\n");
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
                printf("Selecione o filtro das tarefas que você quer encontrar (digite o número da ação):\n1 -> Por data\n2 -> Por prioridade\n3 -> Por categoria\n9 -> Voltar\n");
                scanf("%d", &input);
                while ((getchar()) != '\n');
                if(input==1){
                    consulta_data();
                }else if(input==2){
                    consulta_prioridade();
                }else if(input==3){
                    consulta_categoria();
                }
            }
        }
    }
}
