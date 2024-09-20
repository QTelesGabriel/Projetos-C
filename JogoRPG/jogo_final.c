#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "funcoes_auxiliares.h"

void jogo(const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento);

void jogo_facil(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito);

void jogo_medio(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito);

void jogo_dificil(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito);

void mapas_faceis(char mapa_1[][21], int escolha_mapa);

void mapas_medios(char mapa_2[][31], int escolha_mapa);

void mapas_dificeis(char mapa_3[][51], int escolha_mapa);

void jokenpo(int alinhamento, const char* nome, int *vida);

void charada(int vida);

int main()
{
    int ligado = 0;            /* Quando o jogo acabar vai voltar para o menu */

    while(ligado == 0) {
        int op_menu;                /* variável que vai guardar a opção escolhida no menu */

        int ok_menu = 0;            /* varíavel que vai permitir avançar depois de escolheu uma opção do menu */    
        int personagem_ok = 0;      /* variável que vai permitir começar o jogo apenas após criar personagem */
        int comecar_jogo = 0;       /* serve para permitir começar a jogar o jogo */

        char nome[20];                                      /* strings que vão guardar o nome do personagem */
        char historia_previa[400];                          /* a história prévia dele */
        int raca, alinhamento, profissao, porte;            /* inteiros que vão guardar os valores da raça, alinhamento, profissao e porte */
        int forca_antiga, destreza_antiga, inteligencia_antiga, constituicao_antiga;    /* inteiros que vão guardar os valores de força, destreza, inteligencia e constituicao antes de serem alterados devido as características do personagem */
        int forca, destreza, inteligencia, constituicao;    /* inteiros que vão guardar os valores depois de alterados devido aos atributos */
        int vida = 20;
        int atributo_principal;
        int sair_do_jogo;

        while(ok_menu == 0) {

            system("clear");        /*Limpar a tela assim que o jogo começar*/
            
            printf("1. Criar Personagem\n2. Jogar\n0. Sair\n\nEscolha uma opcao: ");
            scanf("%d", &op_menu);

            /* se a opção do menu for 1 */
            if(op_menu == 1) {

                int soma_atributos = 11;             /* vai verificar se a soma dos atributos foi maior que 10 */
                int ok_caracteristicas = 0;          /* vai garantir que o jogador escolheu opções válidas para raça, alin., prof., e porte */
                int ok_atributos = 0;                /* vai garantir que o jogador escolheu uma quantidade válida */

                system("clear");
                printf("=============================\n");
                printf("****CRIACAO DE PERSONAGEM****\n");
                printf("=============================\n");
                
                /* nome */
                printf("\nEscolha seu nome: ");
                scanf(" %20[^\n]", nome);

                /* raça */
                printf("\nEscolha sua raca:\n1. Humano\n2. Anao\n3. Elfo\nAviso: Se escolher *Anao* nao podera ser *Grande*\n");
                while(ok_caracteristicas == 0) {
                    scanf("%d", &raca);
                    if(raca == 1 || raca == 2 || raca == 3) {
                        ok_caracteristicas = 1;
                    } else {
                        printf("\nEscolha uma opcao valida!\n");
                    }
                }
                ok_caracteristicas = 0;

                /* alinhamento */
                printf("\nEscolha seu alinhamento:\n1. Mal\n2. Neutro\n3. Bom\nAviso: Se escolher *Bom* nao podera ser *Ladino*\n");
                while(ok_caracteristicas == 0) {
                    scanf("%d", &alinhamento);
                    if(alinhamento == 1 || alinhamento == 2 || alinhamento == 3) {
                        ok_caracteristicas = 1;
                    } else {
                        printf("\nEscolha uma opcao valida!\n");
                    }
                }
                ok_caracteristicas = 0;

                /* profissão */
                printf("\nEscolha sua profissao:\n1. Guerreiro\n2. Mago\n3. Ladino\n");
                while(ok_caracteristicas == 0) {
                    if(alinhamento == 3) {
                        scanf("%d", &profissao);
                        if(profissao == 1 || profissao == 2) {
                            ok_caracteristicas = 1;
                        }
                        else if(profissao == 3) {
                            printf("\nVoce nao pode escolher *Ladino* por ser *Bom*\nEscolha outra opcao!\n");
                        } else {
                            printf("\nEscolha uma opcao valida!\n");
                        }
                    } else {
                        scanf("%d", &profissao);
                        if(profissao == 1 || profissao == 2 || profissao == 3) {
                            ok_caracteristicas = 1;
                        } else {
                            printf("\nEscolha uma opcao valida!\n");
                        }
                    }
                }
                ok_caracteristicas = 0;

                /* porte */
                printf("\nEscolha seu porte:\n1. Grande\n2. Medio\n3. Pequeno\n");
                while(ok_caracteristicas == 0) {
                    if(raca == 2){
                        scanf("%d", &porte);
                        if(porte == 2 || porte == 3){
                            ok_caracteristicas = 1;
                        } else if(porte == 1) {
                            printf("\nVoce nao pode escolher *Grande* por ser *Anao*\nEscolha outra opcao!\n");
                        } else {
                            printf("\nEscolha uma opcao valida!\n");
                        }
                    } else {
                        scanf("%d", &porte);
                        if(porte == 1 || porte == 2 || porte == 3) {
                            ok_caracteristicas = 1;
                        } else {
                            printf("\nEscolha uma opcao valida!\n");
                        }
                    }
                }

                printf("\nDigite uma historia previa para o seu personagem:\n");
                scanf(" %400[^\n]", historia_previa);

                /* atributos */
                int aviso = 0;
                printf("\n\n**Atributos**\n\n");
                printf("Avisos:\n   A soma dos atributos deve ser no maximo igual a 10\n    Os atributos podem ir do nivel 1 ao 5 sem incluir os bonus ou as perdas\n");

                while(soma_atributos > 10) {
                    if(aviso > 0) {
                        printf("\nA soma dos atributos superou o valor 10!\nDivida corretamente os pontos entre os atributos\n");
                    }

                    /* força */
                    printf("\nEscolha seu nivel de forca\n");
                    while(ok_atributos == 0) {
                        scanf("%d", &forca_antiga);
                        if(forca_antiga > 5 || forca_antiga < 1) {
                            printf("\nEscolha um nivel possivel!\n");
                            continue;
                        } else {
                            ok_atributos = 1;
                        }
                    }
                    ok_atributos = 0;

                    /* destreza */
                    printf("\nEscolha seu nivel de destreza\n");
                    while(ok_atributos == 0) {
                        scanf("%d", &destreza_antiga);
                        if(destreza_antiga > 5 || destreza_antiga < 1) {
                            printf("\nEscolha um nivel possivel!\n");
                            continue;
                        } else {
                            ok_atributos = 1;
                        }
                    }
                    ok_atributos = 0;

                    /* inteligência */
                    printf("\nEscolha seu nivel de inteligencia\n");
                    while(ok_atributos == 0) {
                        scanf("%d", &inteligencia_antiga);
                        if(inteligencia_antiga > 5 || inteligencia_antiga < 1) {
                            printf("\nEscolha um nivel possivel!\n");
                            continue;
                        } else {
                            ok_atributos = 1;
                        }
                    }
                    ok_atributos = 0;

                    /* constituição */
                    printf("\nEscolha seu nivel de constituicao\n");
                    while(ok_atributos == 0) {
                        scanf("%d", &constituicao_antiga);
                        if(constituicao_antiga > 5 || constituicao_antiga < 1) {
                            printf("\nEscolha um nivel possivel!\n");
                            continue;
                        } else {
                            ok_atributos = 1;
                        }
                    }
                    ok_atributos = 0;

                    soma_atributos = forca_antiga + destreza_antiga + inteligencia_antiga + constituicao_antiga;
                    aviso++;
                }

                /* alteração nos atributos devido as características físicas */
                forca = forca_antiga;
                destreza = destreza_antiga;
                inteligencia = inteligencia_antiga;
                constituicao = constituicao_antiga;

                if(raca == 3) {
                    destreza += 1;
                    constituicao -= 1;
                }

                if(raca == 2) {
                    forca += 1;
                    destreza -= 1;;
                }

                if(profissao == 2) {
                    inteligencia += 1;
                    forca -= 2;
                }

                if(profissao == 3) {
                    destreza += 1;;
                    forca -= 1;
                    inteligencia -= 1;
                }

                if(constituicao > 0) {
                    vida *= constituicao;
                }
                else {
                    vida = 10;
                }

                /*Impressão da atualização de atributos*/
                printf("\nDevido suas caracteristicas fisicas seus atributos foram alterados.\n\n");
                printf("Forca:        %d -----> %d\n", forca_antiga, forca);
                printf("Destreza:     %d -----> %d\n", destreza_antiga, destreza);
                printf("Inteligencia: %d -----> %d\n", inteligencia_antiga, inteligencia);
                printf("Constituicao: %d -----> %d\n\n", constituicao_antiga, constituicao);
                printf("Vida: %d\n\n", vida);

                personagem_ok = 1;

                if(profissao == 1) {
                    atributo_principal = forca;
                }
                else if(profissao == 2) {
                    atributo_principal = inteligencia;
                }
                else if(profissao == 3) {
                    atributo_principal = destreza;
                }

                int escolha_ok = 0; /* para saber se a pessoa escolheu uma opção válida */

                int voltar_ao_menu = 0;
                printf("Seu personagem esta criado!\nSe deseja voltar ao menu inicial aperte 1\nSe deseja comecar a jogar aperte 2\n");
                scanf("%d", &voltar_ao_menu);

                while(escolha_ok == 0) {
                    if(voltar_ao_menu == 2) {
                        ok_menu = 1;
                        escolha_ok = 1;
                        comecar_jogo = 1;
                    } 
                    else if(voltar_ao_menu == 1) {
                        escolha_ok = 1;
                        printf("\n\n");
                    } else {
                        printf("Escolha uma opcao valida!\n");
                    }
                }
            }

            /* se a opção do menu for 2 */
            else if(op_menu == 2) {
                if(personagem_ok != 0) {
                    comecar_jogo = 1;
                    ok_menu = 1;
                } else {
                    printf("\nVoce ainda nao criou um personagem!\n...\n");
                    getchar();
                    getchar();
                }
            }

            /* se a opção do menu for 0 */
            else if(op_menu == 0) {
                
                int confirmar_saida;
                int confirmar_saida_ok = 0;
                
                printf("\nVocê realmente deseja sair?\nSe sim, digite 1\nSe nao, digite 2\n");
                while(confirmar_saida_ok == 0) {
                    scanf("%d", &confirmar_saida);
                    if(confirmar_saida == 1) {
                        sair_do_jogo = 1;
                        confirmar_saida_ok = 1;
                        ligado = 1;
                        break;
                    }
                    else if(confirmar_saida == 2) {
                        system("clear");
                        confirmar_saida_ok = 1;
                    }
                    else {
                        printf("\nDigite uma opcao valida\n");
                    }
                }
            }

            /* se opção do menu não for válida */
            else {
                printf("\nEscolha uma opcao valida!\n\n");
            }

            if(sair_do_jogo == 1) {
                break;
            }
        }

        ok_menu = 0; 

        /* começo do jogo */
        if(comecar_jogo == 1){
            jogo(nome, vida, atributo_principal, forca, constituicao, destreza, inteligencia, profissao, alinhamento);
        }
    }
}

