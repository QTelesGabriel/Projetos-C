#include <stdio.h>
#include <stdlib.h>

#define NUMERO_DE_CONTATOS 500

// Dados que cada contato terá
typedef struct Contato {
    char nome[50];
    char email[50];
    char whatsapp[15];
    char instagram[30];
} t_contato;

// Criando array de contatos como variável global para ser mais fácil de mexer
t_contato contato[NUMERO_DE_CONTATOS];

// Definição das funções
void cadastrar(int *qtd);
void alterar_contato(int qtd);
void excluir_contato(int *qtd);
void listar_contatos(int qtd);
void localizar_por_nome(int qtd);
void menu_de_opcoes(int *qtd);
void armazenar_dados(int qtd);
void carregar_dados(int *qtd);

// Função para criar o menu de opções
void menu_de_opcoes(int *qtd) {
    int continuar = 1;
    while(continuar) {
        system("clear");
        int op;
        printf("Escolha uma tarefa:\n");
        printf("1) Cadastrar\n2) Alterar contato\n3) Excluir contato\n4) Listar contatos\n5) Localizar por nome\n6) Sair\n-> ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrar(qtd);
                break;
            case 2:
                alterar_contato(*qtd);
                break;
            case 3:
                excluir_contato(qtd);
                break;
            case 4:
                listar_contatos(*qtd);
                break;
            case 5:
                localizar_por_nome(*qtd);
                break;
            case 6:
                continuar = 0;
                break;
            default:
                printf("Escolha uma tarefa valida");
                getchar();
                getchar();
                break;
        }
    }

    // Salvar no final do programa;
    armazenar_dados(*qtd);
}

void cadastrar(int *qtd) {
    // Limpar o terminal
    system("clear");

    // Definir os dados do novo contato
    printf("Digite seu nome: ");
    scanf(" %50[^\n]", contato[*qtd].nome);
    printf("Digite seu email: ");
    scanf(" %50[^\n]", contato[*qtd].email);
    printf("Digite seu whatsapp: ");
    scanf(" %15[^\n]", contato[*qtd].whatsapp);
    printf("Digite seu instagram: ");
    scanf(" %30[^\n]", contato[*qtd].instagram);

    // Atualizar a quantidade de contatos
    (*qtd)++;
}

void listar_contatos(int qtd) {
    // Limpar terminal
    system("clear");

    // Listar todos elementos    
    for(int i = 0; i < qtd; i++) {
        printf("%d) Nome: %s    Email: %s   Whatsapp: %s    Instagram: %s   \n", i, contato[i].nome, contato[i].email, contato[i].whatsapp, contato[i].instagram);
    }
    printf("\nAperte enter para continuar...");

    getchar();
    getchar();

}

void armazenar_dados(int qtd) {
    // Abrir arquivo e conferir se ele já existe
    FILE *f = fopen("dados.txt", "w+");
    if(!f) {
        fprintf(stderr, "O arquivo nao existe!\n");
        exit(1);
    }

    // Apontar para o topo do arquivo
    rewind(f);

    // Salvar a quantidade de contatos
    fprintf(f, "%d\n", qtd);

    // Salvar os contatos
    for(int i = 0; i < qtd; i++) {
        fprintf(f, "%s\n", contato[i].nome);
        fprintf(f, "%s\n", contato[i].email);
        fprintf(f, "%s\n", contato[i].whatsapp);
        fprintf(f, "%s\n", contato[i].instagram);
    }

    // Fechar arquivo que foi aberto
    fclose(f);
}

