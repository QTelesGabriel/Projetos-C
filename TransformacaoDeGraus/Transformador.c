#include <stdio.h>
#include <stdlib.h>

void cel_far();
void cel_kel();
void far_cel();
void far_kel();
void kel_cel();
void kel_far();

int main() {

    int opcao;

    do {

        system("clear");

        printf("***TRANSFORMADOR DE MEDIDA***\n\n");
        printf("1. Celsius --> Fahrenheit\n");
        printf("2. Celsius --> Kelvin\n");
        printf("3. Fahrenheit --> Celsius\n");
        printf("4. Fahrenheit --> Kelvin\n");
        printf("5. Kelvin --> Celsius\n");
        printf("6. Kelvin --> Fahrenheit\n");
        printf("0. Sair\n\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("clear");
                cel_far();
                break;
            case 2:
                system("clear");
                cel_kel();
                break;
            case 3:
                system("clear");
                far_cel();
                break;
            case 4:
                system("clear");
                far_kel();
                break;
            case 5:
                system("clear");
                kel_cel();
                break;
            case 6:
                system("clear");
                kel_far();
                break;
            case 0:
                printf("\n\nSaindo...\n");
                break;
            default:
                printf("Escolha uma opcao valida...\n");
                getchar();
                break;

        }

    } while (opcao != 0);

    return 0;
}

void cel_far() {
    float medida_cel;
    float medida_far;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_cel);
    printf("\n\n");
    
    medida_far = (medida_cel * 1.8) + 32;

    printf("%.2f graus celsius em graus fahrenheit = %.2f\n\n", medida_cel, medida_far);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}

void cel_kel() {
    float medida_cel;
    float medida_kel;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_cel);
    printf("\n\n");

    medida_kel = medida_cel + 273.15;

    printf("%.2f graus celsius em kelvin = %.2f\n\n", medida_cel, medida_kel);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}

void far_cel() {
    float medida_cel;
    float medida_far;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_far);
    printf("\n\n");

    medida_cel = (medida_far - 32) / 1.8;

    printf("%.2f graus fahrenheit em graus celsius = %.2f\n\n", medida_far, medida_cel);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}

void far_kel() {
    float medida_kel;
    float medida_far;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_far);
    printf("\n\n");

    medida_kel = ((medida_far - 32) / (9 / 5)) + 273.15;

    printf("%.2f graus fahrenheit em kelvin = %.2f\n\n", medida_far, medida_kel);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}

void kel_cel() {
    float medida_cel;
    float medida_kel;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_kel);
    printf("\n\n");

    medida_cel = medida_kel - 273.15;

    printf("%.2f kelvin em graus celsius = %.2f\n\n", medida_kel, medida_cel);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}
void kel_far() {
    float medida_kel;
    float medida_far;
    printf("Digite o valor a ser transformado: ");
    scanf("%f", &medida_kel);
    printf("\n\n");

    medida_far = (medida_kel - 273.15) * (9 / 5) + 32;

    printf("%.2f kelvin em graus fahrenheit = %.2f\n\n", medida_kel, medida_far);

    printf("Aperte enter para voltar ao menu...");
    getchar();
    getchar();
}