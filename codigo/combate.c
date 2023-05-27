#include "combate.h"

/**
 * a72481 - Sara Ramalho
 * O jogador pega numa arma do mapa.
 */
void get_arma (STATE *st)
{
	int i, stop;
	stop = 0;

	for (i = 0; !stop && i < 10; i++)
	{
		if (st->arma[i].equipada != 1 && st->map[st->arma[i].coord.X][st->arma[i].coord.Y].dist == 0)
		{
			st->acontecimento = 2;
			st->jogador.arma = i;
			st->jogador.arma_atual = i;
			st->arma[i].equipada = 1;
			st->arma[i].coord.X = 0;
	        st->arma[i].coord.Y = 0;
			stop = 1;
		}
	}
}

/**
 * a72481 - Sara Ramalho
 * O jogador coloca a arma de volta no mapa.
 */
void put_arma (STATE *st)
{
	if (st->map[st->jogador.coord.X][st->jogador.coord.Y].objeto == 0) {
	if (st->jogador.arma != -1) st->acontecimento = 3;
	st->arma[st->jogador.arma].equipada = 0;
	st->arma[st->jogador.arma].coord.X = st->jogador.coord.X;
	st->arma[st->jogador.arma].coord.Y = st->jogador.coord.Y;
	st->jogador.arma = -1;
	st->jogador.arma_atual = -1;
	}
	else {
	int stop = 0;
	for (int i = 0; !stop && i < 10; i++) {
	if (st->jogador.coord.X == st->arma[i].coord.X && st->jogador.coord.Y == st->arma[i].coord.Y) {
		st->acontecimento = 15;
		st->arma[st->jogador.arma].equipada = 0;
	    st->arma[st->jogador.arma].coord.X = st->jogador.coord.X;
	    st->arma[st->jogador.arma].coord.Y = st->jogador.coord.Y;
	    st->jogador.arma = i;
	    st->jogador.arma_atual = i;
		st->arma[i].equipada = 1;
		st->arma[i].coord.X = 0;
	    st->arma[i].coord.Y = 0;
		stop = 1;
	}
	}
	}
}

void troca (STATE *st) {
	st->acontecimento = 4;
	if (st->jogador.arma_atual == -1) st->jogador.arma_atual = st->jogador.arma;
	else {
		st->jogador.arma_atual = -1;
	}
}

void ataque (STATE *st, int i) {
	if ((i >= 0 && i < 4) && st->monstro[i].vida > 0)
	{
		st->jogador.vida = st->jogador.vida - 15; // 7 mordidas
	}
	if ((i >= 4 && i < 6) && st->monstro[i].vida > 0)
	{
		st->jogador.vida = st->jogador.vida - 20; // 5 mordidas
	}
	if ((i >= 6 && i < 8) && st->monstro[i].vida > 0)
	{
		st->jogador.vida = st->jogador.vida - 15; // 7 mordidas
	}
}

void tiros (STATE *st, int a, int b) {
	int monstro = 1;
	int x = st->jogador.coord.X;
	int y = st->jogador.coord.Y;
	while (st->map[x][y].caracterAtual != '#' && monstro == 1) {
		for (int i = 0; i<8; i++) {
			if (x == st->monstro[i].coord.X && y == st->monstro[i].coord.Y) {
				if (i >=0 && i <4)
			   {
				st->monstro[i].vida = st->monstro[i].vida - 25; // 4 tiros
				monstro = 0;
				break;
			   }
			   if (i >= 4 && i < 6)
			   {
				st->monstro[i].vida = st->monstro[i].vida - 15; // 7 tiros
				monstro = 0;
				break;
			   }
			   if (i >= 6 && i<8)
			   {
				st->monstro[i].vida=st->monstro[i].vida - 20; // 5 tiros
				monstro=0;
				break;
			   }
			}
		}
		x+=a;
		y+=b;
	}
	if (monstro == 0) st->acontecimento = 7;
	else {st->acontecimento = 8;}
}

void combate(STATE *st, int i)
{
	if (i>=0 && i<4 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual < 5) 
			{
				st->monstro[i].vida = st->monstro[i].vida - 50; // 2 facadas
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida - 17; // 6 socos
			}
	}
	if (i>=4 && i<6 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual < 5)
			{
				st->monstro[i].vida = st->monstro[i].vida - 35; // 3 facadas
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida - 25; // 4 socos
			}
	}
	if (i>=6 && i<8 && st->monstro[i].vida > 0)
	{
			if (st->jogador.arma_atual >= 0 && st->jogador.arma_atual < 5)
			{
				st->monstro[i].vida = st->monstro[i].vida - 50; // 2 facadas
			}
			else 
			{
				st->monstro[i].vida=st->monstro[i].vida - 17; // 6 socos
			}
	}
}

void morte (STATE *st, int i) {
	st->map[st->monstro[i].coord.X][st->monstro[i].coord.Y].acessivel = 1;
	st->monstro[i].coord.X = 0;
	st->monstro[i].coord.Y = 0;
	st->monstro[i].vida = 0;
}

/**
 * a72481 - Sara Ramalho
 * Efeito da poção na vida do jogador quando usada.
 */
int efeito_pocao (STATE *st)
{
	int x = 0;
	for (int i = 0; i < st->pocaoMax; i++)
	{
		if (st->pocao[i].gerada && st->map[st->pocao[i].coord.X][st->pocao[i].coord.Y].dist == 0)
		{
			switch (st->pocao[i].tipo)
			{
			case 0: // veneno
				st->jogador.vida += POISON;
				st->acontecimento = 12;
				break;
			case 1:  // poção "pequena" (comida)
			case 3:
			case 5:
			case 7:
			case 9:
			case 11:
			case 13:
			case 15:
			case 17:
			case 19:
				st->jogador.vida += SMALL_POTION;
				st->acontecimento = 11;
				break;
			case 2: // poção "grande"
			case 4:
			case 6:
			case 8:
			case 10:
			case 12:
			case 14:
			case 16:
			case 18:
				st->jogador.vida += LARGE_POTION;
				st->acontecimento = 11;
				break;
			}
		// destruir poção depois de usada
		st->pocao[i].gerada = 0;
		st->map[st->pocao[i].coord.X][st->pocao[i].coord.Y].objeto = 0;
		x = 1;
		}
	}
	if (st->jogador.vida < MIN_VIDA_JOGADOR) st->jogador.vida = MIN_VIDA_JOGADOR;
	if (st->jogador.vida > MAX_VIDA_JOGADOR) st->jogador.vida = MAX_VIDA_JOGADOR;
	return x;
	
}

/**
 * a72481 - Sara Ramalho
 * Efeito da bomba na vida do jogador quando pisada a área circundante.
 */
void efeito_bomba (STATE *st)
{
	for (int i = 0; i < NUM_MAX_BOMBAS; i++)
	{
		if (st->bomba[i].gerada && st->map[st->bomba[i].coord.X][st->bomba[i].coord.Y].dist == 1)
		{
			st->jogador.vida += EXPLOSAO;
			if (st->acontecimento == 5) st->acontecimento = 14;
			else st->acontecimento = 13;
			st->bomba[i].gerada = 0;
			st->map[st->bomba[i].coord.X][st->bomba[i].coord.Y].objeto = 0;
		}
	}
	if (st->jogador.vida < MIN_VIDA_JOGADOR) st->jogador.vida = MIN_VIDA_JOGADOR;
}
