#include <math.h>

#include "iluminacao.h"

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
			if (st->map[(int)(x)][(int)(y)].caracterAtual == '#' || st->map[(int)(x)][(int)(y)].dist == 300) break;
			x = x + xVetor;
			y = y + yVetor;
		}

		angulo = angulo + 1;
	}
}