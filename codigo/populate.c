#include <ncurses.h>

#include "populate.h"

/**
 * a72481 - Sara Ramalho
 * a104437 - Ana Sá Oliveira
 * Desenha o mapa.
 */
void draw_map(STATE *st)
{
	int x, y;
	/**
     * a104437 - Ana Sá Oliveira
     * Desenha o mapa normalmente.
     */
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
	/**
    * a72481 - Sara Ramalho
    * Desenha as distâncias.
    */
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

void draw_player(STATE *st)
{
	attron(COLOR_PAIR(COLOR_WHITE));
	mvaddch(st->jogador.coord.X, st->jogador.coord.Y, '@' | A_BOLD);
	attroff(COLOR_PAIR(COLOR_WHITE));
}

/**
 * a104437 - Ana Sá Oliveira
 * Desenha as informações que variam ao longo do jogo, por exemplo: vida, arma atual, acontecimento, etc.
 */
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
	if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual<5) printw("faca");
	else {
	if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual<10) printw("pistola");
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
	if (st->acontecimento == 6) printw("atacou e foi atacado por um monstro");
	else {
	if (st->acontecimento == 7) printw("deu um tiro e acertou");
	else {
	if (st->acontecimento == 8) printw("deu um tiro e não acertou");
	else {
	if (st->acontecimento == 9) printw("deu um tiro, acertou e foi atacado por um monstro");
	else {
	if (st->acontecimento == 10) printw("deu um tiro, não acertou e foi atacado por um monstro");
	else {
	if (st->acontecimento == 11) printw("tomou uma poção");
	else {
	if (st->acontecimento == 12) printw("tomou veneno");
	else {
	if (st->acontecimento == 13) printw("uma bomba explodiu");
	else {
	if (st->acontecimento == 14) printw("uma bomba explodiu e foi atacado por um monstro");
	else {
	if (st-> acontecimento == 15) printw("largou uma arma e pegou noutra");
	}
	}
	}
	}
	}
	}
	}
	}
	}
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

/**
 * a104170 - Beatriz Peixoto
 * Desenhar os monstros neste caso 4 ratos.
 */
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

/**
 * a104170 - Beatriz Peixoto
 * Desenhar os monstros- 2 cães.
 */
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

/**
 * a104170 - Beatriz Peixoto
 * Desenhar os monstros - 2 morcegos.
 */
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

/**
 * a72481 - Sara Ramalho
 * Desenhar facas geradas no mapa.
 */
void draw_arma_faca (STATE *st)
{
	for (int i = 0; i < 5; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_YELLOW));
			mvaddch(st->arma[i].coord.X, st->arma[i].coord.Y, 'f' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_YELLOW));
		}
	}
}

/**
 * a72481 - Sara Ramalho
 * Desenhar pistolas geradas no mapa.
 */
void draw_arma_pistola (STATE *st)
{
	for (int i = 5; i < 10; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_YELLOW));
			mvaddch(st->arma[i].coord.X, st->arma[i].coord.Y, 'p' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_YELLOW));
		}
	}
}

/**
 * a72481 - Sara Ramalho
 * Desenhar poções geradas no mapa.
 */
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

/**
 * a72481 - Sara Ramalho
 * Desenhar bombas geradas no mapa.
 */
void draw_bomba (STATE *st)
{
	int i;
	for (i = 0; i < NUM_MAX_BOMBAS; i++)
	{
		if (st->bomba[i].gerada && st->map[st->bomba[i].coord.X][st->bomba[i].coord.Y].ilum == 1)
		{
			attron(COLOR_PAIR(COLOR_RED));
			mvaddch(st->bomba[i].coord.X, st->bomba[i].coord.Y, 'o' | A_BOLD);
			attroff(COLOR_PAIR(COLOR_RED));
			int rX, rY;
	        int r = 1;
	        for (rX = r; rX >= - r ; rX--) {
			    for (rY = r; rY >= - r ; rY--) {
					if (rX == 0 && rY == 0) continue;
				    if (st->map[st->bomba[i].coord.X + rX][st->bomba[i].coord.Y + rY].caracterAtual == '.' && st->map[st->bomba[i].coord.X + rX][st->bomba[i].coord.Y + rY].ilum == 1) {
				        attron(COLOR_PAIR(COLOR_RED));
		                mvaddch(st->bomba[i].coord.X + rX, st->bomba[i].coord.Y + rY, st->map[st->bomba[i].coord.X + rX][st->bomba[i].coord.Y + rY].caracterAtual | A_BOLD);
		                attroff(COLOR_PAIR(COLOR_RED));
				}
			}
		}
		}
	}
}
