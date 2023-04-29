#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"
#include "mapa.h"

void draw_player (STATE *st) {
	attron(COLOR_PAIR(COLOR_WHITE));
	mvaddch(st->playerX, st->playerY, '@' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_WHITE));
}

void draw_light (STATE *st) {
	signed int rX, rY;
	for (rX = 1; rX >= - 1 ; rX--) {
			for (rY = 1; rY >= - 1 ; rY--) {
				st->map[st->playerX+rX][st->playerY+rY].ilum = 1;
			}
		}
}

void draw_info (STATE *st) {
	move(st->nROWS - 1, 0);
	attron(COLOR_PAIR(COLOR_BLUE));
	printw("(%d, %d) %d %d", st->playerX, st->playerY, st->nROWS, st->nCOLS);
	printw(" ");
	attroff(COLOR_PAIR(COLOR_BLUE));
}

void do_movement_action(STATE *st, int dx, int dy) {
	st->playerX += dx;
	st->playerY += dy;
}

void update(STATE *st) {
	int key = getch();

	mvaddch(st->playerX, st->playerY, '.');
	switch(key) {
		case KEY_A1:
		case '7': 
		    if (st->map[st->playerX -1][st->playerY -1].caracterAtual != '#') do_movement_action(st, -1, -1);
			break;
		case KEY_UP:
		case '8': 
		    if (st->map[st->playerX -1][st->playerY].caracterAtual != '#') do_movement_action(st, -1, +0); 
			break;
		case KEY_A3:
		case '9': 
		    if (st->map[st->playerX -1][st->playerY +1].caracterAtual != '#') do_movement_action(st, -1, +1); 
			break;
		case KEY_LEFT:
		case '4': 
	        if (st->map[st->playerX][st->playerY-1].caracterAtual != '#') do_movement_action(st, +0, -1); 
			break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6': 
		    if (st->map[st->playerX][st->playerY +1].caracterAtual != '#') do_movement_action(st, +0, +1); 
			break;
		case KEY_C1:
		case '1': 
		    if (st->map[st->playerX +1][st->playerY -1].caracterAtual != '#') do_movement_action(st, +1, -1); 
			break;
		case KEY_DOWN:
		case '2': 
		    if (st->map[st->playerX +1][st->playerY].caracterAtual != '#') do_movement_action(st, +1, +0);
			break;
		case KEY_C3:
		case '3': 
	        if (st->map[st->playerX +1][st->playerY +1].caracterAtual != '#') do_movement_action(st, +1, +1); 
			break;
		case 'q': endwin(); exit(0); break;
	}
}

void draw_map (STATE *st) {
	int x, y;
	for (x=0;x<st->nROWS;x++) {
		for (y=0;y<st->nCOLS;y++) {
			if (st->map[x][y].ilum == 0) {
				attron(COLOR_PAIR(COLOR_BLUE));
				mvaddch(x,y, st->map[x][y].caracterAtual | A_BOLD);
				attroff(COLOR_PAIR(COLOR_BLUE));
			}
			else {
				attron(COLOR_PAIR(COLOR_WHITE));
				mvaddch(x,y, st->map[x][y].caracterAtual | A_BOLD);
				attroff(COLOR_PAIR(COLOR_WHITE));
			}
		}
	}
}

int main() {
	STATE st;
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
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

	gerar(&st);

	while(1) {
		for (int x = 0; x < st.nROWS; x++) {
			for (int y = 0; y < st.nCOLS ; y++) {
				st.map[x][y].ilum = 0; //antes da função draw_ligth apagamos as luzes todas
			}
		}
		draw_light (&st); //acender as luzes pretendidas
		draw_map(&st);
		draw_info(&st);
		draw_player(&st);
		move(st.playerX, st.playerY);
		update(&st);
	}

	return 0;
}
