#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct Carta {      // Struct que indica características das cartas no baralho
    int num;
    int valor;
    char naipe;
    struct Carta *proximo;
} carta;

typedef struct Pilha_Baralho {      // Struct que indica o baralho completo em formato de Pilha
    carta *topo;
    int quantidade_de_cartas;
} baralho;

typedef struct Cartas_do_jogador {      // Struct que define a mão do jogador
    carta *topo;
} cartas_do_jogador;

typedef struct Jogador {        // Struct que define as características de cada jogador
    cartas_do_jogador mao;
    int jogando;
    int quantidade_de_cartas;
    int indice_do_jogador;
    double dinheiro;
    double aposta;
    struct Jogador *proximo;
    int blackjack;
    int ja_fez_split;
    int split;
} jogador;

typedef struct Jogadores {      // Struct que define uma lista circular para os jogadores
    jogador *inicio;
} jogadores;

void menu_inicial();
void regras();
void print_logo();
void jogar();
void comecar_jogo(jogadores *jogadores, int *quantos_jogadores, baralho *baralho, int *indice);
void apostas(jogadores *jogadores);
void double_down(jogador *jogador, baralho *baralho, int *opcao_do_jogador);
void split(jogador *jogador_da_vez, baralho *baralho, int *quantos_jogadores, int indice);
void distribuicao_inicial_de_cartas(jogadores *jogadores, baralho *baralho, int quantos_jogadores);
void fez_blackjack(jogador *jogador);
jogador *criar_jogador(int indice);
carta *criar_carta(int num, char naipe);
void inicializar_baralho(baralho *baralho);
void inicializar_lista_de_jogadores(jogadores *jogadores);
void inicializar_mao_jogador(jogador *jogador);
void inserir_jogador(jogadores *jogadores, int indice);
void inserir_cartas_no_baralho(baralho *baralho, int num, char naipe);
void criar_baralho_completo(baralho *baralho);
int nao_existem_quatro_cartas_iguais(baralho *baralho, int num);
int nao_existe_carta_igual(baralho *baralho, int num, char naipe);
void comprar_cartas(jogador *jogador, baralho *baralho);
carta *pop(baralho *baralho);
void mostrar_cartas_do_jogador(jogador *jogador_da_vez);
void mostrar_mesa(jogadores *jogadores, int quantos_jogadores);
void mostrar_carta_comprada(jogador *jogador);
int dealer_vai_comprar(jogadores  *jogadores);
void quanto_vale_o_as(jogador *jogador);
void reajustar_valor_do_as(jogador *jogador);
int somatorio_das_cartas(jogador *jogador);
void conferir_situacao_jogador(jogador *jogador);
void conferir_final_da_partida(jogadores *jogadores, int *continuar_mesa);

void menu_inicial() {    
    int op;
    int loop = 1;

    while(loop) {
        system("clear");
        print_logo();
        printf("\n\n1) Jogar\n2) Regras\n3) Sair\n\n-> ");
        
        scanf("%d", &op);

        switch(op) {
            case 1:
                jogar();
                break;

            case 2:
                regras();
                break;

            case 3:
                loop = 0;
                break;
            
            default:
                printf("\nOpção inválida!\nEscolha outra...\n");
                getchar();
                break;
        }
    }
}

void regras() {

    system("clear");

    printf("Objetivo: Obter uma mão com um valor mais próximo de 21 do que a mão do dealer, sem exceder 21.\n\n");
    printf("Valores das cartas:\n\n");
    printf("    - As cartas numéricas de 2 a 10 têm seu valor normal\n");
    printf("    - As cartas de valete, dama e rei valem 10 pontos cada.\n");
    printf("    - O ás pode valer 1 ponto ou 11 pontos, dependendo da melhor estratégia para a mão.\n\n");
    printf("Desenvolvimento do Jogo:\n\n");
    printf("Aposta: Os jogadores fazem suas apostas antes das cartas serem distribuídas.\n\n");
    printf("Distribuição de cartas: O dealer distribui duas cartas para cada jogador, incluindo para si mesmo. As cartas do jogador são distribuídas viradas para cima, enquanto o dealer recebe uma carta virada para cima e outra virada para baixo (carta 'buraco').\n\n");
    printf("Jogada do Jogador: Os jogadores têm várias opções:\n");
    printf("    - Pedir (Hit): Receber uma carta adicional para tentar chegar mais perto de 21.\n");
    printf("    - Ficar (Stand): Não pedir mais cartas e manter o valor atual da mão.\n");
    printf("    - Dobrar (Double Down): Dobrar a aposta inicial e receber exatamente mais uma carta.\n");
    printf("    - Dividir (Split): Se as duas primeiras cartas tiverem o mesmo valor, o jogador pode dividir em duas mãos separadas.\n\n");
    printf("Jogada do Dealer: Depois que os jogadores finalizam suas jogadas, o dealer revela a carta virada para baixo e deve pedir cartas até atingir um total de 17 ou mais.\n\n");
    printf("Comparação das Mãos: As mãos do jogador são comparadas com a do dealer para determinar o vencedor. Se o jogador tiver mais perto de 21 do que o dealer, sem exceder, ou se o dealer ultrapassar 21, o jogador vence.\n\n");
    printf("Pagamento das Apostas: Os ganhos são pagos de acordo com as seguintes regras:\n");
    printf("    - 1:1 para vitória padrão\n");
    printf("    - 3:2 para um blackjack (um ás e uma carta de valor 10).\n\n");
    printf("Blackjack (Natural): Um blackjack ocorre quando um jogador ou o dealer recebe um ás e uma carta de valor 10 como as duas primeiras cartas, resultando em um pagamento melhor (3:2).\n\n");
    printf("Neste jogo todos jogadores começam com R$1.000.000,00.\n\nAlém disso, em todo final de rodada há a opção de alguém sair do jogo ou de adicionar novos jogadores.\n");

    getchar();
    getchar();
}

