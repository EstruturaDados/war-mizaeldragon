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

typedef struct {
    char descricao[100];
    int tipo;
    int conquistados;
} Missao;

// === FUNÇÕES ===
void inicializarMapa(Territorio *mapa, const int qtd);
void exibirMapa(const Territorio *mapa, const int qtd);
void simularBatalha(Territorio *atacante, Territorio *defensor);
void atribuirMissao(Missao *m);
void verificarMissao(Missao *m, Territorio *mapa, const int qtd);
int menuPrincipal();

// === FUNÇÃO PRINCIPAL ===
int main() {
    srand(time(NULL));

    Territorio *mapa = (Territorio *) calloc(QTDE_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    Missao missao;
    inicializarMapa(mapa, QTDE_TERRITORIOS);
    atribuirMissao(&missao);

    int opcao;
    do {
        opcao = menuPrincipal();
        switch (opcao) {
            case 1: {
                exibirMapa(mapa, QTDE_TERRITORIOS);
                int a, d;
                printf("Escolha o território atacante (1-%d): ", QTDE_TERRITORIOS);
                scanf("%d", &a);
                printf("Escolha o território defensor (1-%d): ", QTDE_TERRITORIOS);
                scanf("%d", &d);
                getchar();

                if (a < 1 || a > QTDE_TERRITORIOS || d < 1 || d > QTDE_TERRITORIOS || a == d) {
                    printf("\n⚠️ Escolha inválida.\n");
                    break;
                }

                simularBatalha(&mapa[a - 1], &mapa[d - 1]);
                verificarMissao(&missao, mapa, QTDE_TERRITORIOS);
                break;
            }
            case 2:
                verificarMissao(&missao, mapa, QTDE_TERRITORIOS);
                break;
            case 0:
                printf("\n👋 Saindo do jogo... Até a próxima batalha!\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    free(mapa);
    return 0;
}

// === IMPLEMENTAÇÕES ===

void inicializarMapa(Territorio *mapa, const int qtd) {
    const char *nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};
    const int tropasIniciais[] = {10, 8, 12, 9, 7};

    for (int i = 0; i < qtd; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].tropas = tropasIniciais[i];
    }

    printf("🌍 Territórios inicializados automaticamente!\n");
}

void exibirMapa(const Territorio *mapa, const int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %-10s | Exército: %-8s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
    printf("-----------------------------\n");
}

void simularBatalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n⚠️ %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n🎲 Dados sorteados: %s(Ataque)=%d | %s(Defesa)=%d\n",
           atacante->nome, dadoA, defensor->nome, dadoD);

    if (dadoA >= dadoD) {
        defensor->tropas--;
        printf("🔥 %s venceu a batalha!\n", atacante->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->tropas = 1;
            atacante->tropas--;
            printf("🏴‍☠️ %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
        }
    } else {
        atacante->tropas--;
        printf("🛡️ %s defendeu com sucesso!\n", defensor->nome);
    }
}

void atribuirMissao(Missao *m) {
    int tipo = rand() % 2 + 1;
    m->tipo = tipo;
    m->conquistados = 0;

    if (tipo == 1)
        strcpy(m->descricao, "Destruir o exército Verde");
    else
        strcpy(m->descricao, "Conquistar 3 territórios");

    printf("\n🎯 Missão atribuída: %s\n", m->descricao);
}

void verificarMissao(Missao *m, Territorio *mapa, const int qtd) {
    if (m->tipo == 1) {
        int existeVerde = 0;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0 && mapa[i].tropas > 0)
                existeVerde = 1;
        }

        if (!existeVerde)
            printf("\n🏆 Missão cumprida! Você destruiu o exército Verde!\n");
        else
            printf("\n🚩 Ainda existem territórios Verdes no mapa.\n");

    } else if (m->tipo == 2) {
        int corPrincipal = 0;
        int contagem[QTDE_TERRITORIOS] = {0};
        for (int i = 0; i < qtd; i++) {
            for (int j = i + 1; j < qtd; j++) {
                if (strcmp(mapa[i].corExercito, mapa[j].corExercito) == 0)
                    contagem[i]++;
            }
            if (contagem[i] >= 2) corPrincipal = 1;
        }

        if (corPrincipal)
            printf("\n🏆 Missão cumprida! Você conquistou 3 territórios!\n");
        else
            printf("\n🚩 Ainda não conquistou 3 territórios do mesmo exército.\n");
    }
}

int menuPrincipal() {
    int opcao;
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}
