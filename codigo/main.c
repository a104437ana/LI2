#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>
#include "state.h"
#include "mapa.h"

#define MAX_DIST 10
#define MAX_ROW 60	// x
#define MAX_COL 250 // y
#define SHOW_DIST 0
#define SMALL_POTION 20
#define LARGE_POTION 50
#define POISON -20

void draw_monsterRato(STATE *st)
{
	for (int i = 0; i < 4; i++)
	{
	if(st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].ilum == 1 && st->monstro[i].vida > 0) 
	{
		attron(COLOR_PAIR(COLOR_MAGENTA));
		mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, 'r' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_MAGENTA));
	}
	if (st->monstro[i].vida <= 0) st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
	}
}

void draw_monsterDog(STATE *st)
{
	for (int i = 4; i < 6; i++)
	{
	if(st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].ilum == 1 && st->monstro[i].vida > 0) 
	{
		attron(COLOR_PAIR(COLOR_MAGENTA));
		mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, 'd' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_MAGENTA));
	}
	if (st->monstro[i].vida <= 0) st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
	}
}

void draw_monsterBat(STATE *st)
{
	for (int i = 6; i < 8; i++)
	{
	if(st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].ilum == 1 && st->monstro[i].vida > 0) 
	{
		attron(COLOR_PAIR(COLOR_MAGENTA));
		mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, 'b' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_MAGENTA));
	}
	if (st->monstro[i].vida <= 0) st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
	}
}

void draw_arma_faca (STATE *st)
{
	for (int i = 0; i < 2; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_YELLOW));
			mvaddch(st->arma[i].coord.X, st->arma[i].coord.Y, 'f' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_YELLOW));
		}
	}
}

void draw_arma_pistola (STATE *st)
{
	for (int i = 2; i < 4; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_YELLOW));
			mvaddch(st->arma[i].coord.X, st->arma[i].coord.Y, 'p' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_YELLOW));
		}
	}
}

void draw_pocao (STATE *st)
{
	int i;
	for (i = 0; i < NUM_MAX_POCOES; i++)
	{
		if (st->pocao[i].gerada && st->map[st->pocao[i].coord.X][st->pocao[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_GREEN));
			mvaddch(st->pocao[i].coord.X, st->pocao[i].coord.Y, '!' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_GREEN));
		}
	}
}

void draw_player(STATE *st)
{
	attron(COLOR_PAIR(COLOR_WHITE));
	mvaddch(st->jogador.coord.X, st->jogador.coord.Y, '@' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_WHITE));
}

void efeito_pocao (STATE *st)
{
	for (int i = 0; i < NUM_MAX_POCOES; i++)
	{
		if (st->pocao[i].gerada && st->map[st->pocao[i].coord.X][st->pocao[i].coord.Y].dist == 0)
		{
			switch (st->pocao[i].tipo)
			{
			case 0: // veneno
				st->jogador.vida += POISON;
				break;
			case 1: // poção "pequena" (comida)
				st->jogador.vida += SMALL_POTION;
				break;
			case 2: // poção "grande"
				st->jogador.vida += LARGE_POTION;
				break;
			}
		// destruir poção depois de usada
		st->pocao[i].gerada = 0;
		}
	}
	if (st->jogador.vida < MIN_VIDA_JOGADOR) st->jogador.vida = MIN_VIDA_JOGADOR;
	if (st->jogador.vida > MAX_VIDA_JOGADOR) st->jogador.vida = MAX_VIDA_JOGADOR;
	
}

