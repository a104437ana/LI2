#ifndef ___STATE_H___
#define ___STATE_H___

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
	int durabilidade;
	int equipada; // 1 se o jogador pegou na arma, 0 se está no chão;
} ARMA;

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int acessivel;
	int dist;
	int ilum;
	int acessado;
} MAPA;

typedef struct state {
	int acontecimento;
	int nivel;
	int seed[8][2];
	struct coordenadas jogo;
	struct coordenadas escada;
	struct coordenadas sala[50];
	struct jogador jogador;
	struct monstro monstro[8];
	struct arma arma[4];
	struct mapa map[60][250];
} STATE;

#endif
