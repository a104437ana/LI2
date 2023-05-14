#ifndef ___STATE_H___
#define ___STATE_H___

typedef struct coordenadas {
	int X;
	int Y;
} COORD;

typedef struct jogador {
	struct coordenadas coord;
	int vida;
} JOGADOR;

typedef struct monstro {
	struct coordenadas coord;
	int vida;
} MONSTRO;

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int acessivel;
	int dist;
	int ilum; //1 se iluminado, 0 se não iluminado
} MAPA;

typedef struct state {
	int paredes;
	struct coordenadas jogo;
	struct coordenadas escada;
	struct coordenadas sala[50];
	struct jogador jogador;
	struct monstro monstro[8];
	struct mapa map[60][250];
} STATE;

#endif
