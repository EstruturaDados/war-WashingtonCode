// =====================================================================
// Prática> Desafio Jogo War - Nível Mestre
// Objetivo: Implementar a funcionalidade de missões estratégicas individuais para cada jogador, que deverá receber, no início do jogo, uma missão sorteada de forma automática entre diversas descrições pré-definidas, armazenadas em um vetor de strings. Essa missão será consultada durante o jogo para verificar se a condição de vitória foi atingida. A nova camada de estratégia exige organização modular do código, uso de ponteiros, passagem de parâmetros por valor e referência e gerenciamento adequado da memória.
//=====================================================================

// Bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do Território
typedef struct {
    char nome[30];
    char corExercito[10];
    int qtdTropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* descMissao, int* idMissao, int totalT, Territorio* mapa, char* corAlvo, char* corJogador);
int verificarMissao(int idMissao, char* minhaCor, char* corAlvo, Territorio* mapa, int totalT);
void liberarMemoria(Territorio* mapa, char* missao);

// Função principal
int main() {
    int totalTerritorios, idMissao;
    int optAtacante, optDefensor;
    char corJogador[10], corAlvo[10] = "";

    srand(time(NULL));

    printf("--- WAR ESTRUTURADO (NIVEL MESTRE) ---\n");

    // Validação da quantidade mínima de territórios para evitar erro no Fallback
    do {
        printf("Quantos territorios deseja cadastrar? (Minimo 3): ");
        if (scanf("%d", &totalTerritorios) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar(); 
        if (totalTerritorios < 3) printf("[Erro] O mapa precisa de pelo menos 3 territorios para as missoes!\n");
    } while (totalTerritorios < 3);

    printf("Qual a cor do seu exercito? ");
    fgets(corJogador, 10, stdin);
    corJogador[strcspn(corJogador, "\n")] = 0;

    Territorio* mapa = (Territorio*)calloc(totalTerritorios, sizeof(Territorio));
    char* missaoTexto = (char*)malloc(150 * sizeof(char));

    if (!mapa || !missaoTexto) return 1;

    cadastrarTerritorios(mapa, totalTerritorios);
    atribuirMissao(missaoTexto, &idMissao, totalTerritorios, mapa, corAlvo, corJogador);

    printf("\n==========================================\n");
    printf("SUA MISSAO: %s\n", missaoTexto);
    printf("==========================================\n");

    while (1) {
        exibirMapa(mapa, totalTerritorios);
        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Atacante (1-%d) ou 0 para Sair: ", totalTerritorios);
        scanf("%d", &optAtacante);
        if (optAtacante == 0) break;

        printf("Defensor (1-%d): ", totalTerritorios);
        scanf("%d", &optDefensor);

        if (optAtacante < 1 || optAtacante > totalTerritorios || optDefensor < 1 || optDefensor > totalTerritorios) {
            printf("[Erro] Alvo invalido!\n");
            continue;
        }
        if (strcmp(mapa[optAtacante-1].corExercito, mapa[optDefensor-1].corExercito) == 0) {
            printf("[Erro] Nao pode atacar aliados!\n");
            continue;
        }

        atacar(&mapa[optAtacante-1], &mapa[optDefensor-1]);

        if (verificarMissao(idMissao, corJogador, corAlvo, mapa, totalTerritorios)) {
            exibirMapa(mapa, totalTerritorios);
            printf("\n******************************************\n");
            printf("VITORIA! Missao Cumprida:\n%s\n", missaoTexto);
            printf("******************************************\n");
            break;
        }
    }

    liberarMemoria(mapa, missaoTexto);
    return 0;
}

// --- Implementação das funções ---
// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->qtdTropas <= 1) {
        printf("[Aviso] Tropas insuficientes para atacar! (Minimo 2)\n");
        return;
    }

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    // Exibição dos valores dos dados
    printf("\n--- RESULTADO DOS DADOS ---\n");
    printf("DADO ATACANTE: [%d]\n", dadoA);
    printf("DADO DEFENSOR: [%d]\n", dadoD);
    printf("---------------------------\n");

    if (dadoA > dadoD) {
        printf("O Atacante venceu a rodada!\n");
        defensor->qtdTropas--;
    } else {
        printf("A Defesa venceu a rodada (ou empate)!\n");
        atacante->qtdTropas--;
    }

    if (defensor->qtdTropas <= 0) {
        printf("!!! TERRITORIO %s CONQUISTADO !!!\n", defensor->nome);
        strcpy(defensor->corExercito, atacante->corExercito);
        defensor->qtdTropas = 1;
        atacante->qtdTropas--;
    }
}

// Função de atribuição de missão
void atribuirMissao(char* descMissao, int* idMissao, int totalT, Territorio* mapa, char* corAlvo, char* corJogador) {
    int tentativas = 0, alvoIdx;
    do {
        *idMissao = rand() % 5; 
        alvoIdx = *idMissao;
        tentativas++;
    } while (totalT > alvoIdx && strcmp(mapa[alvoIdx].corExercito, corJogador) == 0 && tentativas < 10);

    if (totalT > alvoIdx) {
        strcpy(corAlvo, mapa[alvoIdx].corExercito);
        sprintf(descMissao, "Eliminar o exercito da cor %s (iniciado no Territorio %d).", corAlvo, alvoIdx + 1);
    } else {
        *idMissao = 99;
        strcpy(descMissao, "OBJETIVO: Conquistar 3 territorios quaisquer.");
    }
}

// Função de verificação de missão
int verificarMissao(int idMissao, char* minhaCor, char* corAlvo, Territorio* mapa, int totalT) {
    int meusTerritorios = 0, corAlvoAindaExiste = 0;
    for (int i = 0; i < totalT; i++) {
        if (strcmp(mapa[i].corExercito, minhaCor) == 0) meusTerritorios++;
        if (corAlvo[0] != '\0' && strcmp(mapa[i].corExercito, corAlvo) == 0) corAlvoAindaExiste = 1;
    }
    if (idMissao == 99) return (meusTerritorios >= 3);
    return !corAlvoAindaExiste; 
}

// Função de cadastro dos territórios
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d - Nome: ", i + 1);
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;
        printf("Cor do exercito: ");
        fgets(mapa[i].corExercito, 10, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;
        printf("Qtd Tropas: ");
        scanf("%d", &mapa[i].qtdTropas);
        getchar();
    }
}

// Função de exibição do mapa
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n========= STATUS DO MAPA =========\n");
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %-12s | Cor: %-8s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].corExercito, mapa[i].qtdTropas);
    }
    printf("==================================\n");
}