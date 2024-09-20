#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum status_tarefa {
    A_FAZER,
    ANDAMENTO,  
    FINALIZADA
} ETarefa;

typedef struct {
    int id;
    ETarefa status;
    char titulo[500];
} t_tarefa;


typedef struct NoTarefa {
    t_tarefa tarefa;
    struct NoTarefa *proximo;
    struct NoTarefa *anterior; 
} no_tarefa;

typedef struct {
    no_tarefa *primeiro;
    no_tarefa *ultimo;
    unsigned int size;
} t_lista;

no_tarefa *criar_tarefa(char *titulo_tarefa, int id_tarefa);
void menu_de_inicializacao(t_lista *lista, int *pt_id);
void tela_inicial(t_lista *lista, int *pt_id);
void gerenciar_tarefa(t_lista *lista, int *pt_id);
void creditos();
void inicializar(t_lista *lista);
void criar_nova_tarefa(t_lista *lista, int *pt_id);
void editar_tarefa(t_lista *lista);
void deletar_tarefa(t_lista *lista);
void listar_tarefas(t_lista *lista);
void salvar_tarefas_em_arquivo(t_lista *lista, const char *nome_arquivo);
void carregar_tarefas_de_arquivo(t_lista *lista, const char *nome_arquivo, int *pt_id);

int main() {
    int id = 0;
    int *pt_id = &id;

    t_lista lista;
    
    inicializar(&lista);
    tela_inicial(&lista, pt_id);

    return 0;
}

no_tarefa *criar_tarefa(char *titulo_tarefa, int id_tarefa) {
    no_tarefa *nova_tarefa = (no_tarefa *)malloc(sizeof(no_tarefa));
    
    if (nova_tarefa) {
        strcpy(nova_tarefa->tarefa.titulo, titulo_tarefa);
        nova_tarefa->tarefa.id = id_tarefa;
        nova_tarefa->tarefa.status = (ETarefa)0;
        nova_tarefa->proximo = NULL;
    }

    return nova_tarefa;
}

void menu_de_inicializacao(t_lista *lista, int *pt_id) {
    char op;

    system("clear");

    printf("1 - Carregar lista de tarefas\n2 - Novo projeto\n-> ");
    op = getchar();
    getchar();

    switch (op) {
        case '1':
            while (lista->primeiro != NULL) {
                free(lista->primeiro);
                lista->primeiro = NULL;
                lista->ultimo = NULL;
            }
            carregar_tarefas_de_arquivo(lista, "arquivo.txt", pt_id);
            gerenciar_tarefa(lista, pt_id);
            break;
        case '2':
            while (lista->primeiro != NULL) {
                free(lista->primeiro);
                lista->primeiro = NULL;
                lista->ultimo = NULL;
            }
            *pt_id = 0;
            inicializar(lista);
            gerenciar_tarefa(lista, pt_id);
            break;
        default:
            printf("\nEscolha uma opcao valida\n");
            getchar();
            break;
    }
}

void tela_inicial(t_lista *lista, int *pt_id){
    char ch;

    while(1) {
        system("clear");
        printf("1 - Gerenciar tarefas\n");
        printf("2 - Creditos\n");
        printf("Q - Sair\n-> ");
        ch = getchar();
        getchar(); 
        ch = toupper(ch);    

        if (ch == 'Q') {
            break;
        }

        switch(ch) {
            case '1':
                menu_de_inicializacao(lista, pt_id);
                break;
            case '2':
                creditos();
                break;
            default:
                printf("\nTecla invalida!\n");
                getchar();
                break;
        }
    }
}

void gerenciar_tarefa(t_lista *lista, int *pt_id) {
    system("clear");
    char op;
    while(1) {
        system("clear");
        printf("C - Criar nova tarefa\nE - Editar tarefa\nD - Deletar tarefa\nL - Listar tarefas\nS - Salvar tarefas\nV - Voltar a tela inicial\n");
        op = getchar();
        getchar();
        op = toupper(op);

        if (op == 'V') {
            break;
        }

        switch (op) {
            case 'C':
                criar_nova_tarefa(lista, pt_id);
                break;
            case 'E':
                system("clear");
                editar_tarefa(lista);
                break;
            case 'D':
                system("clear");
                deletar_tarefa(lista);
                break;
            case 'L':
                system("clear");
                listar_tarefas(lista);
                getchar();
                break;
            case 'S':
                remove("arquivo.txt");
                salvar_tarefas_em_arquivo(lista, "arquivo.txt");
                printf("\nTarefas salvas no arquivo!\n");
                getchar();
                break;
            default:
                printf("\nTecla inválida!\n");
                break;
        }
    }

    return;
}

void creditos() {
    system("clear");
    printf("Criador: Gabriel Queiroz Teles\n");
    printf("Obrigado por usar o sistema!\n\nAperte enter para voltar...\n");
    
    getchar();
}

void inicializar(t_lista *lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->size = 0;
}

void criar_nova_tarefa(t_lista *lista, int *pt_id) {
    system("clear");
    char titulo_tarefa[500];
    int id_tarefa;
    
    printf("Digite um nome para a nova tarefa: ");
    scanf(" %500[^\n]", titulo_tarefa);
    id_tarefa = *pt_id;
    *pt_id += 1;
  
    no_tarefa *tarefa = criar_tarefa(titulo_tarefa, id_tarefa);

    if (!tarefa) {
        fprintf(stderr, "Erro ao criar nova tarefa!\n");
        return;
    }

    if (!lista->primeiro) {
        lista->primeiro = tarefa;
        lista->ultimo = tarefa;
    }

    else {
        lista->ultimo->proximo = tarefa;
        tarefa->anterior = lista->ultimo;
        lista->ultimo = tarefa;

    }

    lista->size++;

    system("clear");
    printf("Tarefa (%s) criada!", titulo_tarefa);
    getchar();
    getchar();
}

