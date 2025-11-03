#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTDE_TERRITORIOS 5

typedef struct {
    char nome[50];
    char corExercito[20];
    int tropas;
} Territorio;

void simularBatalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n⚠️ O território %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n🎲 Dados sorteados:\n");
    printf("%s (Ataque): %d\n", atacante->nome, dadoAtaque);
    printf("%s (Defesa): %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--;
        printf("\n🔥 %s venceu o ataque!\n", atacante->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            printf("🏴‍☠️ %s conquistou o território %s!\n", atacante->nome, defensor->nome);
            strcpy(defensor->corExercito, atacante->corExercito);
        }
    } else {
        atacante->tropas--;
        printf("\n🛡️ %s defendeu com sucesso!\n", defensor->nome);
    }

    printf("\n--- Estado Atual ---\n");
    printf("%s -> Tropas: %d\n", atacante->nome, atacante->tropas);
    printf("%s -> Tropas: %d\n", defensor->nome, defensor->tropas);
}

int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio *) calloc(QTDE_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== Cadastro Inicial dos Territórios ===\n\n");
    for (int i = 0; i < QTDE_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // consome o \n
        printf("\n");
    }

    int opcao;
    do {
        printf("\n=== Fase de Ataque ===\n");
        printf("Escolha o território atacante (1-%d): ", QTDE_TERRITORIOS);
        int a, d;
        scanf("%d", &a);
        printf("Escolha o território defensor (1-%d): ", QTDE_TERRITORIOS);
        scanf("%d", &d);
        getchar();

        if (a < 1 || a > QTDE_TERRITORIOS || d < 1 || d > QTDE_TERRITORIOS || a == d) {
            printf("\n⚠️ Escolha inválida. Tente novamente.\n");
            continue;
        }

        simularBatalha(&mapa[a - 1], &mapa[d - 1]);

        printf("\nDeseja continuar atacando? (1 - Sim | 0 - Não): ");
        scanf("%d", &opcao);
        getchar();

    } while (opcao != 0);

    printf("\n=== Estado Final do Mapa ===\n");
    for (int i = 0; i < QTDE_TERRITORIOS; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }

    free(mapa);
    return 0;
}