void print_logo() {     // Função para imprimir o nome do jogo
    printf("888      888                   888       d8b                   888      \n");
    printf("888      888                   888       Y8P                   888      \n");
    printf("888      888                   888                             888      \n");
    printf("88888b.  888  8888b.   .d8888b 888  888 8888  8888b.   .d8888b 888  888 \n");
    printf("888 '88b 888     '88b d88P'    888 .88P '888     '88b d88P'    888 .88P \n");
    printf("888  888 888 .d888888 888      888888K   888 .d888888 888      888888K  \n");
    printf("888 d88P 888 888  888 Y88b.    888 '88b  888 888  888 Y88b.    888 '88b \n");
    printf("88888P'  888 'Y888888  'Y8888P 888  888  888 'Y888888  'Y8888P 888  888 \n");
    printf("                                         888                            \n");
    printf("                                        d88P                            \n");
    printf("                                      888P'                             \n");
}

void jogar() {      // Função ara começar o jogo
    system("clear");
    printf("Quantos jogadores serão?\n-> ");

    int indice = 0;
    int quantos_jogadores;
    scanf("%d", &quantos_jogadores);
    quantos_jogadores++;

    // Criar e inicializar lista de jogadores
    jogadores jogadores;
    inicializar_lista_de_jogadores(&jogadores);

    // Inicializar e criar um baralho completo de 52 cartas embaralho
    baralho baralho;
    inicializar_baralho(&baralho);

    // Inserir os jogadores na lista de jogadores
    for(int i = 0; i < quantos_jogadores; i++) {
        inserir_jogador(&jogadores, indice);
        indice++;
    }

    printf("\nJogo pronto para começar!\nAperte enter...");
    getchar();
    getchar();

    // Começar o jogo
    comecar_jogo(&jogadores, &quantos_jogadores, &baralho, &indice);
}

