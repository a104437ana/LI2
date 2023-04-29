#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

int raio (STATE *st, int x, int y, int r) {
	int n = 0;
	signed int rX, rY;
	if (r>=0) {
		for (rX = r; rX >= - r ; rX--) {
			for (rY = r; rY >= - r ; rY--) {
				if (st->map[x+rX][y+rY].caracterAnterior == '#') n++;
			}
		}
	}
	return n;
}

void first_map (STATE *st) {
	int x, y;
	x = 0;
	y = 0;
	for (;x<st->nROWS;x++) {
		st->map[x][y].caracterAtual = '#';
	}
	x = st->nROWS - 1;
	for (;y<st->nCOLS;y++) {
		st->map[x][y].caracterAtual = '#';
	}
	y = st->nCOLS - 1;
	for (;x>=0;x--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 0;
	for (;y>0;y--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 1;
	y = 1;
	for (;x<st->nROWS-1;x++) {
		st->map[x][y].caracterAtual = '#';
	}
	x = st->nROWS - 2;
	for (;y<st->nCOLS-1;y++) {
		st->map[x][y].caracterAtual = '#';
	}
	y = st->nCOLS - 2;
	for (;x>=1;x--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 1;
	for (;y>1;y--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 2;
	for (;x<st->nROWS - 2;x++) {
		y = 2;
		for (;y<st->nCOLS - 2;y++) {
			if (drand48() < 0.34) {
				st->map[x][y].caracterAtual = '#';
			}
			else {
				st->map[x][y].caracterAtual = '.';
			}
		}
	}
}

void first_alg (STATE *st) {
	int x, y;
	for (x=0;x<st->nROWS;x++) {
		for (y=0;y<st->nCOLS;y++) {
			st->map[x][y].caracterAnterior = st->map[x][y].caracterAtual;
		}
	}
	x = 2;
	for (;x<st->nROWS - 2;x++) {
		y = 2;
		for (;y<st->nCOLS - 2;y++) {
			if (raio(st,x,y,1)>=5) {
				st->map[x][y].caracterAtual = '#';
			}
			else {
				if (raio(st,x,y,2)==0) {
				    st->map[x][y].caracterAtual = '#';
				}
				else {
				    st->map[x][y].caracterAtual = '.';
				}
			}
		}
	}
}

void second_alg (STATE *st) {
	int x, y;
	for (x=0;x<st->nROWS;x++) {
		for (y=0;y<st->nCOLS;y++) {
			st->map[x][y].caracterAnterior = st->map[x][y].caracterAtual;
		}
	}
	x = 2;
	for (;x<st->nROWS - 2;x++) {
		y = 2;
		for (;y<st->nCOLS - 2;y++) {
			if (raio(st,x,y,1)>=5) {
				st->map[x][y].caracterAtual = '#';
			}
			else {
				st->map[x][y].caracterAtual = '.';
			}
		}
	}
}

void flood_fill (STATE *st, int x, int y) {
	signed int rX, rY;
	for (rX = 1; rX >= - 1 ; rX--) {
			for (rY = 1; rY >= - 1 ; rY--) {
				if (st->map[x+rX][y+rY].acessivel==0 && x+rX>=0 && y+rY>=0 && x+rX<st->nROWS && y+rY<st->nCOLS) {
						st->map[x+rX][y+rY].acessivel = 1;
						flood_fill (st,x+rX,y+rY);
				}
			}
		}
}

void gerar(STATE *st) {
	int i;
	st->playerX = 10;
	st->playerY = 10;
	first_map(st);
	for (i=1;i<=4;i++) {
		first_alg(st);
	}
	for (i=1;i<=3;i++) {
		second_alg(st);
	}
	while (raio(st,st->playerX,st->playerY,1) != 0) {
		st->playerX = lrand48() % st->nROWS;
	    st->playerY = lrand48() % st->nCOLS;
	}
	for (int x = 0; x < st->nROWS; x++) {
		for (int y = 0; y < st->nCOLS ; y++) {
			if (st->map[x][y].caracterAtual == '#') st->map[x][y].acessivel = 2;
			else st->map[x][y].acessivel = 0;
		}
	}
	st->map[st->playerX][st->playerY].acessivel = 1;
	flood_fill(st,st->playerX,st->playerY);
	for (int x = 0; x < st->nROWS; x++) {
		for (int y = 0; y < st->nCOLS ; y++) {
			if (st->map[x][y].acessivel == 0) {
				st->map[x][y].acessivel = 2;
				st->map[x][y].caracterAtual = '#';
			}
		}
	}
}

