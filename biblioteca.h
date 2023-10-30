#ifndef UNTITLED3_BIBLIOTECA_H
#define UNTITLED3_BIBLIOTECA_H

typedef struct  { // struct que mostra onde vai ser salvo cada tipo de conteudo
    char descricao[300];
    char categoria[50];
    char status[15];
    int prioridade;
}Tarefa;

typedef struct{ // struct que armazenará cada tarefa
    Tarefa tarefas[100];
    int qtd;
}ListaDeTarefas;

// funções pricipais
void printMenu();
int criarTarefa(ListaDeTarefas *lt);
int DeletarTarefa(ListaDeTarefas *lt);
int ListarTarefa(ListaDeTarefas lt);
int EditarTarefa(ListaDeTarefas *lt);
int Filtrar_Prioridade(ListaDeTarefas lt);
int Filtrar_Estado(ListaDeTarefas lt);
int Filtrar_Categoria(ListaDeTarefas lt);
int Filtrar_Prioridade_Categoria(ListaDeTarefas lt);
int Exportar_Prioridade(ListaDeTarefas *lt);
int Exportar_Categoria(ListaDeTarefas *lt);
int Exportar_Prioridade_Categoria(ListaDeTarefas *lt);

// funções base
void clearBuffer();

// funções de arquivo
int salvarLista(ListaDeTarefas *lt, char nome[]);
int carregarLista(ListaDeTarefas *lt, char nome[]);

#endif 
