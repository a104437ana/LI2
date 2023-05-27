#include <stdlib.h>
#include <ncurses.h>

#include "update.h"
#include "mapa.h"
#include "actions.h"
#include "combate.h"

/**
 * a104437 - Ana Sá Oliveira - Geração de novo jogo quando encontra escadas, combate com pistola, acontecimentos e tudo que envolva mecher em armas.
 * a104170- Beatriz Peixoto - Acrescentar o movimento dos monstros atrás do jogador, os momentos onde há combate e os comandos usados no ataque e combate.
 * a72481 - Sara Ramalho - Efeito das bombas e das poções.
 * Atualiza o que acontece no jogo em função da jogada (em função da tecla pressionada).
 */
void update(STATE *st)
{
	int r;
	st->acontecimento = 1;
	int key = getch();
	mvaddch(st->jogador.coord.X, st->jogador.coord.Y, '.');
	st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 1;
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
			break;
		case KEY_B2:
		case '5':
			st->map[st->jogador.coord.X][st->jogador.coord.Y].acessivel = 0;
			for (int i=0;i<8;i++) {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
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
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {ataque(st,i);st->acontecimento = 5;}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
			}
			efeito_bomba (st);
			break;
	case 'X':
	case 'x':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,1,0);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y) && (st->monstro[i].coord.X) == st->jogador.coord.X + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
					}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'W':
	case 'w':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,-1,0);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'A':
	case 'a':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,0,-1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.X == st->jogador.coord.X) && (st->monstro[i].coord.Y) == st->jogador.coord.Y - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'D':
	case 'd':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,0,1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.X == st->jogador.coord.X) && (st->monstro[i].coord.Y) == st->jogador.coord.Y + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
		    }
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'Q':
	case 'q':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,-1,-1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y - 1) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'E':
	case 'e':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,-1,1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.Y == st->jogador.coord.Y + 1) && (st->monstro[i].coord.X) == st->jogador.coord.X - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'Z':
	case 'z':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,1,-1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.X == st->jogador.coord.X + 1) && (st->monstro[i].coord.Y) == st->jogador.coord.Y - 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
			}
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case 'C':
	case 'c':
	        if (st->jogador.arma_atual >= 5 && st->jogador.arma_atual < 10) {
				tiros(st,1,1);
			}
			else {
	        for (int i=0;i<8;i++) {
			if ((st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->jogador.arma_atual >= -1 && st->jogador.arma_atual < 5) &&
				((st->monstro[i].coord.X == st->jogador.coord.X + 1) && (st->monstro[i].coord.Y) == st->jogador.coord.Y + 1))
			{
				combate(st,i);
				st->acontecimento = 6;
				break;
		    }
			}
			}
			for (int i=0;i<8;i++) {
				if (st->monstro[i].vida <= 0) morte(st,i);
				else {
				if (st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].dist == 1 && st->monstro[i].vida > 0) {
					ataque(st,i);
					if (st->acontecimento == 7) st->acontecimento = 9;
					else {
					if (st->acontecimento == 8) st->acontecimento = 10;
					else {
					if (st->acontecimento != 6) st->acontecimento = 5;
					}
					}
				}
				else {
					if (st->monstro[i].vida > 0) {
					mvaddch(st->monstro[i].coord.X, st->monstro[i].coord.Y, '.');
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
				    movimento_monstros(st,i);
				    st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 0;
					}
				}
				}
			}
		    break;
	case '+':
			r = efeito_pocao (st);
	        if (r == 0) {
			if (st->jogador.arma == -1) get_arma (st);
			else put_arma (st);
			}
			break;
	case 'S':
	case 's':
			troca(st);
			break;
	case 'L':
	case 'l':
			endwin();
			printf("NIVEL MAXIMO DA CAVERNA ACESSADO POR ESTE JOGADOR : %d\n",st->nivel);
			exit(0);
			break;
	}
}
