#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
printf("\n\n    	       T~~                                     \n");
printf("               |                                           \n");
printf("              / \\                                         \n");
printf("      T~~     |'| T~~                                      \n");
printf("  T~~ |    T~ WWWW|                                        \n");
printf("  |  / \\   |  |  |/\\T~~                                  \n");
printf(" / \\ WWW  / \\ |' |WW|                                    \n");
printf("WWWWW/\\| /   \\|'/\\|/ \\			BEM-VINDO,             \n");
printf("|   /__\\/]WWW[\\/__\\WWWW          AO JOGO DA ADIVINHACAO!\n");
printf("|   WWWW'|I_I|'WWWW'  |                                    \n");
printf("|   |' |/  -  \\|' |'  | 								   \n");
printf("|'  |  |LI=H=LI|' |   |							           \n");
printf("|   |' | |[_]| |  |'  |									   \n");
printf("|   |  |_|###|_|  |   |									   \n");
printf("'---'--'-/___\\-'--'---'							   \n\n\n");

	int numero_de_tentativas;
	int dificuldade;
	printf("Escolha o nível de dificuldade\n1) Facil\n2) Medio\n3) Dificil\n4) ASIATICO\n->");
	while (dificuldade < 1 || dificuldade > 4) {
		scanf("%d", &dificuldade);
		if (dificuldade < 1 || dificuldade > 4) printf("Escolha um nivel valido\n->");
	}

	switch (dificuldade) {
		case 1:
			numero_de_tentativas = 100;
			break;
		case 2:
			numero_de_tentativas = 10;
			break;
		case 3:
			numero_de_tentativas = 5;
			break;
		case 4:
			numero_de_tentativas = 1;
			break;
	}
	
	srand(time(NULL));	// A função time() puxa o numero de segundos desde 1 de janeiro de 1970 (Data chamada de EPOCH)
						// E a função srand "planta esse número na função"

	int numerosecreto = rand() % 100;	// A função rand gera um número completamente aleatório (gigante ou não). 
										// Então para limitar o número é calculado o resto da divisão (nesse caso da divisão por 100)
										// Dessa forma, o resultado será um número de 0 a 99
										// Se eu quisesse de 0 a 1000 era só fazer rand() % 1001
	float pontos = 1000;
    int chute;
	int tentativas = 0;
	int acertou;

    while(1) {
		
		tentativas++;
        printf("\nTentativa %d\n", tentativas);
        printf("Qual é o seu chute?\n->");

        scanf("%d", &chute);
        printf("Seu chute foi %d\n", chute);

        if(chute < 0) {
            printf("Você não pode chutar números negativos\n");
            continue;
        }

		acertou = chute == numerosecreto;
		int maior = chute > numerosecreto;

		if(acertou) {
			break;
		}

		else if(maior) {
            printf("Seu chute foi maior que o número secreto\n");
        }
		else {
			printf("Seu chute foi menor que o número secreto\n");
		}

		pontos -= abs(chute - numerosecreto) / 2.0;

		if (tentativas == numero_de_tentativas) {
			break;
		}
	}
	
	if(acertou) {	
		printf("\nParabéns! Você acertou!\n");
		printf("Jogue de novo, você é um bom jogador!\n");
		printf("Acertou em %d tentativas\n", tentativas);
	}
	else {
		printf("\nVocê é uma decepcao!\nBAKA!\n");
		pontos = 0.0;
	}

	printf("Pontuaçao: %.1f\n", pontos);

	return 0;
}