void jogo(const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento) {

    int dificuldade;            /*variável que vai guardar a dificuldade que for escolhida*/
    int dificuldade_ok = 0;     /*variável que vai permitir sair do loop apenas quando for escolhido uma dificuldade válida*/
    int escolha_mapa;           /*variável que vai guardar qual mapa vai ser escolhido aleatoriamente*/ 

    char atributo_principal_escrito[15];
    if(profissao == 1) {
        strcpy(atributo_principal_escrito, "forca");
    }
    if(profissao == 2) {
        strcpy(atributo_principal_escrito, "inteligencia");
    }
    if(profissao == 3) {
        strcpy(atributo_principal_escrito, "destreza");
    }
    
    char profissao_escrito[10];
    if(profissao == 1) {
        strcpy(profissao_escrito, "guerreiro");
    }
    if(profissao == 2) {
        strcpy(profissao_escrito, "mago");
    }
    if(profissao == 3) {
        strcpy(profissao_escrito, "ladino");
    }
    
    char alinhamento_escrito[10];
    if(alinhamento == 1) {
        strcpy(alinhamento_escrito, "Mal");
    }
    if(alinhamento == 2) {
        strcpy(alinhamento_escrito, "Neutro");
    }
    if(alinhamento == 3) {
        strcpy(alinhamento_escrito, "Bom");
    }

    system("clear");

    while(dificuldade_ok == 0) {
        printf("Escolha a dificuldade\n1. Facil\n2. Medio\n3. Dificil\n");
        scanf("%d", &dificuldade);
        if(dificuldade == 1 || dificuldade == 2 || dificuldade == 3) {
            dificuldade_ok = 1;
        }
        else {
            printf("Escolha uma opcao valida!\n\n");
        }
    }

    srand(time(NULL));
    escolha_mapa = rand() % 2;

    system("clear");

    printf("Depois de um longo dia estudando no IDP, voce comeca a arrumar suas coisas para ir embora. \nPor ter perdido a nocao do tempo, voce nao se deu conta de que era o ultimo estudante presente na faculdade e que ela ja estava com todas as luzes apagadas e fechada.\n");
    printf("Saindo de fininho sem chamar atençao voce consegue chegar ao estacionamento onde esta seu Peugeot 206, voce bota a mao no bolso e percebe que a chave nao esta la.\n");
    getchar();
    printf("Por isso, voce tera que voltar para encontrar e recuperar a chave do seu Peugeot 206, com apenas uma lanterna.\n");
    
    getchar();

    system("clear");

/* Jogo fácil */
    if(dificuldade == 1) {
        jogo_facil(escolha_mapa, nome, vida, atributo_principal, forca, constituicao, destreza, inteligencia, profissao, alinhamento, atributo_principal_escrito, profissao_escrito, alinhamento_escrito);
    }

/* Jogo médio */
    else if(dificuldade == 2) {
        jogo_medio(escolha_mapa, nome, vida, atributo_principal, forca, constituicao, destreza, inteligencia, profissao, alinhamento, atributo_principal_escrito, profissao_escrito, alinhamento_escrito);        
    }

/* Jogo difícil */
    else if(dificuldade == 3) {
        jogo_dificil(escolha_mapa, nome, vida, atributo_principal, forca, constituicao, destreza, inteligencia, profissao, alinhamento, atributo_principal_escrito, profissao_escrito, alinhamento_escrito);
    }
}

void mapas_faceis(char mapa_1[][21], int escolha_mapa) {
    if(escolha_mapa == 0) {

        /*MAPA DESBLOQUEADO 1*/
        strcpy(mapa_1[0], "####################");
        strcpy(mapa_1[1], "#   ##       ### V##");
        strcpy(mapa_1[2], "##  ####   # ### ###");
        strcpy(mapa_1[3], "##         ##### ###");
        strcpy(mapa_1[4], "##  ###### ##     ##");
        strcpy(mapa_1[5], "### #####     ######");
        strcpy(mapa_1[6], "###        ##      #");
        strcpy(mapa_1[7], "###  ########### H #");
        strcpy(mapa_1[8], "#    ##     ###### #");
        strcpy(mapa_1[9], "###             #  #");
        strcpy(mapa_1[10],"### ###########   ##");
        strcpy(mapa_1[11],"##  #      ######V##");
        strcpy(mapa_1[12],"#   ##        ######");
        strcpy(mapa_1[13],"# #    ### ## ######");
        strcpy(mapa_1[14],"#P# ###### ##     H#");
        strcpy(mapa_1[15],"###  ###   #########");
        strcpy(mapa_1[16],"#    #####  ##    ##");
        strcpy(mapa_1[17],"# #  #####     ##  #");
        strcpy(mapa_1[18],"#H##    ######### C#");
        strcpy(mapa_1[19],"####################");
    }

    else if(escolha_mapa == 1) {

        /*MAPA DESBLOQUEADO 2*/
        strcpy(mapa_1[0], "####################");
        strcpy(mapa_1[1], "#   ##H   ###V     #");
        strcpy(mapa_1[2], "### #####  ######  #");
        strcpy(mapa_1[3], "### ##     #####  ##");
        strcpy(mapa_1[4], "#   ##     ###   H##");
        strcpy(mapa_1[5], "# #### ### ### #####");
        strcpy(mapa_1[6], "#  ### ###  ##     #");
        strcpy(mapa_1[7], "#  ##   ##  ## #####");
        strcpy(mapa_1[8], "# ##### ##        ##");
        strcpy(mapa_1[9], "# ##### ##  ####  ##");
        strcpy(mapa_1[10],"#       ##  ##### ##");
        strcpy(mapa_1[11],"#### #####  ##    ##");
        strcpy(mapa_1[12],"##   ##P##V###### ##");
        strcpy(mapa_1[13],"#H #### #####      #");
        strcpy(mapa_1[14],"## # ## ####### ####");
        strcpy(mapa_1[15],"##   ##   ##     ###");
        strcpy(mapa_1[16],"#  ######     ## ###");
        strcpy(mapa_1[17],"# ############## ###");
        strcpy(mapa_1[18],"#    ##C           #");
        strcpy(mapa_1[19],"####################");
    }
}

void mapas_medios(char mapa_2[][31], int escolha_mapa) {
    if(escolha_mapa == 0) {

        strcpy(mapa_2[0], "##############################");
        strcpy(mapa_2[1], "#                   ##       #");
        strcpy(mapa_2[2], "#####  ########     ##  ###  #");
        strcpy(mapa_2[3], "#####    #########  ##  ###  #");
        strcpy(mapa_2[4], "#      ###########       ### #");
        strcpy(mapa_2[5], "# ###     ##           ##### #");
        strcpy(mapa_2[6], "# ###     #########       ##H#");
        strcpy(mapa_2[7], "#######   #############  V####");
        strcpy(mapa_2[8], "#######  ###         #########");
        strcpy(mapa_2[9], "##H       #    #########P    #");
        strcpy(mapa_2[10],"#####  ####  #######        ##");
        strcpy(mapa_2[11],"#####  ####             ##  ##");
        strcpy(mapa_2[12],"###          ###### ####### ##");
        strcpy(mapa_2[13],"####         ###### ####### ##");
        strcpy(mapa_2[14],"####    ###########   #     ##");
        strcpy(mapa_2[15],"##   #  #####         #    ###");
        strcpy(mapa_2[16],"#    #    H##########H#    ###");
        strcpy(mapa_2[17],"##   #   #########    #     ##");
        strcpy(mapa_2[18],"##  ###      ########## ######");
        strcpy(mapa_2[19],"#   #######   ##         V####");
        strcpy(mapa_2[20],"# #####       ## #############");
        strcpy(mapa_2[21],"# ##          ##            ##");
        strcpy(mapa_2[22],"#V##  #####  ##### ######## ##");
        strcpy(mapa_2[23],"####  #####  ######   ##    ##");
        strcpy(mapa_2[24],"###     ###  #######  ## H  ##");
        strcpy(mapa_2[25],"#    ##  ### ##       ########");
        strcpy(mapa_2[26],"###  ##   ##P######    #######");
        strcpy(mapa_2[27],"#    ##   ###########        #");
        strcpy(mapa_2[28],"#### ##H   ##C         ####  #");
        strcpy(mapa_2[29],"##############################");
    }

    else if(escolha_mapa == 1) {
        strcpy(mapa_2[0],  "##############################");                            
        strcpy(mapa_2[1],  "#         ###    V######### ##");
        strcpy(mapa_2[2],  "##              ########### ##");
        strcpy(mapa_2[3],  "## ###      #               ##");
        strcpy(mapa_2[4],  "## ####   ######    ######  ##");
        strcpy(mapa_2[5],  "##   ###     ##       ####  ##");
        strcpy(mapa_2[6],  "#  ####   #######    ####   ##");
        strcpy(mapa_2[7],  "# ##H      #####       ## # ##");                          
        strcpy(mapa_2[8],  "# ############   #   #### #  #");
        strcpy(mapa_2[9],  "#   ##          ##    ### #  #");                             
        strcpy(mapa_2[10], "#   ##    #### ###    ######H#");
        strcpy(mapa_2[11], "#   ###    ###   ###      ####");
        strcpy(mapa_2[12], "########     ###  ####    ####");
        strcpy(mapa_2[13], "##H           ##  ###       ##");
        strcpy(mapa_2[14], "#######       ##  ##     #  ##");
        strcpy(mapa_2[15], "###         ####  ##  #####  #");
        strcpy(mapa_2[16], "##    ###    ########  #######");
        strcpy(mapa_2[17], "##   ###      ######        V#");                   
        strcpy(mapa_2[18], "#   #####   ########       ###");
        strcpy(mapa_2[19], "##   #####  #         ##    ##");
        strcpy(mapa_2[20], "###V H#######    #######    ##");
        strcpy(mapa_2[21], "##########           ###  P###");
        strcpy(mapa_2[22], "############         #########");                          
        strcpy(mapa_2[23], "#              ###      ######");
        strcpy(mapa_2[24], "#  #######   #####           #");
        strcpy(mapa_2[25], "#  ##P      #######    ####  #");
        strcpy(mapa_2[26], "#  ####       ##      #####  #");
        strcpy(mapa_2[27], "#####      #####   ########  #");
        strcpy(mapa_2[28], "####V     #####       H##C   #");
        strcpy(mapa_2[29], "##############################");
    }
}

