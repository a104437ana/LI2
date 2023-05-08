#ifndef ___STATE_H___
#define ___STATE_H___

typedef struct coordenadas {
	int X;
	int Y;
} COORD;

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int acessivel;
	int dist;
	int ilum; //1 se iluminado, 0 se não iluminado
} MAPA;

typedef struct state {
	int erro;
	int paredes;
	struct coordenadas jogo;
	struct coordenadas jogador;
	struct coordenadas escada;
	struct coordenadas sala[50];
	struct coordenadas monstro[10];
	struct mapa map[60][250];
} STATE;

#endif
