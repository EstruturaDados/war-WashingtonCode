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