void mapas_dificeis(char mapa_3[][51], int escolha_mapa) {
    if(escolha_mapa == 0) {
        strcpy(mapa_3[0], "##################################################");
        strcpy(mapa_3[1], "#      ########      #########       #####     V##");
        strcpy(mapa_3[2], "#  ######       ##    #####H     ##    ###  ### ##");
        strcpy(mapa_3[3], "#  ######  ###   ###  ##### ##     ##  ###  ###  #");
        strcpy(mapa_3[4], "#   ###   #####  ###  ##### #####  ##        ##  #");
        strcpy(mapa_3[5], "#       #######  ###  ##### #####  #######  ###  #");
        strcpy(mapa_3[6], "###  #######     ###        #####  ######  ####  #");
        strcpy(mapa_3[7], "###  ######  ##  #######   ######  #####   #######");
        strcpy(mapa_3[8], "####  ##### ###  ########                  #######");
        strcpy(mapa_3[9], "#####  ##H  ###  ##############  #########       #");
        strcpy(mapa_3[10],"#####  #######  #####P           ############  ###");
        strcpy(mapa_3[11],"#####  ########  ##############   ##### #####  ###");
        strcpy(mapa_3[12],"#           ###  ##  #######  ##   #### #####  ###");
        strcpy(mapa_3[13],"############################  ##   #### #####  ###");
        strcpy(mapa_3[14],"############################       ###H #####  ###");
        strcpy(mapa_3[15],"###                                     #####    #");
        strcpy(mapa_3[16],"##########    ###############################  # #");
        strcpy(mapa_3[17],"###V   ###   ################################  # #");
        strcpy(mapa_3[18],"####         ###############                #  #V#");
        strcpy(mapa_3[19],"##########                   ################  ###");
        strcpy(mapa_3[20],"#               #######           ##########   ###");
        strcpy(mapa_3[21],"#           ###############    ###             ###");
        strcpy(mapa_3[22],"###        H###############    ####              #");
        strcpy(mapa_3[23],"#########################    ###########      ## #");
        strcpy(mapa_3[24],"########                        #######    ##### #");
        strcpy(mapa_3[25],"########           ####### #    #######    ##### #");
        strcpy(mapa_3[26],"#######   #######   #####  ###      #     ###### #");
        strcpy(mapa_3[27],"#######   ########   ####  #######        ###### #");
        strcpy(mapa_3[28],"####      ##########   ### ########   ######     #");
        strcpy(mapa_3[29],"#####  #########P       ## ##             H####  #");
        strcpy(mapa_3[30],"#####  #### ##########  #######################  #");
        strcpy(mapa_3[31],"#####          #######  #######################  #");
        strcpy(mapa_3[32],"#####  ####### #######                 ########  #");
        strcpy(mapa_3[33],"#H     #####V  ########  ###########         ##  #");
        strcpy(mapa_3[34],"#####  #######     ####  ######       ########## #");
        strcpy(mapa_3[35],"#           #####  ####  ###### ####       V#### #");
        strcpy(mapa_3[36],"####  ####  #####  ###   #   #######  ########## #");
        strcpy(mapa_3[37],"####  ####  ##### H###   ###               ####H##");
        strcpy(mapa_3[38],"####  ####  #########    ####  ################ ##");
        strcpy(mapa_3[39],"####  ####        ###    ####   ############### ##");
        strcpy(mapa_3[40],"####  ###############    ######   #        P### ##");
        strcpy(mapa_3[41],"###        #######       ######      ########## ##");
        strcpy(mapa_3[42],"#####               ######## ######  ###  ##### ##");
        strcpy(mapa_3[43],"####################### # ########              ##");
        strcpy(mapa_3[44],"##P                V###                    #######");
        strcpy(mapa_3[45],"##      #########       ############   ###########");
        strcpy(mapa_3[46],"####    ############################         #####");
        strcpy(mapa_3[47],"######   ######           #########   ############");
        strcpy(mapa_3[48],"##                       C##                   H##");
        strcpy(mapa_3[49],"##################################################");
    }

    else if(escolha_mapa == 1) {
        strcpy(mapa_3[0], "##################################################");
        strcpy(mapa_3[1], "#                                   ########    ##");
        strcpy(mapa_3[2], "##        #####  #######   ###          ###   ####");
        strcpy(mapa_3[3], "#######   #####  ########   #####  ##         H###");
        strcpy(mapa_3[4], "##        #####  #######    #####  ####   ########");
        strcpy(mapa_3[5], "##   #    #####  ######H       ##  ####   ########");
        strcpy(mapa_3[6], "###  ##          #######     ###########  ########");
        strcpy(mapa_3[7], "###  ######## ##########################     #####");
        strcpy(mapa_3[8], "###  ########     ############                  P#");          
        strcpy(mapa_3[9], "###      ############V            ######     #####");
        strcpy(mapa_3[10],"###########   #########    #########         #####");
        strcpy(mapa_3[11],"#                                                #");
        strcpy(mapa_3[12],"#       #########     #######  #########    ######");
        strcpy(mapa_3[13],"#      #########    #########  ########     ######");
        strcpy(mapa_3[14],"#     ##########   ##########  #########    ######");
        strcpy(mapa_3[15],"#                       H##############     ######");
        strcpy(mapa_3[16],"#   ##    ###    ############                 ####");
        strcpy(mapa_3[17],"#   ####   #  ########################         ###");
        strcpy(mapa_3[18],"#   #####  #          ##########    ###      #####");
        strcpy(mapa_3[19],"#   V###   #           #########   #####       ###");
        strcpy(mapa_3[20],"########   #    #####  ####                #######");
        strcpy(mapa_3[21],"########  ##     #################   ####    #####");
        strcpy(mapa_3[22],"#H       ####  ##########              ##    #####");
        strcpy(mapa_3[23],"##    ####     ####   ################      ######");
        strcpy(mapa_3[24],"##########     ##        #########            ####");
        strcpy(mapa_3[25],"####           #    ################    ##    ####");
        strcpy(mapa_3[26],"############   #               ####     ##       #");
        strcpy(mapa_3[27],"###########          ######    ###  ##  ##   ### #");
        strcpy(mapa_3[28],"##      #             ######## ####  ## ###  H## #");
        strcpy(mapa_3[29],"#######         ###       #### ###   ## ######## #");
        strcpy(mapa_3[30],"#         ###    ###    ###########  ##  ####### #");
        strcpy(mapa_3[31],"##          ###   ####   ######P     ##  #####   #");
        strcpy(mapa_3[32],"###   #   #####      #       #################   #");
        strcpy(mapa_3[33],"#    ##   ############                     ###   #");
        strcpy(mapa_3[34],"##   ##       ##P######                   ########");
        strcpy(mapa_3[35],"##   ########### ################      ###########");
        strcpy(mapa_3[36],"##     #########        #######         ##########");
        strcpy(mapa_3[37],"#   #   ###      ###### ##                     ###");
        strcpy(mapa_3[38],"#   #######  ### ###    #####             ########");
        strcpy(mapa_3[39],"#    #####   ### ##########        #####     #####");
        strcpy(mapa_3[40],"#  H##     ##### ###########    ###########      #");
        strcpy(mapa_3[41],"## ### ######### #####         #########        ##");
        strcpy(mapa_3[42],"##### ##########            ######################");
        strcpy(mapa_3[43],"########            #################H         ###");
        strcpy(mapa_3[44],"##H        #######P                             ##");
        strcpy(mapa_3[45],"#########################################      ###");
        strcpy(mapa_3[46],"######         ###########################     ###");
        strcpy(mapa_3[47],"###    ######                                   ##");
        strcpy(mapa_3[48],"#####         C#############################    V#");
        strcpy(mapa_3[49],"##################################################");
    }
}

