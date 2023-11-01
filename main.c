#include <stdio.h>
#include "biblioteca.h"

//Letizia Lowatzki Baptistella 24.123.031-7

int main() {

    ListaDeTarefas lt; // cria a lista de tarefas para usar durante o programa
    int cod;
    char arquivo[] = "salvo.txt";


    cod = carregarLista(&lt, arquivo);// carrega o arquivo de salvamento da lista ao iniciar o programa
    if(cod == 1){
        lt.qtd = 0;
    }

    int opcao;
    do{ // enquanto o usuário nao clicar para sair, pede a ação que o usuário quer realizar e "chama" a função correspondente
        printMenu();
        printf(">>> ");
        scanf("%d", &opcao);
        clearBuffer();

        if(opcao == 1){
            criarTarefa(&lt);
        }
        else if(opcao == 2){
            DeletarTarefa(&lt);
        }
        else if(opcao == 3){
            ListarTarefa(lt);
        }
        else if(opcao == 4){
            EditarTarefa(&lt);
        }
        else if(opcao == 5){
            Filtrar_Prioridade(lt);
        }
        else if(opcao == 6){
            Filtrar_Estado(lt);
        }
        else if(opcao == 7){
            Filtrar_Categoria(lt);
        }
        else if(opcao == 8){
            Filtrar_Prioridade_Categoria(lt);
        }
        else if(opcao == 9){
            Exportar_Prioridade(&lt);
        }
        else if(opcao == 10){
            Exportar_Categoria(&lt);
        }
        else if(opcao == 11){
            Exportar_Prioridade_Categoria(&lt);
        }
        else if(opcao == 0){
            break;
        }
        else{
            printf("Digite uma opcao valida!");
        }


    }while(opcao != 0);

    // salva todas as funções feitas dentro do arquivo ao sair do programa
    cod = salvarLista(&lt, "salvo.txt");
    if(cod != 0){
        printf("Erro ao salvar as tarefas");
    }
    return 0;
}
