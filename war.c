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