void comecar_jogo(jogadores *jogadores, int *quantos_jogadores, baralho *baralho, int *indice) {  // Função em que o código do jogo funciona
    int continuar_jogo = 1;     // Para saber se a rodada vai acabar
    int continuar_mesa = 1;     // Para saber se a mesa vai acabar
    int opcao_do_jogador;       // Escolher comprar o parar

    while(continuar_mesa) {
        // O jogo reiniciará
        continuar_jogo = 1;
        // Criar novo baralho embaralhado de 52 cartas
        criar_baralho_completo(baralho);
        // Esvaziar mão dos jogadores
        jogador *aux = jogadores->inicio;
        do {
            aux->quantidade_de_cartas = 0;
            aux->ja_fez_split = 0;           
            while(aux->mao.topo != NULL) {
                carta *temp = aux->mao.topo;
                aux->mao.topo = aux->mao.topo->proximo;
                free(temp); 
            }
            aux->blackjack = 0;
            aux->jogando = 1;
            aux = aux->proximo;
        } while(aux != jogadores->inicio);

        // Começar a rodada a partir do jogador 1 e não do dealer(jogador 0)
        jogador *jogador_da_vez = jogadores->inicio->proximo;
        apostas(jogadores);

        // Distribuição inicial de 2 cartas para cada jogador
        distribuicao_inicial_de_cartas(jogadores, baralho, *quantos_jogadores);

        while(continuar_jogo) {

            int valido = 1;     // Opção do jogador é valida

            // Conferir se o jogador não ganhou um black jack na distribuição e se ganhou, ganha automaticamente a rodada
            jogador_da_vez->quantidade_de_cartas++;
            mostrar_mesa(jogadores, *quantos_jogadores);
            fez_blackjack(jogador_da_vez);
            jogador_da_vez->quantidade_de_cartas--;

            // Conferir se o jogador está jogando na rodada
            if(jogador_da_vez->jogando) {

                // Se for o dealer
                if(jogador_da_vez->indice_do_jogador == 0) {
                    
                    // Enquanto o dealer tiver que comprar
                    do {
                        jogador_da_vez->quantidade_de_cartas += 1;
                        if(dealer_vai_comprar(jogadores)) {
                            mostrar_mesa(jogadores, *quantos_jogadores);
                            printf("\n\nVez do Dealer jogar\n");
                            comprar_cartas(jogador_da_vez, baralho);
                            jogador_da_vez->quantidade_de_cartas++;
                            mostrar_carta_comprada(jogador_da_vez);
                            quanto_vale_o_as(jogador_da_vez);
                            reajustar_valor_do_as(jogador_da_vez);
                        }
                        else {
                            mostrar_mesa(jogadores, *quantos_jogadores);
                            printf("\n\nVez do Dealer jogar\n");
                            jogador_da_vez->jogando = 0;
                            getchar();
                        }
                        jogador_da_vez->quantidade_de_cartas-=1;
                    } while(dealer_vai_comprar(jogadores));
                }

                // Se for qualquer outro jogador
                else {
                    // Enquanto o jogador não quiser parar
                    do {
                        // Enquanto a opção escolhida pelo jogador não for válida
                        do {
                            mostrar_mesa(jogadores, *quantos_jogadores);

                            printf("\n\nVez do jogador %d%s\nDeseja...\n1) Comprar carta\n2) Parar\n%s%s-> ", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""), (jogador_da_vez->quantidade_de_cartas == 2 ? "3) Double Down\n" : ""), ((jogador_da_vez->quantidade_de_cartas == 2 && jogador_da_vez->mao.topo->num == jogador_da_vez->mao.topo->proximo->num && jogador_da_vez->ja_fez_split == 0) ? "4) Split\n" : ""));
                            scanf("%d", &opcao_do_jogador);
                            getchar();

                            if(opcao_do_jogador == 1) {
                                valido = 1;
                                jogador_da_vez->quantidade_de_cartas += 1;
                                comprar_cartas(jogador_da_vez, baralho);
                                mostrar_carta_comprada(jogador_da_vez);
                                quanto_vale_o_as(jogador_da_vez);
                                reajustar_valor_do_as(jogador_da_vez);
                                if(somatorio_das_cartas(jogador_da_vez) >= 21) {
                                    opcao_do_jogador = 2;
                                }
                            }
                            else if(opcao_do_jogador == 2) {
                                valido = 1;
                                jogador_da_vez->jogando = 0;
                                printf("\nO jogador %d%s escolheu parar de comprar cartas\n", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""));
                                getchar();
                            }
                            else if(opcao_do_jogador == 3 && jogador_da_vez->quantidade_de_cartas == 2) {
                                valido = 1;
                                double_down(jogador_da_vez, baralho, &opcao_do_jogador);
                            }
                            else if(opcao_do_jogador == 4 && jogador_da_vez->mao.topo->num == jogador_da_vez->mao.topo->proximo->num && jogador_da_vez->quantidade_de_cartas == 2 && jogador_da_vez->ja_fez_split == 0) {
                                valido = 1;
                                split(jogador_da_vez, baralho, quantos_jogadores, *indice);
                            }
                            else {
                                valido = 0;
                            }
                        } while(!valido);
                    } while(opcao_do_jogador != 2);
                }

                // Conferir se o jogador fez blackjack ou se estourou
                conferir_situacao_jogador(jogador_da_vez);
            }
            if(jogador_da_vez == jogadores->inicio) {
                continuar_jogo = 0;
            }
            
            jogador_da_vez = jogador_da_vez->proximo;
        } 

        // Se todo mundo parou final da partida
        conferir_final_da_partida(jogadores, &continuar_mesa);
        continuar_jogo = 0;

        if(continuar_mesa == 1) {
            // Limpar tela e perguntar se alguém deseja sair da mesa
            system("clear");
            
            // Verificar se alguém deseja sair da mesa
            jogador *temp = jogadores->inicio->proximo;
            while(temp != jogadores->inicio) {
                int op;
                printf("O jogador %d%s deseja sair da mesa?\n1) Sim\n2) Não\n-> ", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                do {
                    scanf("%d", &op);
                } while(op != 1 && op != 2);
                if(op == 1) {

                    printf("\nOBRIGADO POR JOGAR JOGADOR %d%s!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("===========================================\n");

                    // Jogador saiu da mesa
                    jogador *aux = temp;
                    while(temp->proximo != aux) {
                        temp = temp->proximo;
                    }
                    if(temp->proximo->split == 0 && temp->proximo->proximo->split == 0) {
                        aux = temp->proximo;
                        temp->proximo = temp->proximo->proximo;
                        free(aux);

                        // Atualizar quantidade de jogadores
                        (*quantos_jogadores)--;
                    }
                    else if(temp->proximo->split == 0 && temp->proximo->proximo->split == 1) {
                        do {
                            aux = temp->proximo;
                            temp->proximo = temp->proximo->proximo;
                            free(aux);

                            // Atualizar quantidade de jogadores
                            (*quantos_jogadores)--;
                        } while(temp->proximo->split == 1);
                    }
                    else if(temp->proximo->split == 1) {
                        aux = temp->proximo;
                        temp->proximo = temp->proximo->proximo;
                        free(aux);

                        // Atualizar quantidade de jogadores
                        (*quantos_jogadores)--;
                    }
                }
                putchar('\n');
                
                temp = temp->proximo;
            }

            int op;
            printf("\nDeseja adicionar alguém na mesa?\n1) Sim\n2) Não\n-> ");
            do {
                scanf("%d", &op);
            } while(op != 1 && op != 2);
            if(op == 1) {
                int quantidade;
                printf("Quantas pessoas?\n-> ");
                scanf("%d", &quantidade);
                
                // Inserir novos jogadores na lista de jogadores
                for(int i = 0; i < quantidade; i++) {
                    inserir_jogador(jogadores, *indice);

                    // Atualizar quantidade de jogadores
                    (*quantos_jogadores)++;
                    (*indice)++;
                }
            }

            // Conferir se ainda há alguém na mesa
            if(*quantos_jogadores == 1) {
                continuar_mesa = 0;
            }
        }

        getchar();
    }
}

