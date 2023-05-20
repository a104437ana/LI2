#include <ncurses.h>

#include "actions.h"

void do_movement_action(STATE *st, int dx, int dy)
{
	st->jogador.coord.X += dx;
	st->jogador.coord.Y += dy;
}

void movimento_monstros (STATE *st, int i)
{	
	if (st->monstro[i].vida > 0) {
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
}