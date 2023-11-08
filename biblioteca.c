#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca.h"

///////////// funções principais /////////////
void printMenu(){ // usada para printar o menu toda vez que acontece alguma ação no programa
    printf("\nGerenciador de Tarefas\n");
    printf("Escolha a funcao:\n 1. Adicionar nova tarefa\n 2. Deletar tarefa\n 3. Listar tarefas\n 4. Editar tarefa\n 5. Filtrar tarefas por prioridade\n 6. Filtrar tarefas por estado\n 7. Filtrar tarefas por categoria\n 8. Filtrar tarefas por prioridade e categoria\n 9. Exportar tarefas por prioridade\n10. Exportar tarefas por categoria\n11. Exportar tarefas por prioridade e categoria\n 0. Sair\n");
}


int criarTarefa(ListaDeTarefas *lt) { // usada para criar uma nova terefa

    if (lt->qtd < 100) { // se a lista tiver menos que 100 tarefas, a função pede a categoria, a desrição, a prioridade e o status da nova tarefa e armazena no struct
        printf("\nDigite a categoria: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].categoria);
        clearBuffer();
        
        printf("Digite a descricao: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].descricao);
        clearBuffer();

        printf("Digite a prioridade (0 a 10): ");
        scanf(" %d", &lt->tarefas[lt->qtd].prioridade);
        clearBuffer();

        printf("Digite o status da tarefa (completo / em andamento / nao iniciado): ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].status);
        clearBuffer();

        printf("Tarefa adicionada com sucesso!\n");
    }
    else{ // caso o struct ja tenha 100 tarefas
        printf("Sua lista de tarefas esta cheia!");
    }
    lt->qtd++;// estrutura que pula pra proxima linha do arquivo para que o usuario nao salve as novas tarefas em cima das outras
    return 0;
}

int DeletarTarefa(ListaDeTarefas *lt){ // função que deleta uma terefa
    int tarefaEscolhida;
    printf("\nDigite a terefa que deseja deletar (de 0 a %d): ",lt->qtd - 1); // o usuario informa a tarefa a ser deletada
    scanf("%d", &tarefaEscolhida);
    clearBuffer();

    if(tarefaEscolhida > lt->qtd){ // confere se a tarefa digitada existe
        printf("Digite um numero valido.");
        return 1;
    }

    for (int i = tarefaEscolhida; i < 100; i++){ // ao deletar uma tarefa, as posições das restantes devem "descer" para uma posição abaixo da que estava
        lt->tarefas[i] = lt->tarefas[i + 1];
    }

    lt->qtd--; // atualiza a quantidade de tarefas salvas
    return 0;
}


int ListarTarefa(ListaDeTarefas lt){ // percorre toda a lista de tarefas e printa no terminal
    
    for (int i = 0; i < lt.qtd; i++){ 
        printf("Tarefa %d\n", i);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
        printf("Status: %s\n", lt.tarefas[i].status);
        printf("\n");
    }
    
    return 0;
}

int EditarTarefa(ListaDeTarefas *lt){ // permeite alterar as configurações das tarefas existentes

    int tarefaEscolhida;
    printf("\nDigite o numero da tarefa que deseja editar (0 a %d): ", lt->qtd - 1); // soliciata a tarefa a ser editada
    scanf("%d", &tarefaEscolhida);
    clearBuffer();

    if (tarefaEscolhida > lt->qtd){ // verifica se ela existe
        printf("Digite um numero valido.");
        return 1;
    }

    else{
        int campoAlteracao;
        printf("\nDigite o campo que deseja alterar:\n1. Categoria\n2. Descricao\n3. Prioridade\n4. Status\n>>> "); // solicita o configuração da tarefa a ser editada
        scanf("%d", &campoAlteracao);
        clearBuffer();

        if (campoAlteracao == 1){
            printf("Digite a nova categoria: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].categoria); // sobrescreve a informação que estava pela nova
            clearBuffer();
        }
        else if (campoAlteracao == 2){
            printf("Digite a nova descricao: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].descricao);
            clearBuffer();
        }
        else if (campoAlteracao == 3){
            printf("Digite o novo numero de prioridade: ");
            scanf("%d",  &lt->tarefas[tarefaEscolhida].prioridade);
            clearBuffer();
        }
        else if (campoAlteracao == 4){
            printf("Digite o novo status: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].status);
            clearBuffer();
        }
    }
    return 0;
}

int Filtrar_Prioridade(ListaDeTarefas lt){ // seleciona as tarefas que possuem a prioridade escolhida pelo usuario
    
    int prioridadeEscolhida;
    printf("\nDigite o taxa de prioridade (0 a 10): "); // pede a prioridade
    scanf("%d", &prioridadeEscolhida);
    clearBuffer();

    if (prioridadeEscolhida > 10 || prioridadeEscolhida < 0){ // verifica se é um npumero plausível
        printf("Digite um numero valido.");
        return 1;
    }
    else{
        for(int i = 0; i < lt.qtd; i++){ // percorre a lista de tarefa e compara cada tarefa com a prioridade escolhida. Se forem compatíveis, aparece no terminal
            if (lt.tarefas[i].prioridade == prioridadeEscolhida){
                printf("\n");
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Status: %s\n", lt.tarefas[i].status);
                printf("\n");
            }
        }
    }
}

int Filtrar_Estado(ListaDeTarefas lt){ // seleciona as tarefas que possuem o estado escolhido pelo usuario

    int estadoEscolhido;
    printf("\nDigite o estado:\n1. nao iniciado\n2. em andamento\n3. completo\n>>> "); // pede o estado que se quer ver as tarefas
    scanf("%d", &estadoEscolhido);
    clearBuffer();

    if (estadoEscolhido > 3 || estadoEscolhido < 1){ // verifica se a informação dada é uma das oferecidas no menu
        printf("Digite um numero valido.");
        return 1;
    }
    else{
        for(int i = 0; i < lt.qtd; i++){ // percorre toda a lista e compara se a tarefa possui o estado desejado pelo usuario. Se tiver, printa no terminal
            if (estadoEscolhido == 1 && strcmp(lt.tarefas[i].status, "nao iniciado") == 0){
                printf("\n");
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                printf("\n");
            }
            else if (estadoEscolhido == 2 && strcmp(lt.tarefas[i].status, "em andamento") == 0){
                printf("\n");
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                printf("\n");
            }
            else if (estadoEscolhido == 3 && strcmp(lt.tarefas[i].status, "completo") == 0){
                printf("\n");
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                printf("\n");
            }
        }  
    } 
    return 0;  
}

int Filtrar_Categoria(ListaDeTarefas lt){
    
    char categoriaEscolhida[100];
    printf("\nDigite a categoria: ");
    scanf("%[^\n]", categoriaEscolhida);
    clearBuffer();

    int verificar = 0; // usado para ver se a categoria digitada existe
    Tarefa tr[100];
    int total = 0;

    for (int i = 0; i < lt.qtd; i++){ // percorre toda a lista de tarefas e verirfica as que possuem a categoria indicada
        if (strcmp(lt.tarefas[i].categoria, categoriaEscolhida) == 0){ 
            verificar = 1;
            tr[total] = lt.tarefas[i];
            total++;
        }
    }

    if(verificar != 1){
        printf("Digite uma categoria válida.\n");
        return 1;
    }

    for (int i = 0; i < total - 1; i++) { // faz a ordenação das tarefas em ordem descrescente
        for (int j = i + 1; j < total; j++) {
            if (tr[i].prioridade < tr[j].prioridade) {
                Tarefa temp = tr[i];
                tr[i] = tr[j];
                tr[j] = temp;
            }
        }
    }

    for(int i = 0; i < total; i++){
        printf("\nDescricao: %s" ,tr[i].descricao);
        printf("\nPrioridade: %d" ,tr[i].prioridade);
        printf("\nStatus: %s" ,tr[i].status);
        printf("\n");
    }

    return 0;  
}

int Filtrar_Prioridade_Categoria(ListaDeTarefas lt){ // junta as funções de filtrar por categoria e filtrar por prioridade

    char categoriaEscolhida[100];
    printf("\nDigite a categoria: "); // primeiro, pede a categoria
    scanf("%[^\n]", categoriaEscolhida);
    clearBuffer();

    int verificar = 0; // usado para ver se a categoria digitada existe
    Tarefa tr[100];
    int total = 0;

    for (int i = 0; i < lt.qtd; i++){ // percorre toda a lista de tarefas
        if (strcmp(lt.tarefas[i].categoria, categoriaEscolhida) == 0){ 
            verificar = 1;
            tr[total] = lt.tarefas[i]; // cria um lista com as tarefas da categoria escolhida (tr)
            total++;
        }
    }
    if(verificar != 1){
        printf("Digite uma categoria válida.\n");
        return 1;
    }

    int prioridadeEscolhida;
    printf("Digite o taxa de prioridade (0 a 10): "); // depois, filtra por prioridade 
    scanf("%d", &prioridadeEscolhida);
    clearBuffer();

    if (prioridadeEscolhida > 10 || prioridadeEscolhida < 0){ // verifica se a prioridade forncedia é válida
        printf("Digite um numero valido.");
        return 1;
    }

    else{
        for(int i = 0; i < total + 1; i++){ // dentro da nova lista de tarefas que passaram no filtro da categoria (tr), verifica qual possui a prioridade que o usuario deseja
            if (tr[i].prioridade == prioridadeEscolhida){
                printf("\n");
                printf("Descricao: %s\n", tr[i].descricao);
                printf("Status: %s\n", tr[i].status);
                printf("\n");
            }
        }
    }
    return 0;
}


int Exportar_Prioridade(ListaDeTarefas *lt){ // exporta as tarefas de uma determinada prioridade para um documento txt
    
    int prioridadeEscolhida; // idem a função de filtrar por prioridade
    printf("\nDigite o taxa de prioridade (0 a 10): ");
    scanf("%d", &prioridadeEscolhida);
    clearBuffer();

    if (prioridadeEscolhida > 10 || prioridadeEscolhida < 0){
        printf("Digite um numero valido.");
        return 1;
    }
    else{
        
        FILE *arq = fopen("Tarefas_Prioridade.txt", "w"); // ao inves de printar no terminal, escreve no arquivo Tarefas_Prioridade.txt

        for(int i = 0; i < lt->qtd; i++){// le as informações que estão em "lt" 
            if (lt->tarefas[i].prioridade == prioridadeEscolhida){
                fprintf(arq,"Prioridade: %d; " ,lt->tarefas[i].prioridade);
                fprintf(arq,"Categoria: %s; " ,lt->tarefas[i].categoria);
                fprintf(arq,"Status: %s; " ,lt->tarefas[i].status);
                fprintf(arq,"Descricao: %s\n" ,lt->tarefas[i].descricao);  
            }   
        }
   
        fclose(arq);
        return 0;
    }
    
}

int Exportar_Categoria(ListaDeTarefas *lt){

char categoriaEscolhida[100];
    printf("\nDigite a categoria: "); // pede a categoria desejada
    scanf("%[^\n]", categoriaEscolhida);
    clearBuffer();

    int verificar = 0; // usado para ver se a categoria digitada existe
    Tarefa tr[100];
    int total = 0;

    for (int i = 0; i < lt->qtd; i++){ // percorre toda a lista de tarefas
        if (strcmp(lt->tarefas[i].categoria, categoriaEscolhida) == 0){ 
            verificar = 1; // categoria válida
            tr[total] = lt->tarefas[i]; // adiciona a tarefa a uma nova lista (tr) com tamanho "total"
            total++;
        }
    }
    if(verificar != 1){ // caso a categoria não exista
        printf("Digite uma categoria válida.\n");
        return 1;
    }

    for (int i = 0; i < total - 1; i++) { // faz a ordenação em ordem descrescente de prioridade
        for (int j = i + 1; j < total; j++) {
            if (tr[i].prioridade < tr[j].prioridade) {
                Tarefa temp = tr[i];
                tr[i] = tr[j];
                tr[j] = temp;
            }
        }
    }

    FILE *arq = fopen("Tarefas_Categoria.txt", "w"); // ao inves de printar no terminal, escreve no arquivo Tarefas_Categoria.txt

        for(int i = 0; i < total; i++){// le as informações que estão em "tr" e escreve no arquivo txt
            fprintf(arq,"Prioridade: %d; " ,tr[i].prioridade);
            fprintf(arq,"Categoria: %s; " ,tr[i].categoria);
            fprintf(arq,"Status: %s; " ,tr[i].status);
            fprintf(arq,"Descricao: %s\n" ,tr[i].descricao);  
        }   
   
        fclose(arq);
        return 0;    
}

int Exportar_Prioridade_Categoria(ListaDeTarefas *lt){ // exporta as tarefas de uma determinada categoria e prioridade para um documento txt
    
    char categoriaEscolhida[100];
    printf("\nDigite a categoria: ");
    scanf("%[^\n]", categoriaEscolhida);
    clearBuffer();

    int verificar = 0; // usado para ver se a categoria digitada existe
    Tarefa tr[100];
    int total = 0;

    for (int i = 0; i < lt->qtd; i++){ // percorre toda a lista de tarefas
        if (strcmp(lt->tarefas[i].categoria, categoriaEscolhida) == 0){ 
            verificar = 1;
            tr[total] = lt->tarefas[i]; // cria um lista com as tarefas da categoria escolhida
            total++;
        }
    }
    if(verificar != 1){
        printf("Digite uma categoria válida.\n");
        return 1;
    }

    int prioridadeEscolhida;
    printf("Digite o taxa de prioridade (0 a 10): "); // solicita a prioridade
    scanf("%d", &prioridadeEscolhida);
    clearBuffer();

    if (prioridadeEscolhida > 10 || prioridadeEscolhida < 0){ // verifica se é uma prioridade válida
        printf("Digite um numero valido.");
        return 1;
    }

    else{
        FILE *arq = fopen("Tarefas_Prioridade_Categoria.txt", "w");

        for(int i = 0; i < total; i++){
            if (tr[i].prioridade == prioridadeEscolhida){ // confere, dentro da nova lista (tr), quais possuem a prioridade informada e escreve no documento
                fprintf(arq,"Prioridade: %d; " ,tr[i].prioridade);
                fprintf(arq,"Categoria: %s; " ,tr[i].categoria);
                fprintf(arq,"Status: %s; " ,tr[i].status);
                fprintf(arq,"Descricao: %s\n" ,tr[i].descricao);  
            }
        }
        fclose(arq);
    }

    return 0;
}


///////////// função base /////////////
void clearBuffer(){ //evita erros com a função scanf
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

///////////// funções relacionadas ao arquivo /////////////
int salvarLista(ListaDeTarefas *lt, char nome[]){ // "escreve" em um arquivo a lista de tarefas em binário para salvá-la
    FILE *f = fopen(nome, "wb");
    if(f == NULL){
        return 1;
    }else {
        fwrite(lt, sizeof(ListaDeTarefas), 1, f);
        fclose(f);
    }
    return 0;
}
int carregarLista(ListaDeTarefas *lt, char nome[]){ // "lê" as informações em binário para que sejam usadas no programa toda vez que for iniciado
    FILE *f = fopen(nome, "rb");
    if (f == NULL){
        return 1;
    }
    else{
        fread(lt, sizeof(ListaDeTarefas),1, f);
        fclose(f);
    }
    return 0;
}
