#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>
#include "state.h"
#include "mapa.h"

#define MAX_DIST 19
#define MAX_ROW 60	// x
#define MAX_COL 250 // y
#define SHOW_DIST 1

void draw_player(STATE *st)
{
	attron(COLOR_PAIR(COLOR_WHITE));
	mvaddch(st->playerX, st->playerY, '@' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_WHITE));
}

void gerarCoordMonstro(STATE *st)
{
	st->monsterX = lrand48() % (st->nROWS);
	st->monsterY = lrand48() % (st->nCOLS);

	while (st->map[st->monsterX][st->monsterY].caracterAtual == '#')
	{
		st->monsterX = lrand48() % (st->nROWS);
		st->monsterY = lrand48() % (st->nCOLS);
	}
}

// calcula a distancia entre o monstro e o jogador


int distMonsterPlayer(STATE *st)
{
	return st->map[st->monsterX][st->monsterX].dist;
}

void draw_monster(STATE *st)
{
	attron(COLOR_PAIR(COLOR_MAGENTA));
	mvaddch(st->monsterX, st->monsterY, 'r' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_MAGENTA));
}

void reset_dist(STATE *st)
{
	int i, j;

	for (i = 0; i < MAX_ROW; i++)
	{
		for (j = 0; j < MAX_COL; j++)
			st->map[i][j].dist = -1;
	}
}

 void calc_dist(int R, int C, int value, STATE *st)
{
	if (R < 0 || C < 0 || R > MAX_ROW || C > MAX_COL)
		return;
	if (value > MAX_DIST)
		return;
	if (st->map[R][C].dist != (-1) && st->map[R][C].dist <= value)
		return;
	if (st->map[R][C].caracterAtual == '#')
		return;

	st->map[R][C].dist = value;

	// A flag SHOW_DIST permite mostrar ou esconder as distâncias. Deve-se comentar a função draw_light para não se sobrepor.
	if (SHOW_DIST && value != 0)
	{
		if (value < 10)
		{
			attron(COLOR_PAIR(COLOR_MAGENTA));
			mvaddch(R, C, (value + '0'));
			attroff(COLOR_PAIR(COLOR_MAGENTA));
		}
		else
		{
			attron(COLOR_PAIR(COLOR_CYAN));
			mvaddch(R, C, ((value % 10) + '0'));
			attroff(COLOR_PAIR(COLOR_CYAN));
		}
	}

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
			st->map[st->playerX + rX][st->playerY + rY].ilum = 1;
		}
	}
}

void draw_info(STATE *st)
{
	move(st->nROWS - 1, 0);
	attron(COLOR_PAIR(COLOR_BLUE));
	printw("(%d, %d) %d %d", st->playerX, st->playerY, st->nROWS, st->nCOLS);
	printw(" ");
	attroff(COLOR_PAIR(COLOR_BLUE));
}

void do_movement_action(STATE *st, int dx, int dy)
{
	st->playerX += dx;
	st->playerY += dy;
}

void update(STATE *st)
{
	int key = getch();

	mvaddch(st->playerX, st->playerY, '.');
    mvaddch(st->monsterX, st->monsterY, '.');
	switch (key)
	{
	case KEY_A1:
	case '7':
		if (st->map[st->playerX - 1][st->playerY - 1].caracterAtual != '#')
			do_movement_action(st, -1, -1);
		break;
	case KEY_UP:
	case '8':
		if (st->map[st->playerX - 1][st->playerY].caracterAtual != '#')
			do_movement_action(st, -1, +0);
		break;
	case KEY_A3:
	case '9':
		if (st->map[st->playerX - 1][st->playerY + 1].caracterAtual != '#')
			do_movement_action(st, -1, +1);
		break;
	case KEY_LEFT:
	case '4':
		if (st->map[st->playerX][st->playerY - 1].caracterAtual != '#')
			do_movement_action(st, +0, -1);
		break;
	case KEY_B2:
	case '5':
		break;
	case KEY_RIGHT:
	case '6':
		if (st->map[st->playerX][st->playerY + 1].caracterAtual != '#')
			do_movement_action(st, +0, +1);
		break;
	case KEY_C1:
	case '1':
		if (st->map[st->playerX + 1][st->playerY - 1].caracterAtual != '#')
			do_movement_action(st, +1, -1);
		break;
	case KEY_DOWN:
	case '2':
		if (st->map[st->playerX + 1][st->playerY].caracterAtual != '#')
			do_movement_action(st, +1, +0);
		break;
	case KEY_C3:
	case '3':
		if (st->map[st->playerX + 1][st->playerY + 1].caracterAtual != '#')
			do_movement_action(st, +1, +1);
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
	for (x = 0; x < st->nROWS; x++)
	{
		for (y = 0; y < st->nCOLS; y++)
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
}

int main()
{
	STATE st;
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd, nrows, ncols);
	st.nROWS = nrows;
	st.nCOLS = ncols;

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
	gerarCoordMonstro(&st);

	while (1)
	{
		for (int x = 0; x < st.nROWS; x++)
		{
			for (int y = 0; y < st.nCOLS; y++)
			{
				st.map[x][y].ilum = 0; // antes da função draw_ligth apagamos as luzes todas
			}
		}
		draw_light(&st); // acender as luzes pretendidas
		draw_map(&st);
		draw_info(&st);
		draw_player(&st);
		draw_monster(&st);
		reset_dist(&st);
		calc_dist(st.playerX, st.playerY, 0, &st);
		draw_light(&st);
		move(st.playerX, st.playerY);
		update(&st);
	}

	return 0;
}