void editar_tarefa(t_lista *lista) {
    int id_escolhido, opcao, novo_status;
    char novo_titulo[500];
    no_tarefa *aux = lista->primeiro;
    
    printf("As tarefas listadas atualmente sao:\n\n");
    listar_tarefas(lista);
    printf("\nEscolha o ID da tarefa que voce deseja editar: ");
    scanf("%d", &id_escolhido);

        aux = lista->primeiro;
        while (aux->tarefa.id != id_escolhido) {
            aux = aux->proximo;
        }
    
    system("clear");
    printf("O que você deseja alterar:\n1)Titulo\n2)Status\n-> ");
    scanf("%d", &opcao);
    system("clear");

    switch (opcao) {
        case 1:
            printf("Digite o novo titulo: ");
            scanf(" %500[^\n]", novo_titulo);
            strcpy(aux->tarefa.titulo, novo_titulo);
            printf("\nNovo nome inserido\n");
            getchar();
            getchar();
            break;
        
        case 2:
            printf("Qual eh o status atual:\n1) A Fazer\n2) Em Andamento\n3) Finalizada\n-> ");
            scanf("%d", &novo_status);
            aux->tarefa.status = (ETarefa)(novo_status - 1);
            printf("\nStatus atualizado\n");
            getchar();
            getchar();
            break;

        default:
            printf("Opcao invalida");
            getchar();
            break;
    }

}

void deletar_tarefa(t_lista *lista) {
    int id_escolhido;
    no_tarefa *aux;

    printf("As tarefas listadas atualmente sao:\n\n");
    listar_tarefas(lista);
    printf("\nEscolha o ID da tarefa que voce deseja deletar: ");
    do {
        scanf("%d", &id_escolhido);
    } while (id_escolhido > (int)lista->size - 1 && id_escolhido < 0);
    
    aux = lista->primeiro;
    while (aux->tarefa.id != id_escolhido) {
        aux = aux->proximo;
    }

    if (!aux) {
        fprintf(stderr, "ID invalido!\n");
        getchar();
        getchar();
        return;
    }

    if (!lista->primeiro->proximo) {
        free(lista->primeiro);
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }

    else if ((int)(lista->ultimo->tarefa.id) == id_escolhido) {
        aux = lista->primeiro;
        while (aux->proximo->proximo != NULL) {
            aux = aux->proximo;
        }
        free(aux->proximo);
        aux->proximo = NULL;
        lista->ultimo = aux;
    }

    else {
        while (aux->proximo->proximo != NULL) {
            aux->tarefa.id = aux->proximo->tarefa.id;
            aux->tarefa.status = aux->proximo->tarefa.status;
            strcpy(aux->tarefa.titulo, aux->proximo->tarefa.titulo);
            
            aux = aux->proximo;
        }

        aux->tarefa.id = aux->proximo->tarefa.id;
        aux->tarefa.status = aux->proximo->tarefa.status;
        strcpy(aux->tarefa.titulo, aux->proximo->tarefa.titulo);

        free(aux->proximo); 

        aux->proximo = NULL;
        lista->ultimo = aux;
    }
    
    lista->size--;

    printf("\n\nTarefa de id_escolhido %d deletada", id_escolhido);
    getchar();
    getchar();
}

void listar_tarefas(t_lista *lista) {
    no_tarefa *aux = lista->primeiro;
    char status_da_tarefa[20];
    
    while (aux != NULL) {
        switch (aux->tarefa.status) {
            case A_FAZER:
                strcpy(status_da_tarefa, "A Fazer");
                break;
            case ANDAMENTO:
                strcpy(status_da_tarefa, "Em Andamento");
                break;
            case FINALIZADA:
                strcpy(status_da_tarefa, "Finalizada");
                break;
            default:
                printf("\nERRO\n");
                break;
        }
        
        printf("ID: %d    TÍTULO: %s    STATUS: %s\n", aux->tarefa.id, aux->tarefa.titulo, status_da_tarefa);
        aux = aux->proximo;
    }
}

void salvar_tarefas_em_arquivo(t_lista *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    no_tarefa *aux = lista->primeiro;
    while (aux != NULL) {
        fwrite(&(aux->tarefa), sizeof(t_tarefa), 1, arquivo);
        aux = aux->proximo;
    }

    fclose(arquivo);
}

void carregar_tarefas_de_arquivo(t_lista *lista, const char *nome_arquivo, int *pt_id) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    t_tarefa tarefa;
    int max_id = -1;

    while (fread(&tarefa, sizeof(t_tarefa), 1, arquivo) == 1) {
        no_tarefa *nova_tarefa = (no_tarefa *)malloc(sizeof(no_tarefa));
        if (nova_tarefa != NULL) {
            nova_tarefa->tarefa = tarefa;
            nova_tarefa->proximo = NULL;
            nova_tarefa->anterior = lista->ultimo;
            if (lista->ultimo == NULL) {
                lista->primeiro = nova_tarefa;
                lista->ultimo = nova_tarefa;
            } else {
                lista->ultimo->proximo = nova_tarefa;
                lista->ultimo = nova_tarefa;
            }
            lista->size++;

            if (tarefa.id > max_id) {
                max_id = tarefa.id;
            }
        }
    }

    fclose(arquivo);

    *pt_id = max_id + 1;
}