#include "distancia.h"

/**
 * a72481 - Sara Ramalho
 * Todos os pontos do mapa ficam com o valor 300 para a distância, até a mesma ser calculada na função calc_dist.
 */
void reset_dist(STATE *st)
{
	int i, j;

	for (i = 0; i < st->jogo.X; i++)
	{
		for (j = 0; j < st->jogo.Y; j++)
			st->map[i][j].dist = 300;
	}
}

/**
 * a72481 - Sara Ramalho
 * Calcula a distância de um ponto do mapa ao jogador.
 */
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
