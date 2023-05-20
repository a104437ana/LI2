#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "state.h"
#include "mapa.h"
#include "populate.h"
#include "iluminacao.h"
#include "distancia.h"
#include "update.h"

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
	st.jogador.vida = 100;
	for (int i = 0; i < 4; i++)
    {
	st.arma[i].equipada = 0;
	}

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
			printf("NIVEL MAXIMO DA CAVERNA ACESSADO POR ESTE JOGADOR : %d\n",st.nivel);
			exit(0);
			break;
		}
		for (int x = 0; x < st.jogo.X; x++)
		{
			for (int y = 0; y < st.jogo.Y; y++)
			{
				st.map[x][y].ilum = LIGHT_STATE;
			}
		}
		gerar_seeds(&st);
		reset_dist(&st);
		calc_dist(st.jogador.coord.X, st.jogador.coord.Y, 0, &st);
		iluminacao(&st);
		draw_map(&st);
		draw_arma_faca(&st);
		draw_arma_pistola(&st);
		draw_pocao(&st);
		draw_bomba(&st);
		draw_monsterRato(&st);
		draw_monsterDog(&st);
		draw_monsterBat(&st);
		draw_player(&st);
		draw_info(&st);
		move(st.jogo.X - 1, 0);
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | Sair - ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		attron(COLOR_PAIR(COLOR_YELLOW));
	    printw("L");
	    attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | Beber poção / Pegar ou largar armas - ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		attron(COLOR_PAIR(COLOR_YELLOW));
	    printw("+");
	    attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | Trocar arma atual - ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		attron(COLOR_PAIR(COLOR_YELLOW));
	    printw("S");
	    attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | Andar na respetiva direção - ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		attron(COLOR_PAIR(COLOR_YELLOW));
	    printw("1,2,3,4,5,6,7,8,9");
	    attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | Atacar na respetiva direção com a arma atual - ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		attron(COLOR_PAIR(COLOR_YELLOW));
	    printw("Z,X,C,A,D,Q,W,E");
	    attroff(COLOR_PAIR(COLOR_YELLOW));
		attron(COLOR_PAIR(COLOR_GREEN));
	    printw(" | ");
	    attroff(COLOR_PAIR(COLOR_GREEN));
		move(st.jogador.coord.X, st.jogador.coord.Y);
		update(&st);
	}
	return 0;
}