void reset_dist(STATE *st)
{
	int i, j;

	for (i = 0; i < st->jogo.X; i++)
	{
		for (j = 0; j < st->jogo.Y; j++)
			st->map[i][j].dist = 300;
	}
}

 void calc_dist(int R, int C, int value, STATE *st)
{
	if (R < 0 || C < 0 || R >= st->jogo.X || C >= st->jogo.Y)
		return;
	if (value > MAX_DIST)
		return;
	if (st->map[R][C].dist != (-1) && st->map[R][C].dist <= value)
		return;
	if (st->map[R][C].caracterAtual == '#')
		return;

	st->map[R][C].dist = value;

	calc_dist(R + 1, C + 1, value + 1, st);
	calc_dist(R, C + 1, value + 1, st);
	calc_dist(R - 1, C + 1, value + 1, st);
	calc_dist(R - 1, C, value + 1, st);
	calc_dist(R - 1, C - 1, value + 1, st);
	calc_dist(R, C - 1, value + 1, st);
	calc_dist(R + 1, C - 1, value + 1, st);
	calc_dist(R + 1, C, value + 1, st);
}

void draw_info(STATE *st) {
	move(0, 0);
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | LIMITES MAXIMOS DO MAPA : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	printw("(%d,%d)", st->jogo.X, st->jogo.Y);
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | COORDENADAS : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	printw("(%d,%d)", st->jogador.coord.X, st->jogador.coord.Y);
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | NIVEL : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	printw("%d",st->nivel);
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | VIDA : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	printw("%d", st->jogador.vida);
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | ARMA ATUAL : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	if (st->jogador.arma_atual == -1) printw("corpo");
	else {
	if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual<2) printw("faca");
	else {
	if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual<2) printw("pistola");
	}
	}
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | ACONTECIMENTO : ");
	attroff(COLOR_PAIR(COLOR_GREEN));
	attron(COLOR_PAIR(COLOR_YELLOW));
	if (st->acontecimento == 0) printw("desceu as escadas");
	else {
	if (st->acontecimento == 1) printw("em andamento");
	else {
	if (st->acontecimento == 2) printw("pegou numa arma");
	else {
	if (st->acontecimento == 3) printw("largou uma arma");
	else {
	if (st->acontecimento == 4) printw("trocou a arma");
	else {
	if (st->acontecimento == 5) printw("foi atacado por um monstro");
	else {
	if (st->acontecimento == 6) printw("atacou um monstro e foi atacado por um monstro");
	}
	}
	}	
	}
	}
	}
	attroff(COLOR_PAIR(COLOR_YELLOW));
	attron(COLOR_PAIR(COLOR_GREEN));
	printw(" | ");
	attroff(COLOR_PAIR(COLOR_GREEN));
}
void do_movement_action(STATE *st, int dx, int dy)
{
	st->jogador.coord.X += dx;
	st->jogador.coord.Y += dy;
}