void apostas(jogadores *jogadores) {
    jogador *jogador_da_vez = jogadores->inicio->proximo;

    // Limpar tela
    system("clear");
    printf("Apostas para a rodada:\n\n");
    
    // Passar por todos jogadores
    while(jogador_da_vez != jogadores->inicio) {

        // Caso só tenha uma mão
        if(jogador_da_vez->split == 0 && jogador_da_vez->proximo->split == 0) {
            printf("Jogador %d: R$", jogador_da_vez->indice_do_jogador);
            scanf("%lf", &jogador_da_vez->aposta);
            jogador_da_vez->dinheiro -= jogador_da_vez->aposta;
            jogador_da_vez = jogador_da_vez->proximo;
        }

        // Tratar as mãos separadas de um jogador
        else if(jogador_da_vez->proximo->split == 1 && jogador_da_vez->split == 0) {
            int contador = 0;
            jogador *aux = jogador_da_vez;
            do {
                printf("Jogador %d%s: R$", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                scanf("%lf", &aux->aposta);
                jogador_da_vez->dinheiro -= aux->aposta;

                aux = aux->proximo;
                contador++;
            } while(aux->split != 0);

            for(int i = 0; i < contador; i++) {
                jogador_da_vez->proximo->dinheiro = jogador_da_vez->dinheiro;
                jogador_da_vez = jogador_da_vez->proximo;
            }
        }
    }
    getchar();
}

void double_down(jogador *jogador, baralho *baralho, int *opcao_do_jogador) {
    
    // Dobrar a aposta
    printf("O jogador %d escolheu fazer o double down\n\n", jogador->indice_do_jogador);
    jogador->dinheiro -= jogador->aposta;
    jogador->aposta += jogador->aposta;
    printf("Nova aposta: R$%.2lf\n", jogador->aposta);

    // Compra da terceira carta
    comprar_cartas(jogador, baralho);
    mostrar_carta_comprada(jogador);
    quanto_vale_o_as(jogador);
    reajustar_valor_do_as(jogador);

    // Acabou a vez do jogador
    jogador->jogando = 0;
    *opcao_do_jogador = 2;

}

void split(jogador *jogador_da_vez, baralho *baralho, int *quantos_jogadores, int indice) {
    
    // Criar a outra mão
    printf("\nO jogador %d%s escolheu fazer o split\n\n", jogador_da_vez->indice_do_jogador, (jogador_da_vez->split == 1 ? ".2" : ""));
    
    jogador *nova_mao = criar_jogador(indice);
    
    // Corrigir dados
    nova_mao->split = 1;
    nova_mao->ja_fez_split = 1;
    jogador_da_vez->ja_fez_split = 1;
    nova_mao->dinheiro = jogador_da_vez->dinheiro;
    nova_mao->indice_do_jogador = jogador_da_vez->indice_do_jogador;
    nova_mao->aposta = jogador_da_vez->aposta;
    jogador_da_vez->dinheiro -= jogador_da_vez->aposta;
    
    nova_mao->proximo = jogador_da_vez->proximo;
    jogador_da_vez->proximo = nova_mao;

    // Passar uma das cartas para a outra mão
    nova_mao->mao.topo = jogador_da_vez->mao.topo;
    jogador_da_vez->mao.topo = jogador_da_vez->mao.topo->proximo;
    nova_mao->mao.topo->proximo = NULL;

    if(nova_mao->mao.topo->num == 1) {
        printf("O valor do Ás voltou a ser 11\n\n");
        nova_mao->mao.topo->valor = 11;
        jogador_da_vez->mao.topo->valor = 11;
    }

    // Corrigir quantidade de jogadores
    (*quantos_jogadores)++;

    // Comprar uma nova carta para cada mão e mostrar
    comprar_cartas(jogador_da_vez, baralho);
    mostrar_carta_comprada(jogador_da_vez);
    quanto_vale_o_as(jogador_da_vez);
    reajustar_valor_do_as(jogador_da_vez);

    comprar_cartas(nova_mao, baralho);
    mostrar_carta_comprada(nova_mao);
    quanto_vale_o_as(nova_mao);
    reajustar_valor_do_as(nova_mao);
    nova_mao->quantidade_de_cartas = 2;

}

void distribuicao_inicial_de_cartas(jogadores *jogadores, baralho *baralho, int quantos_jogadores) {
    jogador *aux = jogadores->inicio->proximo;
    
    for(int i = 0; i < quantos_jogadores * 2; i++) {
        
        system("clear");
        aux->quantidade_de_cartas += 1;
        comprar_cartas(aux, baralho);
        mostrar_carta_comprada(aux);
        quanto_vale_o_as(aux);

        aux = aux->proximo;
    }

}

void fez_blackjack(jogador *jogador) {
    if(jogador->mao.topo->valor + jogador->mao.topo->proximo->valor == 21) {
        if(jogador->indice_do_jogador != 0 && jogador->blackjack == 0) {
            printf("\nO jogador %d%s fez BlackJack!\n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
        }
        else if(jogador->indice_do_jogador == 0 && jogador->blackjack == 0) {
            printf("\nO dealer fez BlackJack!\n");
        }
        jogador->blackjack = 1;
        jogador->jogando = 0;
        getchar();
    }
}

jogador *criar_jogador(int indice) {        // Função para criar um novo jogador
    jogador *novo_jogador = (jogador *)malloc(sizeof(jogador));
    if(!novo_jogador) {
        fprintf(stderr, "Falha ao criar novo jogador!\n");
        return NULL;
    } 
    
    inicializar_mao_jogador(novo_jogador);  

    novo_jogador->ja_fez_split = 0;
    novo_jogador->split = 0;
    novo_jogador->quantidade_de_cartas = 0;
    novo_jogador->jogando = 1;
    novo_jogador->proximo = NULL;
    novo_jogador->blackjack = 0;
    novo_jogador->indice_do_jogador = indice;
    if(novo_jogador->indice_do_jogador == 0) {
        novo_jogador->dinheiro = 20000000;
    }
    else {
        novo_jogador->dinheiro = 1000000;
    }
    novo_jogador->aposta = 0;

    return novo_jogador;
}

carta *criar_carta(int num, char naipe) {
    carta *nova_carta = (carta *)malloc(sizeof(carta));
    if(!nova_carta) {
        fprintf(stderr, "Falha ao criar nova carta!");
        return NULL;
    }
    nova_carta->num = num;
    if(num != 11 && num != 12 && num != 13 && num != 1) {
        nova_carta->valor = num;
    } else if(num == 1) {
        nova_carta->valor = 11;
    } else {
        nova_carta->valor = 10;
    }
    nova_carta->naipe = naipe;
    nova_carta->proximo = NULL;

    return nova_carta;
}

void inicializar_baralho(baralho *baralho) {
    baralho->topo = NULL;
    baralho->quantidade_de_cartas = 0;
}

void inicializar_lista_de_jogadores(jogadores *jogadores) {     // Função para inicializar a lista de jogadores
    jogadores->inicio = NULL;
}

void inicializar_mao_jogador(jogador *jogador) {
    jogador->mao.topo = NULL;
}

void inserir_jogador(jogadores *jogadores, int indice) {        // Função para inserir um novo jogador na lista
    jogador *novo_jogador = criar_jogador(indice);

    if(jogadores->inicio == NULL) {
        jogadores->inicio = novo_jogador;
        novo_jogador->proximo = jogadores->inicio;
        return;
    }

    jogador *aux = jogadores->inicio;
    
    while (aux->proximo != jogadores->inicio) {
        aux = aux->proximo;
    }
    aux->proximo = novo_jogador;
    novo_jogador->proximo = jogadores->inicio;
}

void inserir_cartas_no_baralho(baralho *baralho, int num, char naipe) {
    carta *nova_carta;
    nova_carta = criar_carta(num, naipe);
    
    if(!nova_carta) {
        fprintf(stderr, "Falha ao criar carta!\n");
        exit(1);
    }

    if(baralho->topo == NULL) {
        baralho->topo = nova_carta;
        return;
    }

    nova_carta->proximo = baralho->topo;
    baralho->topo = nova_carta;
}

void criar_baralho_completo(baralho *baralho) {     // Função para criar um baralho completo e ebaralhado
    srand(time(NULL));
    int num;    // Numero da carta
    char naipe[4] = {'C', 'P', 'E', 'O'};   // Naipes
    char naipe_escolhido;   // Naipe da carta

    // Zerar o baralho
    while(baralho->topo != NULL) {
        pop(baralho);
        inicializar_baralho(baralho);
    }

    // Criar uma carta aleatória
    for (int i = baralho->quantidade_de_cartas; i < 52; i++) {
        
        // Escolher um número que já não tenha em 4 cartas
        while(1) {
            num = (rand() % 13) + 1;
            if(nao_existem_quatro_cartas_iguais(baralho, num)) {
                break;
            }
        }

        // Escolher uma carta que de fato não existe ainda
        while(1) {
            naipe_escolhido = naipe[rand() % 4];
            if(nao_existe_carta_igual(baralho, num, naipe_escolhido)) {
                break;
            }
        }

        // Inserir a carta criada no baralho
        inserir_cartas_no_baralho(baralho, num, naipe_escolhido);
        
        // Atualizar o tamhanho do baralho
        baralho->quantidade_de_cartas += 1;
    }
}

int nao_existem_quatro_cartas_iguais(baralho *baralho, int num) {
    if(!baralho->topo) {
        return 1;
    }
    else {
        int contador = 0;
        carta *aux = baralho->topo;
        
        while(aux->proximo != NULL) {
            if(aux->num == num) {
                contador++;
            }
            if(contador >= 4) {
                return 0;
            }
            aux = aux->proximo;
        }
        if(aux->num == num) {
            contador++;
        }
        if(contador >= 4) {
            return 0;
        }
        return 1;
    }
}

int nao_existe_carta_igual(baralho *baralho, int num, char naipe) {
    if(!baralho->topo) {
        return 1;
    }
    else {
        carta *aux = baralho->topo;
        while(aux->proximo != NULL) {
            if(aux->num == num) {
                if(aux->naipe == naipe) {
                    return 0;
                }
            }
            aux = aux->proximo;
        }
        if(aux->num != num) {
            return 1;
        }
        else {
            if(aux->naipe == naipe) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
}

void comprar_cartas(jogador *jogador, baralho *baralho) {
    if(!jogador) {
        fprintf(stderr, "Jogador inválido!\n");
        exit(1);
    }
    
    if(!baralho->topo) {
        criar_baralho_completo(baralho);
    }

    carta *carta_a_ser_comprada = pop(baralho);

    if(!jogador->mao.topo) {
        jogador->mao.topo = carta_a_ser_comprada;
        baralho->quantidade_de_cartas -= 1;
        return;
    }

    carta_a_ser_comprada->proximo = jogador->mao.topo;
    jogador->mao.topo = carta_a_ser_comprada;   
}

carta *pop(baralho *baralho) {
    if(!baralho->topo) {
        fprintf(stderr, "Acabaram as cartas!\n");
        exit(1);
    }

    carta *carta_a_ser_passada = (carta *)malloc(sizeof(carta));
    carta_a_ser_passada->num = baralho->topo->num;
    carta_a_ser_passada->valor = baralho->topo->valor;
    carta_a_ser_passada->naipe = baralho->topo->naipe;
    carta_a_ser_passada->proximo = NULL;

    carta *temp = baralho->topo;
    baralho->topo = baralho->topo->proximo;
    free(temp);

    baralho->quantidade_de_cartas -= 1;

    return carta_a_ser_passada;
}

void mostrar_cartas_do_jogador(jogador *jogador) {       // Função para mostrar as cartas de cada jogador
    char num[3];
    char naipe[4];

    carta *aux = jogador->mao.topo;

    while (aux != NULL) {
        if(aux->naipe == 'P') {
            sprintf(naipe, "♣");
        }
        else if(aux->naipe == 'E') {
            sprintf(naipe, "♠");
        }
        else if(aux->naipe == 'O') {
            sprintf(naipe, "♦");
        }
        else if(aux->naipe == 'C') {
            sprintf(naipe, "♥");
        }

        if(aux->num > 1 && aux->num < 11) {
            sprintf(num, "%d", aux->num);
        }
        else if(aux->num == 1) {
            sprintf(num, "A");
        }
        else if(aux->num == 11) {
            sprintf(num, "J");
        }
        else if(aux->num == 12) {
            sprintf(num, "Q");
        }
        else if(aux->num == 13) {
            sprintf(num, "K");
        }

        if(jogador->indice_do_jogador == 0 && jogador->mao.topo == aux && jogador->quantidade_de_cartas == 2) {
            
            printf(" ______   \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n");
            printf("|_|__|_|  \n\n");
        }
        else {
            printf(" ______   \n");
            printf("|%s    %s|  \n", num, (aux->num == 10 ? "" : " "));
            printf("|%s     |  \n", naipe);
            printf("|      |  \n");
            printf("|______|  \n\n");
        }
        aux = aux->proximo;
    }    

    printf("//=================\\\\\n");
    
}

void mostrar_mesa(jogadores *jogadores, int quantos_jogadores) {
    system("clear");

    jogador *aux = jogadores->inicio;
    printf("\n        Dealer\n\n");
    printf("\\\\=================//\n");
    mostrar_cartas_do_jogador(aux);
    printf("\n");
    aux = aux->proximo;

    for(int indice = 1; indice < quantos_jogadores; indice++) {
        printf("\n      Jogador%d%s\n\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
        printf("\\\\=================//\n");
        mostrar_cartas_do_jogador(aux);
        printf("\n");

        aux = aux->proximo;
    }
}

void mostrar_carta_comprada(jogador *jogador) {
    char num[3];
    char naipe[4];

    if(jogador->mao.topo->naipe == 'P') {
        sprintf(naipe, "♣");
    }
    else if(jogador->mao.topo->naipe == 'E') {
        sprintf(naipe, "♠");
    }
    else if(jogador->mao.topo->naipe == 'O') {
        sprintf(naipe, "♦");
    }
    else if(jogador->mao.topo->naipe == 'C') {
        sprintf(naipe, "♥");
    }

    if(jogador->mao.topo->num > 1 && jogador->mao.topo->num < 11) {
        sprintf(num, "%d", jogador->mao.topo->num);
    }
    else if(jogador->mao.topo->num == 1) {
        sprintf(num, "A");
    }
    else if(jogador->mao.topo->num == 11) {
        sprintf(num, "J");
    }
    else if(jogador->mao.topo->num == 12) {
        sprintf(num, "Q");
    }
    else if(jogador->mao.topo->num == 13) {
        sprintf(num, "K");
    }

    if(jogador->indice_do_jogador == 0) {
        printf("Carta para o dealer:\n");
    }
    else {
        printf("Carta para o jogador %d%s: \n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
    }

    if(jogador->indice_do_jogador == 0 && jogador->quantidade_de_cartas == 2) {
        printf(" ______   \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n");
        printf("|_|__|_|  \n\n");
    }
    else {
        printf(" ______   \n");
        printf("|%s    %s|  \n", num, (jogador->mao.topo->num == 10 ? "" : " "));
        printf("|%s     |  \n", naipe);
        printf("|      |  \n");
        printf("|______|  \n\n");
    }

    getchar();
}
  
int dealer_vai_comprar(jogadores  *jogadores) {
    int soma_das_cartas = somatorio_das_cartas(jogadores->inicio);

    // Regra do 17
    // 1) O dealer deve comprar até bater 16
    // 2) O dealer deve parar de comprar se tiver 17 ou mais
    if(soma_das_cartas >= 17) {
        return 0;
    }

    return 1;
}

void quanto_vale_o_as(jogador *jogador) {
    int soma_das_cartas = somatorio_das_cartas(jogador);

    if(jogador->mao.topo->num == 1) {
        if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
            if(soma_das_cartas > 21) {
                jogador->mao.topo->valor = 1;
                if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
                    printf("\nO Ás está valendo 1...\n");
                    getchar();
                }
            }
            else {
                jogador->mao.topo->valor = 11;
                if(jogador->indice_do_jogador != 0 || jogador->quantidade_de_cartas != 2) {
                    printf("O Ás está valendo 11...\n");
                    getchar();
                }
            }
        }
        else {
            if(jogador->quantidade_de_cartas != 2) {
                printf("O Ás está valendo 11...\n");
            }
            jogador->mao.topo->valor = 11;
        }
    }    
}

void reajustar_valor_do_as(jogador *jogador) {
    carta *aux = jogador->mao.topo;
    while(aux != NULL) {
        if(somatorio_das_cartas(jogador) > 21) {
            if(aux->valor == 11) {
                aux->valor = 1;
                printf("\nO valor do Ás foi de 11 para 1 para evitar estouro...\n");
                getchar();
            }
        }

        aux = aux->proximo;
    }
}

int somatorio_das_cartas(jogador *jogador) {
    int somatorio = 0;
    carta *aux = jogador->mao.topo;
    while(aux != NULL) {
        somatorio += aux->valor;
        aux = aux->proximo;
    }

    return somatorio;
}

void conferir_situacao_jogador(jogador *jogador) {
    if(jogador->indice_do_jogador == 0) {
        if(somatorio_das_cartas(jogador) > 21) {
            printf("\nO dealer estourou!\n");
            jogador->jogando = 0;
            getchar();
        }
        else if(somatorio_das_cartas(jogador) <= 21 && somatorio_das_cartas(jogador) > 16) {
            printf("\nO dealer decidiu parar...\n");
            jogador->jogando = 0;
            getchar();
        }
    }
    else {
        if(somatorio_das_cartas(jogador) > 21) {
            printf("\nO jogador %d%s estourou!\n", jogador->indice_do_jogador, (jogador->split == 1 ? ".2" : ""));
            getchar();
            jogador->jogando = 0;
        }
    }
}

void conferir_final_da_partida(jogadores *jogadores, int *continuar_mesa) {
    system("clear");
    
    jogador *aux = jogadores->inicio;
    int pontos_dealer = somatorio_das_cartas(aux);
    if(pontos_dealer > 21) {
        pontos_dealer = 0;
    }
    aux = aux->proximo;

    while(aux != jogadores->inicio) {

        // Se tiver apenas uma mão
        if(aux->proximo->split == 0) {

            // Tratando casos comuns e de BlackJack
            if((somatorio_das_cartas(aux) > 21 || somatorio_das_cartas(aux) < pontos_dealer) || (aux->blackjack == 0 && jogadores->inicio->blackjack == 1)) {
                printf("O jogador %d%s perdeu!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                printf("Dinheiro perdido: R$%.2lf\n", aux->aposta);
                jogadores->inicio->dinheiro += aux->aposta;
            }
            else if((somatorio_das_cartas(aux) == pontos_dealer) || (aux->blackjack == 1 && jogadores->inicio->blackjack == 1)) {
                printf("O jogador %d%s empatou!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta);
                aux->dinheiro += aux->aposta;
            }
            else if((somatorio_das_cartas(aux) > pontos_dealer) || (aux->blackjack == 1 && jogadores->inicio->blackjack == 0)) {
                printf("O jogador %d%s ganhou!\n", aux->indice_do_jogador, (aux->split == 1 ? ".2" : ""));
                if(aux->blackjack == 1) {
                    printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta * 2.5);
                    aux->dinheiro += aux->aposta * 2.5;
                    jogadores->inicio->dinheiro -= aux->aposta * 2.5;
                }
                else {
                    printf("Dinheiro devolvido: R$%.2lf\n", aux->aposta * 2);
                    aux->dinheiro += aux->aposta * 2;
                    jogadores->inicio->dinheiro -= aux->aposta * 2;
                }
            }

                if(aux->dinheiro < 0) {
                    printf("Dinheiro que você deve: R$%.2lf  ''⌐(ಠ۾ಠ)¬''\n\n", aux->dinheiro - 2 * aux->dinheiro);
                }
                else {
                    printf("Dinheiro total: R$%.2lf\n\n", aux->dinheiro);
                }

            aux = aux->proximo;
        }

        // Se tiver feito split
        else {
            int contador = 0;
            jogador *temp = aux;
            do {
                // Tratando casos comuns e de BlackJack
                if((somatorio_das_cartas(temp) > 21 || somatorio_das_cartas(temp) < pontos_dealer) || (temp->blackjack == 0 && jogadores->inicio->blackjack == 1)) {
                    printf("O jogador %d%s perdeu!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("Dinheiro perdido: R$%.2lf\n", temp->aposta);
                    jogadores->inicio->dinheiro += temp->aposta;
                }
                else if((somatorio_das_cartas(temp) == pontos_dealer) || (temp->blackjack == 1 && jogadores->inicio->blackjack == 1)) {
                    printf("O jogador %d%s empatou!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta);
                    aux->dinheiro += temp->aposta;
                }
                else if((somatorio_das_cartas(temp) > pontos_dealer) || (temp->blackjack == 1 && jogadores->inicio->blackjack == 0)) {
                    printf("O jogador %d%s ganhou!\n", temp->indice_do_jogador, (temp->split == 1 ? ".2" : ""));
                    if(temp->blackjack == 1) {
                        printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta * 2.5);
                        aux->dinheiro += temp->aposta * 2.5;
                        jogadores->inicio->dinheiro -= temp->aposta * 2.5;
                    }
                    else {
                        printf("Dinheiro devolvido: R$%.2lf\n", temp->aposta * 2);
                        aux->dinheiro += temp->aposta * 2;
                        jogadores->inicio->dinheiro -= temp->aposta * 2;
                    }
                }

                contador++;
                temp = temp->proximo;
            } while(temp->split != 0);

            temp = aux;
            do {
                temp->dinheiro = aux->dinheiro;
                temp = temp->proximo;
            } while(temp->split == 1);

            if(aux->dinheiro < 0) {
                printf("Dinheiro que você deve: R$%.2lf  ''⌐(ಠ۾ಠ)¬''\n\n", aux->dinheiro - 2 * aux->dinheiro);
            }
            else {
                printf("Dinheiro total: R$%.2lf\n\n", aux->dinheiro);
            }

            for(int i = 0; i < contador; i++) {
                aux = aux->proximo;
            }
        }
    }

    getchar();

    if(jogadores->inicio->dinheiro <= 0) {
        system("clear");
        printf("    e88~-_       e      ,d88~~\\      e          ,88~-_   888   | 888~~  888~~\\  888~-_     ,88~-_   888   | \n");
        printf("   d888   \\     d8b     8888        d8b        d888   \\  888   | 888___ 888   | 888   \\   d888   \\  888   | \n");
        printf("   8888        /Y88b    `Y88b      /Y88b      88888    | 888   | 888    888 _/  888    | 88888    | 888   | \n");
        printf("   8888       /  Y88b    `Y88b,   /  Y88b     88888    | 888   | 888    888  \\  888   /  88888    | 888   | \n");
        printf("   Y888   /  /____Y88b     8888  /____Y88b     Y888 \\ /  Y88   | 888    888   | 888_-~    Y888   /  Y88   | \n");
        printf("    '88_-~  /      Y88b \\__88P' /      Y88b     `88__X    '8__/  888___ 888__/  888 ~-_    `88_-~    '8__/  \n");

        *continuar_mesa = 0;
                        
        getchar();   
    }
}

int main() {
    
    setlocale(LC_ALL, "pt_BR.utf8");
    menu_inicial();
    return 0;

}