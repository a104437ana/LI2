#ifndef ___STATE_H___
#define ___STATE_H___

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int dist;
	int ilum;
} MAPA;

typedef struct state {
	int playerX;
	int playerY;
	int nROWS;
	int nCOLS;
	struct mapa map[60][250];
} STATE;

#endif
