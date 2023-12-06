#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carro {
    char proprietario[50];
    char combustivel[10];
    char modelo[50];
    char cor[20];
    char chassis[20];
    int ano;
    char placa[8];
    struct Carro *proximo;
} Carro;

Carro* addCarro(Carro *head, char proprietario[], char combustivel[], char modelo[], char cor[], char chassis[], int ano, char placa[]) {
    Carro *carroNovo = (Carro*)malloc(sizeof(Carro));
    if (!carroNovo) {
        printf("Erro ao alocar a memoria para o novo carro.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(carroNovo->proprietario, proprietario);
    strcpy(carroNovo->combustivel, combustivel);
    strcpy(carroNovo->modelo, modelo);
    strcpy(carroNovo->cor, cor);
    strcpy(carroNovo->chassis, chassis);
    carroNovo->ano = ano;
    strcpy(carroNovo->placa, placa);
    carroNovo->proximo = head;
    return carroNovo;
}

void listDiesel2010OrLaterproprietarios(Carro *head) {
    Carro *current = head;
    printf("\nProprietarios de carros do ano de 2010 ou posterior movidos a diesel:\n");
    while (current != NULL) {
        if (current->ano >= 2010 && strcmp(current->combustivel, "diesel") == 0) {
            printf("%s\n", current->proprietario);
        }
        current = current->proximo;
    }
}

void listPlacasStartingWithJAndEndingWith0247(Carro *head) {
    Carro *current = head;
    printf("\nPlacas que comecam com a letra J e terminam com 0, 2, 4 ou 7, e seus proprietarios:\n");
    while (current != NULL) {
        if (current->placa[0] == 'J' && (current->placa[6] == '0' || current->placa[6] == '2' || current->placa[6] == '4' || current->placa[6] == '7')) {
            printf("Placa: %s, Proprietario: %s\n", current->placa, current->proprietario);
        }
        current = current->proximo;
    }
}

void listModeloAndCorForVowelSecondLetterAndEvenSum(Carro *head) {
    Carro *current = head;
    printf("\nModelo e cor dos veiculos com placas que tem como segunda letra uma vogal e a soma dos valores numericos eh par:\n");
    while (current != NULL) {
        if ((current->placa[1] == 'A' || current->placa[1] == 'E' || current->placa[1] == 'I' || current->placa[1] == 'O' || current->placa[1] == 'U') &&
            ((current->placa[2] - '0') + (current->placa[3] - '0') + (current->placa[4] - '0') + (current->placa[5] - '0') + (current->placa[6] - '0')) % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", current->modelo, current->cor);
        }
        current = current->proximo;
    }
}

void changeproprietarioByChassis(Carro *head, char chassis[], char newproprietario[]) {
    Carro *current = head;
    while (current != NULL) {
        if (strcmp(current->chassis, chassis) == 0 && strpbrk(current->placa, "0") == NULL) {
            strcpy(current->proprietario, newproprietario);
            printf("Proprietario do carro com chassi %s alterado para %s\n", chassis, newproprietario);
            return;
        }
        current = current->proximo;
    }
    printf("Carro nao encontrado ou possui digitos zero na placa.\n");
}

void freeList(Carro *head) {
    Carro *current = head;
    Carro *proximo;
    while (current != NULL) {
        proximo = current->proximo;
        free(current);
        current = proximo;
    }
}

int main() {
    Carro *head = NULL;
    int numCarros;

    printf("Quantos carros deseja cadastrar? ");
    scanf("%d", &numCarros);

    for (int i = 0; i < numCarros; ++i) {
        char proprietario[50], combustivel[10], modelo[50], cor[20], chassis[20], placa[8];
        int ano;

        printf("\ncarro %d:\n", i + 1);
        printf("Proprietario: ");
        scanf("%s", proprietario);
        fflush(stdin);
        printf("Combustivel (alcool, diesel, gasolina): ");
        scanf("%s", combustivel);
        fflush(stdin);
        printf("Modelo: ");
        scanf("%s", modelo);
        fflush(stdin);
        printf("Cor: ");
        scanf("%s", cor);
        fflush(stdin);
        printf("Chassi: ");
        scanf("%s", chassis);
        fflush(stdin);
        printf("Ano: ");
        scanf("%d", &ano);
        fflush(stdin);
        printf("Placa: ");
        scanf("%s", placa);
        fflush(stdin);

        head = addCarro(head, proprietario, combustivel, modelo, cor, chassis, ano, placa);
    }

    listDiesel2010OrLaterproprietarios(head);
    listPlacasStartingWithJAndEndingWith0247(head);
    listModeloAndCorForVowelSecondLetterAndEvenSum(head);

    char chassisToChange[20], newproprietario[50];
    printf("\nDigite o chassi do carro que tera o proprietario alterado: ");
    scanf("%s", chassisToChange);
    fflush(stdin);
    printf("Digite o novo proprietario: ");
    scanf("%s", newproprietario);
        fflush(stdin);
    changeproprietarioByChassis(head, chassisToChange, newproprietario);

    freeList(head);

    return 0;
}