void carregar_dados(int *qtd) {
    // Abrir arquivo
    FILE *f = fopen("dados.txt", "r");
    
    // Conferir se o arquivo existe. Caso não exista criá-lo e escrever nele o número 0 que representa a quantidade de elementos que ele possui
    if(!f) {
        f = fopen("dados.txt", "w+");
        rewind(f);
        fprintf(f, "0");
    }

    // Dar o valor de quantos contatos existem a variável qtd
    rewind(f);
    fscanf(f, "%d", qtd);

    // Loop para carregar os contatos
    for(int i = 0; i < *qtd; i++) {
        fscanf(f, " %50[^\n]", contato[i].nome);
        fscanf(f, " %50[^\n]", contato[i].email);
        fscanf(f, " %15[^\n]", contato[i].whatsapp);
        fscanf(f, " %30[^\n]", contato[i].instagram);
    }

    // Fechar arquivo que foi aberto
    fclose(f);
}

void alterar_contato(int qtd) {
    // Limpar terminal
    system("clear");

    // Listar os contatos para fácil vizualização
    listar_contatos(qtd);  

    // Escolher o incice do contato que será alterado
    printf("Escolha o indice do contato que deseja alterar: ");
    int indice;
    
    // Loop para garantir que o índice escolhido é um valor válido
    while(1) {
        scanf("%d", &indice);
        if (indice >= 0 && indice < qtd) {
            break;
        } else {
            printf("O indice escolhido eh invalido!\nEscolha outro: ");
            getchar();
        }
    }

    // Alterar contato
    printf("Digite outro nome: ");
    scanf(" %50[^\n]", contato[indice].nome);

    printf("Digite outro email: ");
    scanf(" %50[^\n]", contato[indice].email);
    
    printf("Digite outro whatsapp: ");
    scanf(" %15[^\n]", contato[indice].whatsapp);
    
    printf("Digite outro instagram: ");
    scanf(" %30[^\n]", contato[indice].instagram);
}

void excluir_contato(int *qtd) {
    // Limpar terminal
    system("clear");
    
    // Listar os contatos para fácil vizualização
    listar_contatos(*qtd);  

    // Escolher o índice do contato que será excluído
    printf("Escolha o indice do contato que deseja alterar: ");
    int indice;

    // Loop para garantir que o índice escolhido é um valor válido
    while(1) {
        scanf("%d", &indice);
        if (indice >= 0 && indice < *qtd) {
            break;
        }
        else {
            printf("O indice escolhido eh invalido!\nEscolha outro: ");
        }
    }

    // Sobreescrever os valores até o indice
    for(int i = indice + 1; i <= (*qtd) - 1; i++) {
        contato[i-1] = contato[i];
    }

    // Excluir o último contato (o que está repetido) ao diminuir o tamanho do array
    (*qtd)--;
}

void localizar_por_nome(int qtd) {
    // Nome que será procurado
    char nome_desejado[50];
    
    // Variável que vai pecorrer as letras dos nomes para comparar
    int j;

    // Variável que vai ser verdadeira quando o nome for diferente
    int nao_achou = 0;

    // Definir nome a ser encontrado
    printf("Digite o nome que deseja procurar: ");
    scanf(" %50[^\n]", nome_desejado);

    // Variável que vai guardar o índice do contato que possui o nome que será definido
    int indice;

    // Começar a comparação
    for(int i = 0; i < qtd; i++) {
        nao_achou = 0;
        j = 0;
        while(nome_desejado[j] != '\0' || contato[i].nome[j] != '\0') {
            if(nome_desejado[j] != contato[i].nome[j]) {
                nao_achou = 1;
                break;
            }
            j++;
        }
        if(nao_achou == 0) {
            indice = i;
            break;
        }
    }

    if (nao_achou == 1) {
        printf("\nNão foi possível encontrar o nome. Confira se está corretamente escrito...\n");
    }
    else {
        printf("\nO índice do nome desejado é: %d\n", indice);
    }
    getchar();
    getchar();
}

int main() {
    // Criando uma variável que vai guardar quantos contatos tem
    int qtd;    
    
    // Carregar os dados do arquivo
    carregar_dados(&qtd);

    // Menu de opções
    menu_de_opcoes(&qtd);

    return 0;
}