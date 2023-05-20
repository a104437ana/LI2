#ifndef ___STATE_H___
#define ___STATE_H___

#define LIGHT_STATE 0
#define MAX_DIST 10
#define MAX_ROW 60 // x
#define MAX_COL 250 // y
#define SHOW_DIST 0
#define MAX_VIDA_JOGADOR 100
#define MIN_VIDA_JOGADOR 0
#define MAX_VIDA_MONSTRO 100
#define MAX_DURAB_ARMA 100
#define NUM_MAX_POCOES 20
#define SMALL_POTION 20
#define LARGE_POTION 50
#define POISON -20
#define NUM_MAX_BOMBAS 5
#define EXPLOSAO -10

typedef struct coordenadas {
	int X;
	int Y;
} COORD;

typedef struct jogador {
	struct coordenadas coord;
	int vida;
	int arma_atual;
	int arma; // indice da arma que o jogador tem, -1 se não equipado;
	int corpo;
} JOGADOR;

typedef struct monstro {
	struct coordenadas coord;
	int vida;
} MONSTRO;

typedef struct arma {
	struct coordenadas coord;
	int equipada; // 1 se o jogador pegou na arma, 0 se está no chão;
} ARMA;

typedef struct pocao {
	struct coordenadas coord;
	int tipo;
	int gerada;
} POCAO;

typedef struct bomba {
	struct coordenadas coord;
	int gerada;
} BOMBA;

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int acessivel;
	int dist;
	int ilum;
	int acessado;
	int objeto;
} MAPA;

typedef struct state {
	int pocaoMax;
	int acontecimento;
	int nivel;
	int seed[8][2];
	struct coordenadas jogo;
	struct coordenadas escada;
	struct coordenadas sala[50];
	struct jogador jogador;
	struct monstro monstro[8];
	struct arma arma[10];
	struct pocao pocao[NUM_MAX_POCOES];
	struct bomba bomba [NUM_MAX_BOMBAS];
	struct mapa map[60][250];
} STATE;

#endif
