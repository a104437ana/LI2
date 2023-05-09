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

void draw_monsterRato(STATE *st)
{  

	for (int i=0;i<4;i++) {
	attron(COLOR_PAIR(COLOR_MAGENTA));
	mvaddch(st->monstro[i].X, st->monstro[i].Y, 'r' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_MAGENTA));
}
}

void draw_monsterDog(STATE *st)
{  

	for (int i=4;i<6;i++) {
	attron(COLOR_PAIR(COLOR_MAGENTA));
	mvaddch(st->monstro[i].X, st->monstro[i].Y, 'd' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_MAGENTA));
}
}

void draw_monsterBat(STATE *st)
{  

	for (int i=6;i<8;i++) {
	attron(COLOR_PAIR(COLOR_MAGENTA));
	mvaddch(st->monstro[i].X, st->monstro[i].Y, 'b' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_MAGENTA));
}
}

void draw_player(STATE *st)
{
	attron(COLOR_PAIR(COLOR_WHITE));
	mvaddch(st->jogador.X, st->jogador.Y, '@' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_WHITE));
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

void draw_light(STATE *st)
{
	signed int rX, rY;
	for (rX = 1; rX >= -1; rX--)
	{
		for (rY = 1; rY >= -1; rY--)
		{
			st->map[st->jogador.X + rX][st->jogador.Y + rY].ilum = 1;
		}
	}
}

void draw_info(STATE *st) {
	move(st->jogo.X - 1, 0);
	attron(COLOR_PAIR(COLOR_BLUE));
	printw("(%d, %d) %d %d -> %d", st->jogador.X, st->jogador.Y, st->jogo.X, st->jogo.Y, (st->paredes * 100) / (st->jogo.X * st->jogo.Y));
	printw(" ");
	attroff(COLOR_PAIR(COLOR_BLUE));
}

void do_movement_action(STATE *st, int dx, int dy)
{
	st->jogador.X += dx;
	st->jogador.Y += dy;
}

void movimento_monstros (STATE *st, int i) {
	if (st->map[st->monstro[i].X][st->monstro[i].Y].dist != 300) {
	 {
		if (st->map[st->monstro[i].X - 1][st->monstro[i].Y].acessivel ==1 && st->map[st->monstro[i].X - 1][st->monstro[i].Y].dist < st->map[st->monstro[i].X][st->monstro[i].Y].dist)
		{
		st->monstro[i].X = st->monstro[i].X - 1;
		}
		else {
			if (st->map[st->monstro[i].X + 1][st->monstro[i].Y].dist < st->map[st->monstro[i].X][st->monstro[i].Y].dist)
		    {
			st->monstro[i].X = st->monstro[i].X + 1;
		    }
			else {
				if (st->map[st->monstro[i].X][st->monstro[i].Y - 1].dist < st->map[st->monstro[i].X][st->monstro[i].Y].dist)
		        {
			    st->monstro[i].Y = st->monstro[i].Y - 1;
		        }
				else {
					if (st->map[st->monstro[i].X][st->monstro[i].Y + 1].dist < st->map[st->monstro[i].X][st->monstro[i].Y].dist)
		            {
			        st->monstro[i].Y = st->monstro[i].Y + 1;
		            }
					else {

					}
				}
			}
		}
	}
}
}

