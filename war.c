// =====================================================================
// Prática> Desafio Jogo War - Nível aventureiro
// Objetivo: Implementar ataque, alocação dinâmica e manipulação por ponteiros.
//=====================================================================

// Bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct para representar um território
typedef struct {
    char nome[30];
    char corExercito[10];
    int qtdTropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int totalTerritorios;
    int optAtacante, optDefensor;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- Bem-vindo ao WAR Estruturado ---\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    getchar(); // Limpa o buffer do teclado

    // Alocação Dinâmica usando calloc
    Territorio* mapa = (Territorio*)calloc(totalTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, totalTerritorios);

    int jogando = 1;
    while (jogando) {
        exibirMapa(mapa, totalTerritorios);

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o numero do territorio ATACANTE (1 a %d) ou 0 para sair: ", totalTerritorios);
        scanf("%d", &optAtacante);

        if (optAtacante == 0) break;

        printf("Escolha o numero do territorio DEFENSOR (1 a %d): ", totalTerritorios);
        scanf("%d", &optDefensor);

        // Validações de entrada
        if (optAtacante < 1 || optAtacante > totalTerritorios || optDefensor < 1 || optDefensor > totalTerritorios) {
            printf("\n[Erro] Territorios invalidos!\n");
            continue;
        }

        if (optAtacante == optDefensor) {
            printf("\n[Erro] Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }

        // Executa o ataque passando os endereços via ponteiros
        atacar(&mapa[optAtacante - 1], &mapa[optDefensor - 1]);
    }

    // Liberação da memória antes de fechar o programa
    liberarMemoria(mapa);
    
    printf("\nPrograma encerrado. Memoria liberada.\n");
    return 0;
}

// Cadastro utilizando aritmética de ponteiros
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome do territorio: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = 0; // Remove o \n

        printf("Cor do Exercito: ");
        fgets((mapa + i)->corExercito, 10, stdin);
        (mapa + i)->corExercito[strcspn((mapa + i)->corExercito, "\n")] = 0;

        printf("Quantidade de Tropas: ");
        scanf("%d", &(mapa + i)->qtdTropas);
        getchar(); // Limpa buffer
    }
}
