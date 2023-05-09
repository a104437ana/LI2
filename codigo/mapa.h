#include "state.h"

void gerar_coordenadas (STATE *st);
int raio (STATE *st, int x, int y, int r);
void first_map (STATE *st);
void first_alg (STATE *st);
void second_alg (STATE *st);
void flood_fill_alg (STATE *st, int x, int y, int valor1, int valor2);
void reset_acesso (STATE *st);
int prencher_mapa_acesso (STATE *st);
void gerar_corredores (STATE *st, int i);
void gerar(STATE *s);