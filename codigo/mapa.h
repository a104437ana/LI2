#include "state.h"

void escada (STATE *st);
int raio (STATE *st, int x, int y, int r);
void first_map (STATE *st);
void first_alg (STATE *st);
void second_alg (STATE *st);
void flood_fill_alg (STATE *st, int x, int y, int valor);
void gerar(STATE *s);
void gerarCoordMontro(STATE *st);