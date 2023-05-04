#ifndef ___STATE_H___
#define ___STATE_H___

typedef struct mapa {
	char caracterAtual;
	char caracterAnterior;
	int acessivel;
	int dist; //valor da distancia ao jogador
	int ilum; //1 se iluminado, 0 se não iluminado
} MAPA;

typedef struct state {
	int playerX;
	int playerY;
	int nROWS;
	int nCOLS;
	int monsterX;
	int monsterY;
	struct mapa map[60][250];
} STATE;

typedef struct monsters {
     int monsterX;
	 int monsterY;
} MONSTER;

#endif
