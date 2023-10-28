#ifndef UNTITLED3_BIBLIOTECA_H
#define UNTITLED3_BIBLIOTECA_H

typedef struct  { // struct que mostra onde vai ser salvo cada tipo de conteudo
    char descricao[300];
    char categoria[100];
    char status[15];
    int prioridade;
}Tarefa;

typedef struct{ // struct que armazenará cada tarefa
    Tarefa tarefas[100];
    int qtd;
}ListaDeTarefas;

void printMenu();
int criarTarefa(ListaDeTarefas *lt);
int DeletarTarefa(ListaDeTarefas *lt);
int ListarTarefa(ListaDeTarefas lt);
int EditarTarefa(ListaDeTarefas *lt);


int salvarLista(ListaDeTarefas *lt, char nome[]);
int carregarLista(ListaDeTarefas *lt, char nome[]);

#endif 
