#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "mapa.h"

void escada (STATE *st) {
	st->escada.X = lrand48() % st->jogo.X;
	st->escada.Y = lrand48() % st->jogo.Y;
	while (st->map[st->escada.X][st->escada.Y].acessivel != 1) {
		st->escada.X = lrand48() % st->jogo.X;
	    st->escada.Y = lrand48() % st->jogo.Y;
    }
}

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
	for (;x<st->jogo.X;x++) {
		st->map[x][y].caracterAtual = '#';
	}
	x = st->jogo.X - 1;
	for (;y<st->jogo.Y;y++) {
		st->map[x][y].caracterAtual = '#';
	}
	y = st->jogo.Y - 1;
	for (;x>=0;x--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 0;
	for (;y>0;y--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 1;
	y = 1;
	for (;x<st->jogo.X-1;x++) {
		st->map[x][y].caracterAtual = '#';
	}
	x = st->jogo.X - 2;
	for (;y<st->jogo.Y-1;y++) {
		st->map[x][y].caracterAtual = '#';
	}
	y = st->jogo.Y - 2;
	for (;x>=1;x--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 1;
	for (;y>1;y--) {
		st->map[x][y].caracterAtual = '#';
	}
	x = 2;
	for (;x<st->jogo.X - 2;x++) {
		y = 2;
		for (;y<st->jogo.Y - 2;y++) {
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
	for (x=0;x<st->jogo.X;x++) {
		for (y=0;y<st->jogo.Y;y++) {
			st->map[x][y].caracterAnterior = st->map[x][y].caracterAtual;
		}
	}
	x = 2;
	for (;x<st->jogo.X - 2;x++) {
		y = 2;
		for (;y<st->jogo.Y - 2;y++) {
			if (raio(st,x,y,1)>=5) {
				st->map[x][y].caracterAtual = '#';
			}
			else {
				if (raio(st,x,y,2)<=2) {
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
	for (x=0;x<st->jogo.X;x++) {
		for (y=0;y<st->jogo.Y;y++) {
			st->map[x][y].caracterAnterior = st->map[x][y].caracterAtual;
		}
	}
	x = 2;
	for (;x<st->jogo.X - 2;x++) {
		y = 2;
		for (;y<st->jogo.Y - 2;y++) {
			if (raio(st,x,y,1)>=5) {
				st->map[x][y].caracterAtual = '#';
			}
			else {
				st->map[x][y].caracterAtual = '.';
			}
		}
	}
}

void flood_fill_alg (STATE *st, int x, int y, int valor,int valori) {
	signed int rX, rY;
	for (rX = 1; rX >= - 1 ; rX--) {
			for (rY = 1; rY >= - 1 ; rY--) {
				if (st->map[x+rX][y+rY].acessivel==valori && x+rX>=0 && y+rY>=0 && x+rX<st->jogo.X && y+rY<st->jogo.Y) {
						st->map[x+rX][y+rY].acessivel = valor;
						flood_fill_alg (st,x+rX,y+rY,valor,valori);
				}
			}
		}
}

void gerar(STATE *st) {
	int i,j,x,y;
	st->jogador.X = lrand48() % st->jogo.X;
	st->jogador.Y = lrand48() % st->jogo.Y;
	first_map(st);
	for (i=1;i<=5;i++) {
		first_alg(st);
	}
	for (i=1;i<=15;i++) {
		second_alg(st);
	}
	while (st->map[st->jogador.X][st->jogador.Y].caracterAtual != '.') {
		st->jogador.X = lrand48() % st->jogo.X;
	    st->jogador.Y = lrand48() % st->jogo.Y;
	}
	for (x = 0; x < st->jogo.X; x++) {
		for (y = 0; y < st->jogo.Y ; y++) {
			if (st->map[x][y].caracterAtual == '#') st->map[x][y].acessivel = -1;
			else st->map[x][y].acessivel = 0;
		}
	}
	
	i = 1;
	for (x = 0; x < st->jogo.X; x++) {
		for (y = 0; y < st->jogo.Y ; y++) {
			if (st->map[x][y].acessivel == 0) {
				st->sala[i-1].X = x;
				st->sala[i-1].Y = y;
				st->map[x][y].acessivel = i;
				flood_fill_alg(st,x,y,i,0);
				i++;
			}
		}
	}

	j = 1;
	while (j<i) {
		x = st->sala[j].X;
		y = st->sala[j].Y - 1;
		for (;y>2 && st->map[x][y].acessivel != 1;y--) {
		}
		if (y>2) {
			st->map[x][y].caracterAtual = '+';
			y++;
			st->map[x][y].caracterAtual = '+';
			y++;
			for (;y<st->jogo.Y - 2 && st->map[x][y].acessivel != j+1; y++) {
				st->map[x][y].caracterAtual = '+';
			}
			while (y<st->jogo.Y - 2 && st->map[x][y].caracterAtual != '#') {
				st->map[x][y].caracterAtual = '+';
				y++;
			}
			y--;
			st->map[x][y].caracterAtual = '+';
			flood_fill_alg(st,x,y,1,j+1);
		}
		else {
		x = st->sala[j].X;
		y = st->sala[j].Y + 1;
		for (;y<st->jogo.Y - 2 && st->map[x][y].acessivel != 1;y++) {
		}
		if (y<st->jogo.Y - 2) {
			st->map[x][y].caracterAtual = '+';
			y--;
			st->map[x][y].caracterAtual = '+';
			y--;
			for (;y<st->jogo.Y - 2 && st->map[x][y].acessivel != j+1; y--) {
				st->map[x][y].caracterAtual = '+';
			}
			while (y<st->jogo.Y - 2 && st->map[x][y].caracterAtual != '#') {
				st->map[x][y].caracterAtual = '+';
				y--;
			}
			y++;
			st->map[x][y].caracterAtual = '+';
			flood_fill_alg(st,x,y,1,j+1);
		}
		}
		j++;
	}

    while (st->map[st->jogador.X][st->jogador.Y].acessivel != 1) {
		st->jogador.X = lrand48() % st->jogo.X;
	    st->jogador.Y = lrand48() % st->jogo.Y;
	}
	st->map[st->jogador.X][st->jogador.Y].acessivel = 1;
	
	escada(st);
	st->map[st->escada.X][st->escada.Y].acessivel = 1;
	st->map[st->escada.X][st->escada.Y].caracterAtual = '>';
	st->map[st->jogador.X][st->jogador.Y].caracterAtual = '>';

	for (x = 0; x < st->jogo.X; x++) {
		for (y = 0; y < st->jogo.Y ; y++) {
			if (st->map[x][y].caracterAtual == '#') {(st->paredes)++; st->map[x][y].acessivel = -1;}
			if (st->map[x][y].caracterAtual == '+') st->map[x][y].acessivel = 1;
			if (st->map[x][y].acessivel == 0 || st->map[x][y].acessivel > 1) st->erro = 1;
		}
	}
}