void movimento_monstros (STATE *st, int i)
{	
	if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist != 300)
	{
		// 8 acessível
		if (st->map[st->monstro[i].coord.X - 1][st->monstro[i].coord.Y].acessivel == 1 && 
			st->map[st->monstro[i].coord.X - 1][st->monstro[i].coord.Y].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X - 1;
			return;
		}

		// 2 acessível
		if (st->map[st->monstro[i].coord.X + 1][st->monstro[i].coord.Y].acessivel == 1 &&
			st->map[st->monstro[i].coord.X + 1][st->monstro[i].coord.Y].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X + 1;
			return;
		}

		// 4 acessível
		if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y - 1].acessivel == 1 &&
			st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y - 1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.Y = st->monstro[i].coord.Y - 1;
			return;
		}
		
		// 6 acessível
		if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y + 1].acessivel == 1 &&
			st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y + 1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.Y = st->monstro[i].coord.Y + 1;
			return;
		}
		
		// 3 acessível
		if (st->map[st->monstro[i].coord.X + 1][st->monstro[i].coord.Y + 1].acessivel == 1 &&
			st->map[st->monstro[i].coord.X + 1][st->monstro[i].coord.Y + 1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X+1;
			st->monstro[i].coord.Y = st->monstro[i].coord.Y+1;
			return;
		}
		
		// 7 acessível
		if (st->map[st->monstro[i].coord.X -1][st->monstro[i].coord.Y -1].acessivel == 1 &&
			st->map[st->monstro[i].coord.X -1][st->monstro[i].coord.Y -1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X-1;
			st->monstro[i].coord.Y = st->monstro[i].coord.Y-1;
			return;
		}
		
		// 9 acessível
		if (st->map[st->monstro[i].coord.X-1][st->monstro[i].coord.Y +1].acessivel == 1 && 
			st->map[st->monstro[i].coord.X-1][st->monstro[i].coord.Y +1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist)
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X -1;
			st->monstro[i].coord.Y=st->monstro[i].coord.Y+1;
			return;
		}
		
		// 1 acessível
		if (st->map[st->monstro[i].coord.X +1][st->monstro[i].coord.Y-1].acessivel == 1 &&
			st->map[st->monstro[i].coord.X +1][st->monstro[i].coord.Y-1].dist < st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist) 
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X+1;
			st->monstro[i].coord.Y = st->monstro[i].coord.Y-1;
			return;
		}
	}
	else {
		signed int x, y;
		x = 0;
		y = 0;
		if (st->seed[i][0] % 3 == 0) x = -1;
		if (st->seed[i][0] % 3 == 1) x = 0;
        if (st->seed[i][0] % 3 == 2) x = 1;
		if (st->seed[i][1] % 3 == 0) y = -1;
		if (st->seed[i][1] % 3 == 1) y = 0;
        if (st->seed[i][1] % 3 == 2) y = 1;
		if (st->map[st->monstro[i].coord.X + x][st->monstro[i].coord.Y + y].acessivel == 1) 
		{
			st->monstro[i].coord.X = st->monstro[i].coord.X + x;
			st->monstro[i].coord.Y = st->monstro[i].coord.Y + y;
		}
	}
}

void ataque (STATE *st) {
	st->jogador.vida = st->jogador.vida - 5;
}

void combate(STATE *st, int i)
{
	if (i>=0 && i<4 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual == 0 || st->jogador.arma_atual == 1) // faca
			{
				st->monstro[i].vida = st->monstro[i].vida - 50;
			}
			if (st->jogador.arma_atual == 2 || st->jogador.arma_atual == 3)
			{
				st->monstro[i].vida = st->monstro[i].vida - 50;
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida -10; // soco;
			}
	}
	if (i>=4 && i<6 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual == 0 || st->jogador.arma_atual == 1) // faca
			{
				st->monstro[i].vida = st->monstro[i].vida - 20;
			}
			if (st->jogador.arma_atual == 2 || st->jogador.arma_atual == 3)
			{
				st->monstro[i].vida = st->monstro[i].vida - 20;
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida -10; // soco;
			}
	}
	if (i>=6 && i<8 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual == 0 || st->jogador.arma_atual == 1) // faca
			{
				st->monstro[i].vida = st->monstro[i].vida - 50;
			}
			if (st->jogador.arma_atual == 2 || st->jogador.arma_atual == 3)
			{
				st->monstro[i].vida = st->monstro[i].vida - 50;
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida -10; // soco;
			}
	}
}

void get_arma (STATE *st)
{
	int i, stop;
	stop = 0;

	for (i = 0; !stop && i < 4; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].dist == 0)
		{
			st->acontecimento = 2;
			st->jogador.arma = i;
			st->jogador.arma_atual = i;
			st->arma[i].equipada = 1;
			stop = 1;
		}
	}
}

void put_arma (STATE *st)
{
	if (st->jogador.arma != -1) st->acontecimento = 3;
	st->arma[st->jogador.arma].equipada = 0;
	st->arma[st->jogador.arma].coord.X = st->jogador.coord.X;
	st->arma[st->jogador.arma].coord.Y = st->jogador.coord.Y;
	st->jogador.arma = -1;
	st->jogador.arma_atual = -1;
}

void troca (STATE *st) {
	if (st->jogador.arma_atual == -1) st->jogador.arma_atual = st->jogador.arma;
	else {
		st->jogador.arma_atual = -1;
	}
}

