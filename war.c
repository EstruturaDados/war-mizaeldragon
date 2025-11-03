#include <stdio.h>
#include <string.h>

#define QTDE_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[20];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[QTDE_TERRITORIOS];

    printf("=== Cadastro Inicial dos Territórios ===\n\n");

    for (int i = 0; i < QTDE_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("\n");
    }

    printf("\n=== Estado Atual do Mapa ===\n\n");
    for (int i = 0; i < QTDE_TERRITORIOS; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].corExercito);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
