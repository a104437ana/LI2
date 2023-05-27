#include <math.h>

#include "iluminacao.h"

/**
 * a104170- Beatriz Peixoto
 * Campo de visão do jogador. Para cada ângulo, às coordenadas do jogador soma-se o vetor (xVetor, yVetor) e atualizamos as coordenadas do jogador 
 até atingirmos uma parede ou que a distancia seja maior que a definida.
 */

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