void jogo_facil(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito)
{
    int i, j;
    char personagem = 'O';
    int ataque_monstro = 10, defesa_monstro = 2;
    int vida_monstro[4] = {6};
    int acrescimos = 0;
    char mapa_1[20][21];

    /*Definir o mapa do jogo*/
    mapas_faceis(mapa_1, escolha_mapa);

    /*MAPA BLOQUEADO*/
    char mapa[20][20];
    for(i = 0; i < 20; i++) {
        for(j = 0; j < 20; j++) {
            mapa[i][j] = '?';
        }
    }

    /*MAPA BLOQUEADO CÓPIA*/
    char mapa_copia[20][20];
    for(i = 0; i < 20; i++) {
        for(j = 0; j < 20; j++) {
            mapa_copia[i][j] = '?';
        }
    }

    int continuar_ate_break = 0;
    int contador;

    /*Preparar as armadilhas*/
    /*Posição: armadilha 1*/
    int axfac[6];
    int ayfac[6];

    for(contador = 0; contador <= 5; contador ++) {
        while(continuar_ate_break == 0) {
            axfac[contador] = rand() % 15;
            ayfac[contador] = rand() % 15;
            if(mapa_1[axfac[contador] + 5][ayfac[contador] + 5] == ' ') {
                axfac[contador] += 5;
                ayfac[contador] += 5;
                break;
            }
        }
    }

    /*Variáveis para permitir que a armadilha possa ser percebida automaticamente apenas uma vez*/
    int teste_fac[6] = {0};

    /*Criando a visão do jogador para imprimir o mapa*/
    char movimento;
    int n = 1;
    int m = 1;

    for(i = -2; i <= 2; i++) {
        for(j = -2; j <= 2; j++) {
            if(n + i >= 0 && m + j >= 0) {
                mapa[n + i][m + j] = mapa_1[n + i][m + j];
            }
            if(i == 0 && j == 0) {
                mapa[n + i][m + j] = personagem;
            }
        }
    }
    
    int mxfac[4];
    int myfac[4];

    srand(time(NULL));
    int x_monstro = 0, y_monstro = 0;

    for(contador = 0; contador < 4; contador++) {
        while(mapa_1[x_monstro][y_monstro] != ' ') {
            x_monstro = (rand() % 9) + 11;
            y_monstro = (rand() % 9) + 11;
            mxfac[contador] = x_monstro;
            myfac[contador] = y_monstro;
        }
        mapa_1[mxfac[contador]][myfac[contador]] = 'M';
    }

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 20; j++) {
            printf("%c", mapa[i][j]);
            if(mapa[i][j] == '#') {
                printf("#");
            }
            else if(mapa[i][j] == ' ') {
                printf(" ");
            }
            else if(mapa[i][j] == '?') {
                printf("?");
            }
            else if(mapa[i][j] == 'O') {
                printf("O");
            }

        }
        if(i == 0) {
            printf("                    Vida: %d", vida);
        }
        if(i == 1) {
            printf("                    Profissao: %s", profissao_escrito);
        }
        if(i == 2) {
            printf("                    Alinhamento: %s", alinhamento_escrito);
        }
        if(i == 3) {
            printf("                    Atributo principal: %s", atributo_principal_escrito);
        }
        if(i == 4) {
            printf("                    Forca: %d", forca);
        }
        if(i == 5) {
            printf("                    Inteligencia: %d", inteligencia);
        }
        if(i == 6) {
            printf("                    Destreza: %d", destreza);
        }
        if(i == 7) {
            printf("                    Constituicao: %d", constituicao);
        }
        if(i == 9) {
            printf("                    Nome: %s", nome);
        }
        putchar('\n');
    }

    int turnos_potencializacao; /*variável que vai guardar a quantidade de turnos que algo vai acontecer*/
    int turnos_visao;
    int atributo_principal_potencializado = 2 * atributo_principal;
    int atributo_principal_temp = atributo_principal;
    int visao = 2;
    int limite = 3;

    int ir_para_boss = 0;

    /*MOVIMENTAÇÃO SER INFINITA ATÉ O JOGO ACABAR*/
    while(vida > 0 && ir_para_boss == 0) {
        /*scanf(" %c", &movimento); */
        movimento = le_tecla();
        system("clear");
        
        if(mapa_1[n][m + 1] != '#' && mapa_1[n][m + 1] != 'M') {
            if(movimento == 'd' || movimento == 'D') {          /*Movimentação para a direita*/
                mapa[n][m + 1] = mapa_1[n][m + 1];
                mapa[n][m] = mapa_copia[n][m];
                m++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_1[n][m] = ' ';
                    turnos_visao = 30;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 20; i++) {
                        for(j = 0; j < 20; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 19 && m + j <= 19)) {
                            mapa[n + i][m + j] = mapa_1[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m - limite >= 0) {
                        mapa[n + i][m - limite] = mapa_copia[n + i][m - limite];
                    }
                }
            }
        }

        if(mapa_1[n][m - 1] != '#' && mapa_1[n][m - 1] != 'M') {
            if(movimento == 'a' || movimento == 'A') {          /*Movimentação para a esquerda*/
                mapa[n][m - 1] = mapa_1[n][m - 1];
                mapa[n][m] = mapa_copia[n][m];
                m--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_1[n][m] = ' ';
                    turnos_visao = 30;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 20; i++) {
                        for(j = 0; j < 20; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 19 && m + j <= 19)) {
                            mapa[n + i][m + j] = mapa_1[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m + limite >= 0) {
                        mapa[n + i][m + limite] = mapa_copia[n + i][m + limite];
                    }
                }
            }
        }

        if(mapa_1[n - 1][m] != '#' && mapa_1[n - 1][m] != 'M') {
            if(movimento == 'w' || movimento == 'W') {          /*Movimentação se for para cima*/
                mapa[n - 1][m] = mapa_1[n - 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_1[n][m] = ' ';
                    turnos_visao = 30;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 20; i++) {
                        for(j = 0; j < 20; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 19 && m + j <= 19)) {
                            mapa[n + i][m + j] = mapa_1[n + i][m + j];
                        }
                    }   
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + limite >= 0 && m + i >= 0) {
                        mapa[n + limite][m + i] = mapa_copia[n + limite][m + i];
                    }
                }
            }
        }

        if(mapa_1[n + 1][m] != '#' && mapa_1[n + 1][m] != 'M') {
            if(movimento == 's' || movimento == 'S') {          /*Movimentação se for para baixo*/
                mapa[n + 1][m] = mapa_1[n + 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_1[n][m] = ' ';
                    turnos_visao = 30;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 20; i++) {
                        for(j = 0; j < 20; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i >= 0 && m + j >= 0) {
                            if((n + i >= 0 && m + j >= 0) && (n + i <= 19 && m + j <= 19)) {
                                mapa[n + i][m + j] = mapa_1[n + i][m + j];
                            }
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n - limite >= 0 && m + i >= 0) {
                        mapa[n - limite][m + i] = mapa_copia[n - limite][m + i];
                    }
                }
            }
        }

        /*Conferir se caiu na cura ou no potencializador*/
        if(mapa[n][m] == 'H') {
            mapa_1[n][m] = ' ';
            vida += 20;
        }
        
        if(mapa[n][m] == 'P') {
            mapa_1[n][m] = ' ';
            turnos_potencializacao = 30;
            atributo_principal = atributo_principal_potencializado;
        }
        
        turnos_potencializacao -= 1;
        if(turnos_potencializacao == 0) {
            atributo_principal = atributo_principal_temp;
        }

        /*Conferir se alguma armadilha entrou na visão do jogador*/
        float perceber_armadilha_float;

        float destreza_float = (float)destreza;
        float inteligencia_float = (float)inteligencia;

        if(profissao == 3) {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 12) * 100);
        }
        else {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 20) * 100);
        }

        int perceber_armadilha = (int)perceber_armadilha_float;

        int num_aleatorio_perceber_armadilha;

        srand(time(NULL));
        num_aleatorio_perceber_armadilha = rand() % 101;

        for(contador = 0; contador <= 5; contador++) {
            for(i = -visao; i <= visao; i++) {
                for(j = -visao; j <= visao; j++) {
                    if(n + i == axfac[contador] && m + j == ayfac[contador]) {
                        if(teste_fac[contador] == 0) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_1[axfac[contador]][ayfac[contador]] != '-') {
                                    mapa_1[axfac[contador]][ayfac[contador]] = 'A';
                                    mapa[axfac[contador]][ayfac[contador]] = 'A';
                                }
                            }
                            teste_fac[contador] = 1;
                        }
                    }
                }
            }
        }

        /* Teste de armadilha forçado pela tecla T ou t */
        if(movimento == 't' || movimento == 'T') {
            for(contador = 0; contador <= 5; contador++) {
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i == axfac[contador] && m + j == ayfac[contador]) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_1[axfac[contador]][ayfac[contador]] != '-') {
                                    mapa_1[axfac[contador]][ayfac[contador]] = 'A';
                                    mapa[axfac[contador]][ayfac[contador]] = 'A';
                                }
                            }
                        }
                    }
                }
            }
            vida -= 1;
        } 

        /* Atacar os monstros */
        if(movimento == 'b' || movimento == 'B') {
            if(profissao == 2) {                /* Se for mago */
                for(contador = 0; contador < 4; contador++) {
                    for(i = -2; i <= 2; i++) {
                        for(j = -2; j <= 2; j++) {
                            if(n + i == mxfac[contador] && m + j == myfac[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_1[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
            else {                              /* Se for de outra profissao */
                for(contador = 0; contador < 4; contador++) {
                    for(i = -1; i <= 1; i++) {
                        for(j = -1; j <= 1; j++) {
                            if(n + i == mxfac[contador] && m + j == myfac[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_1[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
        }

        /* Conferir se caiu na armadilha */
        for(contador = 0; contador <= 5; contador++) {
            if(n == axfac[contador] && m == ayfac[contador]) {
                if(mapa_1[n][m] != '-') {
                    vida -= 5;
                    mapa_1[n][m] = '-';
                    teste_fac[contador] = 1;
                }
            }
        }

        /*Ataque do monstro*/
        for(contador = 0; contador < 4; contador++) {
            for(i = -1; i <= 1; i++) {
                for(j = -1; i <= 1; i++) {
                    if(mxfac[contador] + i == n && myfac[contador] + j == m) {
                        if(mapa_1[mxfac[contador]][myfac[contador]] == 'M') {
                            if(ataque_monstro - forca + acrescimos > 0) {
                                vida -= (ataque_monstro - forca + acrescimos);
                            }
                            else {
                                vida -= 0;
                            }
                        }  
                    }
                }
            }
        }
        

        /*Colocar o personagem no meio da visão*/
        mapa[n][m] = personagem;
        
        /*Impressão do mapa*/
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 20; j++) {
                printf("%c", mapa[i][j]);
                if(mapa[i][j] == '#') {
                    printf("#");
                }
                else if(mapa[i][j] == ' ') {
                    printf(" ");
                }
                else if(mapa[i][j] == '?') {
                    printf("?");
                }
                else if(mapa[i][j] == 'O') {
                    printf("O");
                }
                else if(mapa[i][j] == 'H') {
                    printf("p");
                }
                else if(mapa[i][j] == 'P') {
                    printf("o");
                }
                else if(mapa[i][j] == 'V') {
                    printf("i");
                }
                else if(mapa[i][j] == 'C') {
                    printf("h");
                }
                else if(mapa[i][j] == 'A') {
                    printf("r");
                }
                else if(mapa[i][j] == '-') {
                    printf("-");
                }
                else if(mapa[i][j] == 'M') {
                    printf("o");
                }
            }
            if(i == 0) {
                printf("                    Vida: %d", vida);
            }
            if(i == 1) {
                printf("                    Profissao: %s", profissao_escrito);
            }
            if(i == 2) {
                printf("                    Alinhamento: %s", alinhamento_escrito);
            }
            if(i == 3) {
                printf("                    Atributo principal: %s", atributo_principal_escrito);
            }
            if(i == 4) {
                printf("                    Forca: %d", forca);
            }
            if(i == 5) {
                printf("                    Inteligencia: %d", inteligencia);
            }
            if(i == 6) {
                printf("                    Destreza: %d", destreza);
            }
            if(i == 7) {
                printf("                    Constituicao: %d", constituicao);
            }
            if(i == 9) {
                printf("                    Nome: %s", nome);
            }
            putchar('\n');
        }

        if(mapa_1[n][m] == '-') {
            /*Criar texto para quando cair na armadilha*/
            printf("\nvoce caiu em cima de uma armadilha\n");
        }

        if(mapa_1[n][m] == 'H') {
            /*Criar texto para quando cair em poção de cura*/
            printf("\nVoce encontrou um cookie da Johns e o comeu, recuperando 20 de vida\n");
        }

        if(mapa_1[n][m] == 'V') {
            /*Criar texto para quando cair em poção de visão além do alcance*/
            printf("\nVoce encontrou uma bateria muito forte para sua lanterna e aumentou a potencia dela por um tempo\n");
        }

        if(mapa_1[n][m] == 'P') {
            /*Criar texto para quando cair em poção de potencializador de atributo principal*/
            printf("\nVoce encontrou um redbull que aumentou seu atributo principal\n");
        }

        if(mapa_1[n][m] == 'C') {
            ir_para_boss = 1;
            printf("\n\nVoce encontrou o Nilson com as chaves do seu Peugeot 206...\n\n");
            getchar();
        }

        if(vida <= 0) {
            printf("\nVoce perdeu e nao achou sua chave do Peugeot 206");
            getchar();        
        }
    }

    if(ir_para_boss == 1) {

        system ("clear");
        
        /*Realizar boss fight*/
        jokenpo(alinhamento, nome, &vida);       /*Jokenpô*/

        if(vida > 0) {
            charada(vida);
        }
    }   
}

void jogo_medio(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito)
{
    int i, j;
    char personagem = 'O';
    int ataque_monstro = 10, defesa_monstro = 2;
    int vida_monstro[10] = {6};
    int acrescimos = 0;
    char mapa_2[30][31];

    /*Definir o mapa do jogo*/
    mapas_medios(mapa_2, escolha_mapa);

    /*MAPA BLOQUEADO*/
    char mapa[30][30];
    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            mapa[i][j] = '?';
        }
    }

    /*MAPA BLOQUEADO CÓPIA*/
    char mapa_copia[30][30];
    for(i = 0; i < 30; i++) {
        for(j = 0; j < 30; j++) {
            mapa_copia[i][j] = '?';
        }
    }

    int continuar_ate_break = 0;
    int contador;

    /*Preparar as armadilhas*/
    /*Posição: armadilha 1*/
    int axmed[10];
    int aymed[10];

    for(contador = 0; contador <= 9; contador ++) {
        while(continuar_ate_break == 0) {
            axmed[contador] = rand() % 25;
            aymed[contador] = rand() % 25;
            if(mapa_2[axmed[contador] + 5][aymed[contador] + 5] == ' ') {
                axmed[contador] += 5;
                aymed[contador] += 5;
                break;
            }
        }
    }

    /*Variáveis para permitir que a armadilha possa ser percebida automaticamente apenas uma vez*/
    int teste_med[10] = {0};

    /*Criando a visão do jogador para imprimir o mapa*/
    char movimento;
    int n = 1;
    int m = 1;

    for(i = -2; i <= 2; i++) {
        for(j = -2; j <= 2; j++) {
            if(n + i >= 0 && m + j >= 0) {
                mapa[n + i][m + j] = mapa_2[n + i][m + j];
            }
            if(i == 0 && j == 0) {
                mapa[n + i][m + j] = personagem;
            }
        }
    }

    int mxmed[10];
    int mymed[10];

    srand(time(NULL));
    int x_monstro = 0, y_monstro = 0;

    for(contador = 0; contador < 10; contador++) {
        while(mapa_2[x_monstro][y_monstro] != ' ') {
            x_monstro = (rand() % 19) + 11;
            y_monstro = (rand() % 19) + 11;
            mxmed[contador] = x_monstro;
            mymed[contador] = y_monstro;
        }
        mapa_2[mxmed[contador]][mymed[contador]] = 'M';
    }

    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            printf("%c", mapa[i][j]);
            if(mapa[i][j] == '#') {
                printf("#");
            }
            else if(mapa[i][j] == ' ') {
                printf(" ");
            }
            else if(mapa[i][j] == '?') {
                printf("?");
            }
            else if(mapa[i][j] == 'O') {
                printf("O");
            }
        }
        if(i == 0) {
            printf("                    Vida: %d", vida);
        }
        if(i == 1) {
            printf("                    Profissao: %s", profissao_escrito);
        }
        if(i == 2) {
            printf("                    Alinhamento: %s", alinhamento_escrito);
        }
        if(i == 3) {
            printf("                    Atributo principal: %s", atributo_principal_escrito);
        }
        if(i == 4) {
            printf("                    Forca: %d", forca);
        }
        if(i == 5) {
            printf("                    Inteligencia: %d", inteligencia);
        }
        if(i == 6) {
            printf("                    Destreza: %d", destreza);
        }
        if(i == 7) {
            printf("                    Constituicao: %d", constituicao);
        }
        if(i == 9) {
            printf("                    Nome: %s", nome);
        }
        putchar('\n');
    }

    int turnos_potencializacao; /*variável que vai guardar a quantidade de turnos que algo vai acontecer*/
    int turnos_visao;
    int atributo_principal_potencializado = 2 * atributo_principal;
    int atributo_principal_temp = atributo_principal;
    int visao = 2;
    int limite = 3;

    int ir_para_boss = 0;

    /*MOVIMENTAÇÃO SER INFINITA ATÉ O JOGO ACABAR*/
    while(vida > 0 && ir_para_boss == 0) {
        /*scanf(" %c", &movimento); */
        movimento = le_tecla();
        system("clear");
        
        if(mapa_2[n][m + 1] != '#' && mapa_2[n][m + 1] != 'M') {
            if(movimento == 'd' || movimento == 'D') {          /*Movimentação para a direita*/
                mapa[n][m + 1] = mapa_2[n][m + 1];
                mapa[n][m] = mapa_copia[n][m];
                m++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_2[n][m] = ' ';
                    turnos_visao = 40;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 30; i++) {
                        for(j = 0; j < 30; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 29 && m + j <= 29)) {
                            mapa[n + i][m + j] = mapa_2[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m - limite >= 0) {
                        mapa[n + i][m - limite] = mapa_copia[n + i][m - limite];
                    }
                }
            }
        }

        if(mapa_2[n][m - 1] != '#' && mapa_2[n][m - 1] != 'M') {
            if(movimento == 'a' || movimento == 'A') {          /*Movimentação para a esquerda*/
                mapa[n][m - 1] = mapa_2[n][m - 1];
                mapa[n][m] = mapa_copia[n][m];
                m--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_2[n][m] = ' ';
                    turnos_visao = 40;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 30; i++) {
                        for(j = 0; j < 30; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 29 && m + j <= 29)) {
                            mapa[n + i][m + j] = mapa_2[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m + limite >= 0) {
                        mapa[n + i][m + limite] = mapa_copia[n + i][m + limite];
                    }
                }
            }
        }

        if(mapa_2[n - 1][m] != '#' && mapa_2[n - 1][m] != 'M') {
            if(movimento == 'w' || movimento == 'W') {          /*Movimentação se for para cima*/
                mapa[n - 1][m] = mapa_2[n - 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_2[n][m] = ' ';
                    turnos_visao = 40;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 30; i++) {
                        for(j = 0; j < 30; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 29 && m + j <= 29)) {
                            mapa[n + i][m + j] = mapa_2[n + i][m + j];
                        }
                    }   
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + limite >= 0 && m + i >= 0) {
                        mapa[n + limite][m + i] = mapa_copia[n + limite][m + i];
                    }
                }
            }
        }

        if(mapa_2[n + 1][m] != '#' && mapa_2[n + 1][m] != 'M') {
            if(movimento == 's' || movimento == 'S') {          /*Movimentação se for para baixo*/
                mapa[n + 1][m] = mapa_2[n + 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_2[n][m] = ' ';
                    turnos_visao = 40;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 30; i++) {
                        for(j = 0; j < 30; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i >= 0 && m + j >= 0) {
                            if((n + i >= 0 && m + j >= 0) && (n + i <= 29 && m + j <= 29)) {
                                mapa[n + i][m + j] = mapa_2[n + i][m + j];
                            }
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n - limite >= 0 && m + i >= 0) {
                        mapa[n - limite][m + i] = mapa_copia[n - limite][m + i];
                    }
                }
            }
        }

        /*Conferir se caiu na cura ou no potencializador*/
        if(mapa[n][m] == 'H') {
            mapa_2[n][m] = ' ';
            vida += 20;
        }
        
        if(mapa[n][m] == 'P') {
            mapa_2[n][m] = ' ';
            turnos_potencializacao = 40;
            atributo_principal = atributo_principal_potencializado;
        }
        
        turnos_potencializacao -= 1;
        if(turnos_potencializacao == 0) {
            atributo_principal = atributo_principal_temp;
        }

        /*Conferir se alguma armadilha entrou na visão do jogador*/
        float perceber_armadilha_float;

        float destreza_float = (float)destreza;
        float inteligencia_float = (float)inteligencia;

        if(profissao == 3) {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 12) * 100);
        }
        else {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 20) * 100);
        }

        int perceber_armadilha = (int)perceber_armadilha_float;

        int num_aleatorio_perceber_armadilha;

        srand(time(NULL));
        num_aleatorio_perceber_armadilha = rand() % 101;

        for(contador = 0; contador <= 9; contador++) {
            for(i = -visao; i <= visao; i++) {
                for(j = -visao; j <= visao; j++) {
                    if(n + i == axmed[contador] && m + j == aymed[contador]) {
                        if(teste_med[contador] == 0) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_2[axmed[contador]][aymed[contador]] != '-') {
                                    mapa_2[axmed[contador]][aymed[contador]] = 'A';
                                    mapa[axmed[contador]][aymed[contador]] = 'A';
                                }
                            }
                            teste_med[contador] = 1;
                        }
                    }
                }
            }
        }

        /*Teste forçado pela tecla 't'*/
        if(movimento == 't') {
            for(contador = 0; contador <= 9; contador++) {
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i == axmed[contador] && m + j == aymed[contador]) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_2[axmed[contador]][aymed[contador]] != '-') {
                                    mapa_2[axmed[contador]][aymed[contador]] = 'A';
                                    mapa[axmed[contador]][aymed[contador]] = 'A';
                                }
                            }
                        }
                    }
                }
            }
            vida -= 1;
        }      

        /* Atacar os monstros */
        if(movimento == 'b' || movimento == 'B') {
            if(profissao == 2) {                /* Se for mago */
                for(contador = 0; contador < 10; contador++) {
                    for(i = -2; i <= 2; i++) {
                        for(j = -2; j <= 2; j++) {
                            if(n + i == mxmed[contador] && m + j == mymed[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_2[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
            else {                              /* Se for de outra profissao */
                for(contador = 0; contador < 10; contador++) {
                    for(i = -1; i <= 1; i++) {
                        for(j = -1; j <= 1; j++) {
                            if(n + i == mxmed[contador] && m + j == mymed[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_2[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
        }  

        for(contador = 0; contador <= 9; contador++) {
            if(n == axmed[contador] && m == aymed[contador]) {
                if(mapa_2[n][m] != '-') {
                    vida -= 5;
                    mapa_2[n][m] = '-';
                }
            }
        }

        /*Ataque do monstro*/
        for(contador = 0; contador < 10; contador++) {
            for(i = -1; i <= 1; i++) {
                for(j = -1; i <= 1; i++) {
                    if(mxmed[contador] + i == n && mymed[contador] + j == m) {
                        if(mapa_2[mxmed[contador]][mymed[contador]] == 'M') {
                            if(ataque_monstro - forca + acrescimos > 0) {
                                vida -= (ataque_monstro - forca + acrescimos);
                            }
                            else {
                                vida -= 0;
                            }
                        }  
                    }
                }
            }
        }

        /*Colocar o personagem no meio da visão*/
        mapa[n][m] = personagem;

        /*Impressão do mapa*/
        for (i = 0; i < 30; i++) {
            for (j = 0; j < 30; j++) {
                printf("%c", mapa[i][j]);
                if(mapa[i][j] == '#') {
                    printf("#");
                }
                else if(mapa[i][j] == ' ') {
                    printf(" ");
                }
                else if(mapa[i][j] == '?') {
                    printf("?");
                }
                else if(mapa[i][j] == 'O') {
                    printf("O");
                }
                else if(mapa[i][j] == 'H') {
                    printf("p");
                }
                else if(mapa[i][j] == 'P') {
                    printf("o");
                }
                else if(mapa[i][j] == 'V') {
                    printf("i");
                }
                else if(mapa[i][j] == 'C') {
                    printf("h");
                }
                else if(mapa[i][j] == 'A') {
                    printf("r");
                }
                else if(mapa[i][j] == '-') {
                    printf("-");
                }
                else if(mapa[i][j] == 'M') {
                    printf("o");
                }
            }
            if(i == 0) {
                printf("                    Vida: %d", vida);
            }
            if(i == 1) {
                printf("                    Profissao: %s", profissao_escrito);
            }
            if(i == 2) {
                printf("                    Alinhamento: %s", alinhamento_escrito);
            }
            if(i == 3) {
                printf("                    Atributo principal: %s", atributo_principal_escrito);
            }
            if(i == 4) {
                printf("                    Forca: %d", forca);
            }
            if(i == 5) {
                printf("                    Inteligencia: %d", inteligencia);
            }
            if(i == 6) {
                printf("                    Destreza: %d", destreza);
            }
            if(i == 7) {
                printf("                    Constituicao: %d", constituicao);
            }
            if(i == 9) {
                printf("                    Nome: %s", nome);
            }
            putchar('\n');
        }

        if(mapa_2[n][m] == '-') {
            /*Criar texto para quando cair na armadilha*/
            printf("\nCaiu na armadilha\n");
        }

        if(mapa_2[n][m] == 'H') {
            /*Criar texto para quando cair em poção de cura*/
            printf("\nVoce encontrou um cookie da Johns e o comeu, recuperando 20 de vida\n");
        }

        if(mapa_2[n][m] == 'V') {
            /*Criar texto para quando cair em poção de visão além do alcance*/
            printf("\nVoce encontrou uma bateria muito forte para sua lanterna e aumentou a potencia dela por um tempo\n");
        }

        if(mapa_2[n][m] == 'P') {
            /*Criar texto para quando cair em poção de potencializador de atributo principal*/
            printf("\nVoce encontrou um redbull que aumentou seu atributo principal\n");
        }

        if(mapa_2[n][m] == 'C') {
            ir_para_boss = 1;
            printf("\n\nVoce encontrou o Nilson com as chaves do seu Peugeot 206...\n\n");
            getchar();
        }
        
        if(vida <= 0) {
            printf("\nVoce perdeu e nao achou sua chave do Peugeot 206");
            getchar();        
        }
    }

    if(ir_para_boss == 1) {
        system ("clear");
        
        /*Realizar boss fight*/
        jokenpo(alinhamento, nome, &vida);       /*Jokenpô*/

        if(vida > 0) {
            charada(vida);
        }
    }   
}

void jogo_dificil(int escolha_mapa, const char* nome, int vida, int atributo_principal, int forca, int constituicao, int destreza, int inteligencia, int profissao, int alinhamento, const char* atributo_principal_escrito, const char* profissao_escrito, const char* alinhamento_escrito)
{
    int i, j;
    char personagem = 'O';
    int ataque_monstro = 10, defesa_monstro = 2;
    int vida_monstro[20] = {6};
    int acrescimos = 0;
    char mapa_3[50][51];

    /*Definir o mapa do jogo*/
    mapas_dificeis(mapa_3, escolha_mapa);

    /*MAPA BLOQUEADO*/
    char mapa[50][50];
    for(i = 0; i < 50; i++) {
        for(j = 0; j < 50; j++) {
            mapa[i][j] = '?';
        }
    }

    /*MAPA BLOQUEADO CÓPIA*/
    char mapa_copia[50][50];
    for(i = 0; i < 50; i++) {
        for(j = 0; j < 50; j++) {
            mapa_copia[i][j] = '?';
        }
    }

    int continuar_ate_break = 0;
    int contador;

    /*Preparar as armadilhas*/
    /*Posição: armadilha 1*/
    int axdif[20];
    int aydif[20];

    for(contador = 0; contador <= 19; contador ++) {
        while(continuar_ate_break == 0) {
            axdif[contador] = rand() % 45;
            aydif[contador] = rand() % 45;
            if(mapa_3[axdif[contador] + 5][aydif[contador] + 5] == ' ') {
                axdif[contador] += 5;
                aydif[contador] += 5;
                break;
            }
        }
    }

    /*Variáveis para permitir que a armadilha possa ser percebida automaticamente apenas uma vez*/
    int teste_dif[20] = {0};

    /*Criando a visão do jogador para imprimir o mapa*/
    char movimento;
    int n = 1;
    int m = 1;

    for(i = -2; i <= 2; i++) {
        for(j = -2; j <= 2; j++) {
            if(n + i >= 0 && m + j >= 0) {
                mapa[n + i][m + j] = mapa_3[n + i][m + j];
            }
            if(i == 0 && j == 0) {
                mapa[n + i][m + j] = personagem;
            }
        }
    }

    int mxdif[20];
    int mydif[20];

    srand(time(NULL));
    int x_monstro = 0, y_monstro = 0;

    for(contador = 0; contador < 20; contador++) {
        while(mapa_3[x_monstro][y_monstro] != ' ') {
            x_monstro = (rand() % 39) + 11;
            y_monstro = (rand() % 39) + 11;
            mxdif[contador] = x_monstro;
            mydif[contador] = y_monstro;
        }
        mapa_3[mxdif[contador]][mydif[contador]] = 'M';
    }

    for (i = 0; i < 50; i++) {
        for (j = 0; j < 50; j++) {
            printf("%c", mapa[i][j]);
            if(mapa[i][j] == '#') {
                printf("#");
            }
            else if(mapa[i][j] == ' ') {
                printf(" ");
            }
            else if(mapa[i][j] == '?') {
                printf("?");
            }
            else if(mapa[i][j] == 'O') {
                printf("O");
            }
        }
        if(i == 0) {
            printf("                    Vida: %d", vida);
        }
        if(i == 1) {
            printf("                    Profissao: %s", profissao_escrito);
        }
        if(i == 2) {
            printf("                    Alinhamento: %s", alinhamento_escrito);
        }
        if(i == 3) {
            printf("                    Atributo principal: %s", atributo_principal_escrito);
        }
        if(i == 4) {
            printf("                    Forca: %d", forca);
        }
        if(i == 5) {
            printf("                    Inteligencia: %d", inteligencia);
        }
        if(i == 6) {
            printf("                    Destreza: %d", destreza);
        }
        if(i == 7) {
            printf("                    Constituicao: %d", constituicao);
        }
        if(i == 9) {
            printf("                    Nome: %s", nome);
        }
        putchar('\n');
    }

    int turnos_potencializacao; /*variável que vai guardar a quantidade de turnos que algo vai acontecer*/
    int turnos_visao;
    int atributo_principal_potencializado = 2 * atributo_principal;
    int atributo_principal_temp = atributo_principal;
    int visao = 2;
    int limite = 3;

    int ir_para_boss = 0;

    /*MOVIMENTAÇÃO SER INFINITA ATÉ O JOGO ACABAR*/
    while(vida > 0 && ir_para_boss == 0) {
        /*scanf(" %c", &movimento); */
        movimento = le_tecla();
        system("clear");
        
        if(mapa_3[n][m + 1] != '#' && mapa_3[n][m + 1] != 'M') {
            if(movimento == 'd' || movimento == 'D') {          /*Movimentação para a direita*/
                mapa[n][m + 1] = mapa_3[n][m + 1];
                mapa[n][m] = mapa_copia[n][m];
                m++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_3[n][m] = ' ';
                    turnos_visao = 50;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 50; i++) {
                        for(j = 0; j < 50; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 49 && m + j <= 49)) {
                            mapa[n + i][m + j] = mapa_3[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m - limite >= 0) {
                        mapa[n + i][m - limite] = mapa_copia[n + i][m - limite];
                    }
                }
            }
        }

        if(mapa_3[n][m - 1] != '#' && mapa_3[n][m - 1] != 'M') {
            if(movimento == 'a' || movimento == 'A') {          /*Movimentação para a esquerda*/
                mapa[n][m - 1] = mapa_3[n][m - 1];
                mapa[n][m] = mapa_copia[n][m];
                m--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_3[n][m] = ' ';
                    turnos_visao = 50;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 50; i++) {
                        for(j = 0; j < 50; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 49 && m + j <= 49)) {
                            mapa[n + i][m + j] = mapa_3[n + i][m + j];
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + i >= 0 && m + limite >= 0) {
                        mapa[n + i][m + limite] = mapa_copia[n + i][m + limite];
                    }
                }
            }
        }

        if(mapa_3[n - 1][m] != '#' && mapa_3[n - 1][m] != 'M') {
            if(movimento == 'w' || movimento == 'W') {          /*Movimentação se for para cima*/
                mapa[n - 1][m] = mapa_3[n - 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n--;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_3[n][m] = ' ';
                    turnos_visao = 50;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 50; i++) {
                        for(j = 0; j < 50; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if((n + i >= 0 && m + j >= 0) && (n + i <= 49 && m + j <= 49)) {
                            mapa[n + i][m + j] = mapa_3[n + i][m + j];
                        }
                    }   
                }
                for(i = -visao; i <= visao; i++) {
                    if(n + limite >= 0 && m + i >= 0) {
                        mapa[n + limite][m + i] = mapa_copia[n + limite][m + i];
                    }
                }
            }
        }

        if(mapa_3[n + 1][m] != '#' && mapa_3[n + 1][m] != 'M') {
            if(movimento == 's' || movimento == 'S') {          /*Movimentação se for para baixo*/
                mapa[n + 1][m] = mapa_3[n + 1][m];
                mapa[n][m] = mapa_copia[n][m];
                n++;

                /*Conferir se caiu na visao além do alcance*/
                if(mapa[n][m] == 'V') {
                    mapa_3[n][m] = ' ';
                    turnos_visao = 50;
                    visao = 4;
                    limite = 5;   
                }
                turnos_visao -= 1;
                if(turnos_visao == 0) {
                    visao = 2;
                    limite = 3;
                    for(i = 0; i < 50; i++) {
                        for(j = 0; j < 50; j++) {
                            mapa[i][j] = '?';
                        }
                    }
                }

                /*Mover a visão do jogador*/
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i >= 0 && m + j >= 0) {
                            if((n + i >= 0 && m + j >= 0) && (n + i <= 49 && m + j <= 49)) {
                                mapa[n + i][m + j] = mapa_3[n + i][m + j];
                            }
                        }
                    }
                }
                for(i = -visao; i <= visao; i++) {
                    if(n - limite >= 0 && m + i >= 0) {
                        mapa[n - limite][m + i] = mapa_copia[n - limite][m + i];
                    }
                }
            }
        }

        /*Conferir se caiu na cura ou no potencializador*/
        if(mapa[n][m] == 'H') {
            mapa_3[n][m] = ' ';
            vida += 20;
        }
        
        if(mapa[n][m] == 'P') {
            mapa_3[n][m] = ' ';
            turnos_potencializacao = 50;
            atributo_principal = atributo_principal_potencializado;
        }
        
        turnos_potencializacao -= 1;
        if(turnos_potencializacao == 0) {
            atributo_principal = atributo_principal_temp;
        }

        /*Conferir se alguma armadilha entrou na visão do jogador*/
        float perceber_armadilha_float;

        float destreza_float = (float)destreza;
        float inteligencia_float = (float)inteligencia;

        if(profissao == 3) {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 12) * 100);
        }
        else {
            perceber_armadilha_float = (((destreza_float + inteligencia_float) / 20) * 100);
        }

        int perceber_armadilha = (int)perceber_armadilha_float;

        int num_aleatorio_perceber_armadilha;

        srand(time(NULL));
        num_aleatorio_perceber_armadilha = rand() % 101;

        for(contador = 0; contador <= 19; contador++) {
            for(i = -visao; i <= visao; i++) {
                for(j = -visao; j <= visao; j++) {
                    if(n + i == axdif[contador] && m + j == aydif[contador]) {
                        if(teste_dif[contador] == 0) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_3[axdif[contador]][aydif[contador]] != '-') {
                                    mapa_3[axdif[contador]][aydif[contador]] = 'A';
                                    mapa[axdif[contador]][aydif[contador]] = 'A';
                                }
                            }
                            teste_dif[contador] = 1;
                        }
                    }
                }
            }
        }

        /*Teste forçado pela tecla 't'*/
        if(movimento == 't') {
            for(contador = 0; contador <= 19; contador++) {
                for(i = -visao; i <= visao; i++) {
                    for(j = -visao; j <= visao; j++) {
                        if(n + i == axdif[contador] && m + j == aydif[contador]) {
                            if(num_aleatorio_perceber_armadilha <= perceber_armadilha) {
                                if(mapa_3[axdif[contador]][aydif[contador]] != '-') {
                                    mapa_3[axdif[contador]][aydif[contador]] = 'A';
                                    mapa[axdif[contador]][aydif[contador]] = 'A';
                                }
                            }
                        }
                    }
                }
            }
            vida -= 1;
        }      

        /* Atacar os monstros */
        if(movimento == 'b' || movimento == 'B') {
            if(profissao == 2) {                /* Se for mago */
                for(contador = 0; contador < 20; contador++) {
                    for(i = -2; i <= 2; i++) {
                        for(j = -2; j <= 2; j++) {
                            if(n + i == mxdif[contador] && m + j == mydif[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_3[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
            else {                              /* Se for de outra profissao */
                for(contador = 0; contador < 20; contador++) {
                    for(i = -1; i <= 1; i++) {
                        for(j = -1; j <= 1; j++) {
                            if(n + i == mxdif[contador] && m + j == mydif[contador]) {
                                vida_monstro[contador] -= (1 + atributo_principal - defesa_monstro + acrescimos);
                                if(vida_monstro[contador] <= 0) {
                                    mapa_3[n + i][m + j] = ' ';
                                    mapa[n + i][m + j] = ' ';
                                }
                            }
                        }
                    }
                }
            }
        }   

        /* Dano que a armadilha dá */
        for(contador = 0; contador <= 19; contador++) {
            if(n == axdif[contador] && m == aydif[contador]) {
                if(mapa_3[n][m] != '-') {
                    vida -= 5;
                    mapa_3[n][m] = '-';
                }
            }
        }

        /*Ataque do monstro*/
        for(contador = 0; contador < 20; contador++) {
            for(i = -1; i <= 1; i++) {
                for(j = -1; i <= 1; i++) {
                    if(mxdif[contador] + i == n && mydif[contador] + j == m) {
                        if(mapa_3[mxdif[contador]][mydif[contador]] == 'M') {
                            if(ataque_monstro - forca + acrescimos > 0) {
                                vida -= (ataque_monstro - forca + acrescimos);
                            }
                            else {
                                vida -= 0;
                            }
                        }  
                    }
                }
            }
        }

        /*Colocar o personagem no meio da visão*/
        mapa[n][m] = personagem;

        /*Impressão do mapa*/
        for (i = 0; i < 50; i++) {
            for (j = 0; j < 50; j++) {
                printf("%c", mapa[i][j]);
                if(mapa[i][j] == '#') {
                    printf("#");
                }
                else if(mapa[i][j] == ' ') {
                    printf(" ");
                }
                else if(mapa[i][j] == '?') {
                    printf("?");
                }
                else if(mapa[i][j] == 'O') {
                    printf("O");
                }
                else if(mapa[i][j] == 'H') {
                    printf("p");
                }
                else if(mapa[i][j] == 'P') {
                    printf("o");
                }
                else if(mapa[i][j] == 'V') {
                    printf("i");
                }
                else if(mapa[i][j] == 'C') {
                    printf("h");
                }
                else if(mapa[i][j] == 'A') {
                    printf("r");
                }
                else if(mapa[i][j] == '-') {
                    printf("-");
                }
                else if(mapa[i][j] == 'M') {
                    printf("o");
                }
            }
            if(i == 0) {
                printf("                    Vida: %d", vida);
            }
            if(i == 1) {
                printf("                    Profissao: %s", profissao_escrito);
            }
            if(i == 2) {
                printf("                    Alinhamento: %s", alinhamento_escrito);
            }
            if(i == 3) {
                printf("                    Atributo principal: %s", atributo_principal_escrito);
            }
            if(i == 4) {
                printf("                    Forca: %d", forca);
            }
            if(i == 5) {
                printf("                    Inteligencia: %d", inteligencia);
            }
            if(i == 6) {
                printf("                    Destreza: %d", destreza);
            }
            if(i == 7) {
                printf("                    Constituicao: %d", constituicao);
            }
            if(i == 9) {
                printf("                    Nome: %s", nome);
            }
            putchar('\n');
        }

        if(mapa_3[n][m] == '-') {
            /*Criar texto para quando cair na armadilha*/
            printf("\nCaiu na armadilha\n");
        }

        if(mapa_3[n][m] == 'H') {
            /*Criar texto para quando cair em poção de cura*/
            printf("\nVoce encontrou um cookie da Johns e o comeu, recuperando 20 de vida\n");
        }

        if(mapa_3[n][m] == 'V') {
            /*Criar texto para quando cair em poção de visão além do alcance*/
            printf("\nVoce encontrou uma bateria muito forte para sua lanterna e aumentou a potencia dela por um tempo\n");
        }

        if(mapa_3[n][m] == 'P') {
            /*Criar texto para quando cair em poção de potencializador de atributo principal*/
            printf("\nVoce encontrou um redbull que aumentou seu atributo principal\n");
        }

        if(mapa_3[n][m] == 'C') {
            ir_para_boss = 1;
            printf("\n\nVoce encontrou o Nilson com as chaves do seu Peugeot 206...\n\n");
            getchar();
        }

        if(vida <= 0) {
            printf("\nVoce perdeu e nao achou sua chave do Peugeot 206");
            getchar();        
        }
    }

    if(ir_para_boss == 1) {
        system ("clear");

        /*Realizar boss fight*/
        jokenpo(alinhamento, nome, &vida);       /*Jokenpô*/

        if(vida > 0) {
            charada(vida);
        }
    }   
}

void jokenpo(int alinhamento, const char* nome, int *vida) {
    /* JOKENPÔ */
    /* Texto para quando encontrar o boss */
    printf("rsrsrsrsrsrs voce nunca saira dessa faculdade se voce nao ganhar de mim em uma partida de JOKENPO\n");
    getchar();
    
    int vida_p = *vida;
    
    srand(time(NULL));

    int npc;                    	/*A JOGADA DO COMPUTADOR*/
    int jogada;                     /* A SUA JOGADA EM FORMA DE INT */
    int ok_jogou;                   /*CONFIRMAÇÃO DE SE VOCÊ DIGITOU UM NÚMERO VÁLIDO*/
    char oponente[10];			/*SE O OPONENTE É HERÓI OU VILÃO*/
    char voce[10];				/*O QUE VOCÊ VAI JOGAR*/
    int vitoria = 0;			/*MARCADOR DE VITÓRIAS*/
    int jokenpo_ok = 0;			/*COMPLETOU O JOKENPÔ*/
    int game_over;

    if(alinhamento == 1) {		/* SALVAR O NOME DO OPONENTE COMO HERÓI SE VOCÊ FOR MAL E VILÃO SE VOCÊ FOR BOM OU NEUTRO */
        strcpy(oponente, "Heroi");
    }
    else {
        strcpy(oponente, "Vilao");
    }

    printf("\n========================\n");
    printf("***BATALHA_DE_JOKENPÔ***\n");
    printf("========================\n");

    /* LOOP PARA O JOKENPÔ ENQUANTO A VIDA FOR MAIOR QUE 0 E NÃO TIVER GANHADO AINDA */

    while(vitoria < 3 && vida_p > 0) {

        ok_jogou = 0;
        while(ok_jogou == 0) {		/* LOOP PARA CASO A PESSOA DIGITE UMA OPÇÃO DIFERENTE DAS PERMITIDAS */
            printf("\nVocê escolhe:\n\n");
            printf("1. TESOURA\n2. PEDRA\n3. PAPEL\n\n");
            scanf("%d", &jogada);
            if(jogada == 1) {
                strcpy(voce, "TESOURA!");
                ok_jogou = 1;
            }
            else if(jogada == 2) {
                strcpy(voce, "PEDRA!");
                ok_jogou = 1;
            }
            else if(jogada == 3) {
                strcpy(voce, "PAPEL!");
                ok_jogou = 1;
            }
            else {
                printf("Escolha uma opção válida\n");
            }
        }

        npc = rand() % 3;

        if(ok_jogou == 1 && npc == 0) {
            printf("%s: TESOURA!\n", oponente);
            printf("%s: %s\n\n", nome, voce);
            if(jogada == 1) {
                printf("Empate!\nDenovo!\n\n");
                printf("Vida: %d\n", vida_p);
            }
            else if(jogada == 2) {
                vitoria += 1;
                if(vitoria < 2) {
                    printf("Você ganhou!\nDenovo!\n\n");
                    printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você ganhou!\n\n");
                    printf("Vida: %d\n", vida_p);
                    jokenpo_ok = 1;
                }
            }
            else if(jogada == 3) {
                vida_p -= 10;
                if(vida_p > 0) {
                    printf("Você perdeu!\nDenovo!\n\n");
                    printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você perdeu!\n\n");
                    printf("Vida: 00\n");
                    game_over = 1;
                }
            }
        }

        else if(ok_jogou == 1 && npc == 1) {
            printf("%s: PEDRA!\n", oponente);
            printf("%s: %s\n\n", nome, voce);
            if(jogada == 2){
                printf("Empate!\nDenovo!\n\n");
                printf("Vida: %d\n", vida_p);
            }
            else if(jogada == 3) {
                vitoria += 1;
                if(vitoria < 2) {
                printf("Você ganhou!\nDenovo!\n\n");
                printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você ganhou!\n\n");
                    printf("Vida: %d\n", vida_p);
                            jokenpo_ok = 1;
                }
            }
            else if(jogada == 1) {
                vida_p -= 10;
                if(vida_p > 0) {
                    printf("Você perdeu!\nDenovo!\n\n");
                    printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você perdeu!\n\n");
                    printf("Vida: 00\n");
                    game_over = 1;
                }
            }
        }
        else if(ok_jogou == 1 && npc == 2) {
            printf("%s: PAPEL!\n", oponente);
            printf("%s: %s\n\n", nome, voce);
            if(jogada == 3) {
                printf("Empate!\nDenovo!\n\n");
                printf("Vida: %d\n", vida_p);
            }
            else if(jogada == 1) {
                vitoria += 1;
                if(vitoria < 2) {
                printf("Você ganhou!\nDenovo!\n\n");
                printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você ganhou!\n\n");
                    printf("Vida: %d\n", vida_p);
                    jokenpo_ok = 1;
                }
            }
            else if(jogada == 2){
                vida_p -= 10;
                if(vida_p > 0) {
                    printf("Você perdeu!\nDenovo!\n\n");
                    printf("Vida: %d\n", vida_p);
                }
                else {
                    printf("Você perdeu!\n\n");
                    printf("Vida: 00\n");
                    game_over = 1;
                }
            }
        }
        printf("=======================\n");
    }

    if(jokenpo_ok == 1) {				            /*SE VOCÊ GANHOU O JOKENPÔ*/
        printf("Você ganhou!\n\n");
    }
    else if(jokenpo_ok != 1 && game_over == 1) {	/*SE VOCÊ PERDEU NO  JOKENPÔ ATÉ MORRER*/
        printf("Você perdeu!\n\n");
    }

    *vida = vida_p;
}

void charada(int vida) {
    /*VARIÁVEIS PARA A CHARADA*/

    system("clear");

    printf("rsrsrsrsrs Voce achou mesmo que seria tao facil? rsrsrs Agora voce deve acertar 3 charadas que eu vou te passar!\n\n");
    getchar();
    getchar();

    printf("==================\n");
    printf("*****CHARADAS*****\n");
    printf("==================\n");

    char charada[10][300];		/*AS CHARADAS EM VETORES*/
    int i_temp[10] = {10};			/*O NÚMERO DAS CHARADAS QUE JÁ FORAM ESCOLHIDAS PARA NÃO REPETIR*/
    int incremento = 0;		/*PARA SALVAR AS CHARADAS QUE JÁ FORAM EM ÍNDICES DIFERENTES DE i_temp*/
    int resposta;			/*A RESPOSTA QUE VOCÊ VAI DAR PARA A CHARADA*/
    int prosseguir;			/*SE VOCÊ ESCOLHEU UMA RESPOSTA VÁLIDA*/
    int vitoria_2 = 0;		/*A QUANTIDADE DE CHARADAS QUE VOCÊ VAI ACERTOU*/
    int i;				/*VARIÁVEL QUE VAI SERVIR PARA ESCOLHER ALEATÓRIAMENTE A CHARADA*/

    /*AS CHARADAS EM FORMA DE CHAR*/

    strcpy(charada[0], "O que é, o que é?\nPode ser atirado do alto de um prédio e ficar super bem. Mas quando é colocado na água morre pouco tempo depois.\n\n1. gato\n2. papel\n3. chuteira");
    strcpy(charada[1], "O que é, o que é?\nSobe, sobe, sobe e jamais desce.\n\n1. elevador\n2. altura\n3. idade");
    strcpy(charada[2], "O que é, o que é?\nQuanto mais disso há, menos você vê.\n\n1. figurinha\n2. luz\n3. escuridão");
    strcpy(charada[3], "O que é, o que é?\nEstá sempre a caminho, mas nunca chega.\n\n1. amanhã\n2. fim\n3. sol");
    strcpy(charada[4], "O que é, o que é?\nPertence a você, mas as outras pessoas usam mais do que você.\n\n1. seu nome\n2. cérebro\n3. celular");
    strcpy(charada[5], "O que é, o que é?\nNão é vivo, mas cresce. Não tem pulmões, mas precisa de ar. Não tem boca, mas a água pode matá-lo.\n\n1. papel\n2. pedra\n3. fogo");
    strcpy(charada[6], "O que é, o que é?\nTem 6 faces, mas não usa maquiagem. Tem também 21 olhos, mas não pode ver.\n\n1. hidra\n2. dado\n3. polvo");
    strcpy(charada[7], "O que é, o que é?\nFaz duas pessoas a partir de uma só.\n\n1. espelho\n2. reprodução\n3. eco-eco");
    strcpy(charada[8], "O que é, o que é?\nQuanto mais você tira, maior eu fico.\n\n1. fome\n2. buraco\n3. cabelo");
    strcpy(charada[9], "O que é, o que é?\nNão tem pés, mãos ou asas, mas pode subir aos céus.\n\n1. fumaça\n2. mosquito\n3. skate");

    /*O JOGO DA CHARADA*/
    
    while(vida > 0 && vitoria_2 < 3) {
        i = rand() % 10;
        if(i != i_temp[0] && i != i_temp[1] && i != i_temp[2] && i != i_temp[3] && i != i_temp[4] && i != i_temp[5] && i != i_temp[6] && i != i_temp[7] && i != i_temp[8] && i != i_temp[9]) {		/*PARA NÃO ESCOLHER AS CHARADAS QUE JÁ FORAM*/
            prosseguir = 0;
            printf("\n\n%s\n", charada[i]);
            printf("\nA resposta é: ");

            while(prosseguir == 0) {		/*REPETIR ENQUANTO A RESPOSTA NÃO FOR UM NÚMERO VÁLIDO*/
                scanf("%d", &resposta);
                i_temp[incremento] = i;
                incremento++;

                if(resposta == 1 || resposta == 2 || resposta == 3) {
                    prosseguir = 1;
                }
                else{
                    printf("Escolha uma opção válida\n");
                }
            }

/*REPOSTAS DAS CHARADAS*/

            if(i == 0) {
                if(resposta == 1 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 1) {
                if(resposta == 1 || resposta == 2) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 2) {
                if(resposta == 1 || resposta == 2) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 3) {
                if(resposta == 2 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 4) {
                if(resposta == 2 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 5) {
                if(resposta == 1 || resposta == 2) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 6) {
                if(resposta == 1 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 7) {
                if(resposta == 2 || resposta == 3){
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else{
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 8) {
                if(resposta == 1 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else {
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            else if(i == 9) {
                if(resposta == 2 || resposta == 3) {
                    printf("Você errou!\n");
                    vida -= 50;
                }
                else{
                    printf("Você acertou!\n");
                    vitoria_2 += 1;
                }
            }
            if(vida > 0) {
                printf("Vida: %d\n\n", vida);
            }
            else {
                printf("Vida: 00\n\n");
            }
        }
        printf("===================================\n\n");
    }

    if(vida > 0) {		/*SE VENCEU O JOGO*/
        printf("\n\nVoce conseguiu acertar todas charadas do Nilson...");
        getchar();
        getchar();
        printf("Nilson fica impressionado com sua inteligencia e te entrega a chave.\n");
        printf("Voce pega a chave do seu Peugeot 206 e vai embora da faculdade!\nVoce ganhou");
        getchar();
        getchar();
    }
    else {			/*SE PERDEU O JOGO*/
        printf("\n\nNilson percebe que voce nao eh inteligente e nao te da a chave e te deixa de recuperacao!\nVoce perdeu!\n");
        getchar();
        getchar();
    }
}