#include "state.h"

void get_arma (STATE *st);
void put_arma (STATE *st);
void troca (STATE *st);
void ataque (STATE *st, int i);
void tiros (STATE *st, int a, int b);
void combate(STATE *st, int i);
void morte (STATE *st, int i);
int efeito_pocao (STATE *st);
void efeito_bomba (STATE *st);