void update(STATE *st)
{
	st->acontecimento = 1;
	int key = getch();
	mvaddch(st->jogador.coord.X, st->jogador.coord.Y, '.');
	if (st->map[st->jogador.coord.X][st->jogador.coord.Y].caracterAtual == '>') st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
	else st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 1;
	switch (key) {
		case KEY_A1:
		case '7':
			if (st->map[st->jogador.coord.X - 1][st->jogador.coord.Y - 1].acessivel == 1)
			{
				do_movement_action(st, -1, -1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X - 1 == st->escada.X && st->jogador.coord.Y - 1== st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_UP:
		case '8':
			if (st->map[st->jogador.coord.X - 1][st->jogador.coord.Y].acessivel == 1)
			{
				do_movement_action(st, -1, +0);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X - 1 == st->escada.X && st->jogador.coord.Y == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_A3:
		case '9':
			if (st->map[st->jogador.coord.X - 1][st->jogador.coord.Y + 1].acessivel == 1)
			{
				do_movement_action(st, -1, +1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X - 1 == st->escada.X && st->jogador.coord.Y + 1 == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_LEFT:
		case '4':
			if (st->map[st->jogador.coord.X][st->jogador.coord.Y - 1].acessivel == 1)
			{
				do_movement_action(st, +0, -1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X == st->escada.X && st->jogador.coord.Y - 1 == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_B2:
		case '5':
			st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_RIGHT:
		case '6':
			if (st->map[st->jogador.coord.X][st->jogador.coord.Y + 1].acessivel == 1) 
			{
				do_movement_action(st, +0, +1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X == st->escada.X && st->jogador.coord.Y + 1 == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_C1:
		case '1':
			if (st->map[st->jogador.coord.X + 1][st->jogador.coord.Y - 1].acessivel == 1) 
			{
				do_movement_action(st, +1, -1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X + 1 == st->escada.X && st->jogador.coord.Y - 1 == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_DOWN:
		case '2':
			if (st->map[st->jogador.coord.X + 1][st->jogador.coord.Y].acessivel == 1)
			{
				do_movement_action(st, +1, +0);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X + 1 == st->escada.X && st->jogador.coord.Y == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
		case KEY_C3:
		case '3':
			if (st->map[st->jogador.coord.X + 1][st->jogador.coord.Y + 1].acessivel == 1)
			{
				do_movement_action(st, +1, +1);
				st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			}
			else {
				if (st->jogador.coord.X + 1 == st->escada.X && st->jogador.coord.Y + 1 == st->escada.Y) {
					gerar(st);
				}
				else {
					st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
				}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
			break;
	case 'X':
	case 'x':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y) && (st->monstro[i].coord.X) == st->jogador.coord.X + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'W':
	case 'w':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'A':
	case 'a':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.X == st->jogador.coord.X) && (st->monstro[i].coord.Y) == st->jogador.coord.Y - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'D':
	case 'd':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.X == st->jogador.coord.X) && (st->monstro[i].coord.X) == st->jogador.coord.X + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
		    }
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'Q':
	case 'q':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y - 1) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'E':
	case 'e':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y + 1) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'Z':
	case 'z':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.X == st->jogador.coord.X + 1) && (st->monstro[i].coord.Y) == st->jogador.coord.Y - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case 'C':
	case 'c':
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) &&
				((st->monstro[i].coord.X == st->jogador.coord.X + 1) && (st->monstro[i].coord.X) == st->jogador.coord.X + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
		    }
			}
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1) {ataque(st);if (st->acontecimento != 6) st->acontecimento = 5;}
				else {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
				}
			}
		    break;
	case '+':
			if (st->jogador.arma == -1) get_arma (st);
			else put_arma (st);
			efeito_pocao (st);
			break;
	case 'S':
	case 's':
			troca(st);
			st->acontecimento = 4;
			break;
	case 'L':
	case 'l':
			endwin();
			exit(0);
			break;
	}
}

void iluminacao(STATE *st)
{
	float angulo = 0;
	float xVetor;
	float yVetor;
	float x;
	float y;

	while (angulo >= 0 && angulo <= 360)
	{
		x = st->jogador.coord.X;
		y = st->jogador.coord.Y;
		// ordenada = (st->jogador.coord.X) - ((st->jogador.coord.Y) * tan(angulo));
		//  determinar o vetor diretor d areta
		xVetor = sin(angulo) - 0;
		yVetor = cos(angulo) - 0;

		while (1)
		{
			st->map[(int)(x)][(int)(y)].ilum = 1;
			st->map[(int)(x)][(int)(y)].acessado = 1;
			if (st->map[(int)(x)][(int)(y)].caracterAtual == '#') break;
			x = x + xVetor;
			y = y + yVetor;
		}

		angulo = angulo + 1;
	}
}
 
void draw_map(STATE *st)
{
	int x, y;
	for (x = 0; x < st->jogo.X; x++)
	{
		for (y = 0; y < st->jogo.Y; y++)
		{
			if (st->map[x][y].ilum == 0 && st->map[x][y].acessado == 0)
            {  
				attron(COLOR_PAIR(COLOR_BLUE));
				mvaddch(x, y, ' ' | A_BOLD);
				attroff(COLOR_PAIR(COLOR_BLUE));

			}
			else
			{
				if (st->map[x][y].ilum == 0 && st->map[x][y].acessado == 1) {
					attron(COLOR_PAIR(COLOR_BLUE));
				    mvaddch(x, y, st->map[x][y].caracterAtual | A_BOLD);
				    attroff(COLOR_PAIR(COLOR_BLUE));
				} else 
				{
				attron(COLOR_PAIR(COLOR_WHITE));
				mvaddch(x, y, st->map[x][y].caracterAtual | A_BOLD);
				attroff(COLOR_PAIR(COLOR_WHITE));
				}
			}
		}
	
	}

	if (SHOW_DIST)
	{
		for (x = 0; x < st->jogo.X; x++)
		{
			for (y = 0; y < st->jogo.Y; y++)
			{
				if (st->map[x][y].dist < 10)
				{
					attron(COLOR_PAIR(COLOR_MAGENTA));
					mvaddch(x, y, (st->map[x][y].dist + '0'));
					attroff(COLOR_PAIR(COLOR_MAGENTA));
				}
				else
				{
					attron(COLOR_PAIR(COLOR_CYAN));
					mvaddch(x, y, ((st->map[x][y].dist % 10) + '0'));
					attroff(COLOR_PAIR(COLOR_CYAN));
				}
			}
		}
	}
}



int main() 
{
	STATE st;
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd, nrows, ncols);
	st.jogo.X = nrows;
	st.jogo.Y = ncols;
	st.nivel = 0;
	st.jogador.arma = -1;
	st.jogador.corpo = -1;
	st.jogador.arma_atual = -1;
	//st.jogador.vida = 100;

	srand48(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);

	gerar(&st);
	while (1)
	{
		if (st.jogador.vida <= 0) {
			endwin();
			exit(0);
			break;
		}
		for (int x = 0; x < st.jogo.X; x++)
		{
			for (int y = 0; y < st.jogo.Y; y++)
			{
				st.map[x][y].ilum = 0;
			}
		}
		gerar_seeds(&st);
		iluminacao(&st);
		reset_dist(&st);
		calc_dist(st.jogador.coord.X, st.jogador.coord.Y, 0, &st);
		draw_map(&st);
		draw_arma_faca(&st);
		draw_arma_pistola(&st);
		draw_pocao(&st);
		draw_monsterRato(&st);
		draw_monsterDog(&st);
		draw_monsterBat(&st);
		draw_player(&st);
		draw_info(&st);
		move(st.jogador.coord.X, st.jogador.coord.Y);
		update(&st);
	}
	return 0;
}