void update(STATE *st)
{
	int key = getch();
	mvaddch(st->jogador.X, st->jogador.Y, '.');
	if (st->map[st->jogador.X][st->jogador.Y].caracterAtual == '<') st->map[st->jogador.X][st->jogador.Y].acessivel = 0;
	else st->map[st->jogador.X][st->jogador.Y].acessivel = 1;
	switch (key)
	{
	case KEY_A1:
	case '7':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X - 1][st->jogador.Y - 1].caracterAtual == '.' || st->map[st->jogador.X - 1][st->jogador.Y - 1].caracterAtual == '+')
			do_movement_action(st, -1, -1);
		else {
			if (st->jogador.X - 1 == st->escada.X && st->jogador.Y - 1== st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_UP:
	case '8':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X - 1][st->jogador.Y].caracterAtual == '.' || st->map[st->jogador.X - 1][st->jogador.Y].caracterAtual == '+')
			do_movement_action(st, -1, +0);
		else {
			if (st->jogador.X - 1 == st->escada.X && st->jogador.Y == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_A3:
	case '9':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X - 1][st->jogador.Y + 1].caracterAtual == '.' || st->map[st->jogador.X - 1][st->jogador.Y + 1].caracterAtual == '+')
			do_movement_action(st, -1, +1);
		else {
			if (st->jogador.X - 1 == st->escada.X && st->jogador.Y + 1 == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_LEFT:
	case '4':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X][st->jogador.Y - 1].caracterAtual == '.' || st->map[st->jogador.X][st->jogador.Y - 1].caracterAtual == '+')
			do_movement_action(st, +0, -1);
		else {
			if (st->jogador.X == st->escada.X && st->jogador.Y - 1 == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_B2:
	case '5':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		break;
	case KEY_RIGHT:
	case '6':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X][st->jogador.Y + 1].caracterAtual == '.' || st->map[st->jogador.X][st->jogador.Y + 1].caracterAtual == '+')
			do_movement_action(st, +0, +1);
		else {
			if (st->jogador.X == st->escada.X && st->jogador.Y + 1 == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_C1:
	case '1':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X + 1][st->jogador.Y - 1].caracterAtual == '.' || st->map[st->jogador.X + 1][st->jogador.Y - 1].caracterAtual == '+')
			do_movement_action(st, +1, -1);
		else {
			if (st->jogador.X + 1 == st->escada.X && st->jogador.Y - 1 == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_DOWN:
	case '2':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X + 1][st->jogador.Y].caracterAtual == '.' || st->map[st->jogador.X + 1][st->jogador.Y].caracterAtual == '+')
			do_movement_action(st, +1, +0);
		else {
			if (st->jogador.X + 1 == st->escada.X && st->jogador.Y == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case KEY_C3:
	case '3':
	    for (int i=0;i<8;i++) {
		mvaddch(st->monstro[i].X, st->monstro[i].Y, '.');
		st->map[st->monstro[i].X][st->monstro[i].Y].acessivel = 1;
		movimento_monstros(st,i);
	    }
		if (st->map[st->jogador.X + 1][st->jogador.Y + 1].caracterAtual == '.' || st->map[st->jogador.X + 1][st->jogador.Y + 1].caracterAtual == '+')
			do_movement_action(st, +1, +1);
		else {
			if (st->jogador.X + 1 == st->escada.X && st->jogador.Y + 1 == st->escada.Y) {
			    gerar(st);
			}
		}
		break;
	case 'q':
		endwin();
		exit(0);
		break;
	}
}


void draw_map(STATE *st)
{
	int x, y;
	for (x = 0; x < st->jogo.X; x++)
	{
		for (y = 0; y < st->jogo.Y; y++)
		{
			if (st->map[x][y].ilum == 0)
			{
				attron(COLOR_PAIR(COLOR_BLUE));
				mvaddch(x, y, st->map[x][y].caracterAtual | A_BOLD);
				attroff(COLOR_PAIR(COLOR_BLUE));
			}
			else
			{
				attron(COLOR_PAIR(COLOR_WHITE));
				mvaddch(x, y, st->map[x][y].caracterAtual | A_BOLD);
				attroff(COLOR_PAIR(COLOR_WHITE));
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
	st.paredes = 0;

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
		for (int x = 0; x < st.jogo.X; x++)
		{
			for (int y = 0; y < st.jogo.Y; y++)
			{
				st.map[x][y].ilum = 0; // antes da função draw_ligth apagamos as luzes todas
			}
		}
		draw_light(&st); // acender as luzes pretendidas
		reset_dist(&st);
		calc_dist(st.jogador.X, st.jogador.Y, 0, &st);
		draw_map(&st);
		draw_info(&st);
		draw_player(&st);
		draw_monsterRato(&st);
		draw_monsterDog(&st);
		draw_monsterBat(&st);
		move(st.jogador.X, st.jogador.Y);
		update(&st);
	}
	return 0;
}
