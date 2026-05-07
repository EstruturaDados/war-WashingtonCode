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

