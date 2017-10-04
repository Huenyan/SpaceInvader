#include "tiro.h"

int getAtivoTiro(TIRO* tiro)
{
    return tiro->ativo;
}
void setAtivoTiro(TIRO* tiro, int ativo)
{
    tiro->ativo = ativo;
}
int getXTiro(TIRO* tiro)
{
    return tiro->x;
}
void setXTiro(TIRO* tiro, int x)
{
    tiro->x = x;
}
int getYTiro(TIRO* tiro)
{
    return tiro->y;
}
void setYTiro(TIRO* tiro, int y)
{
    tiro->y = y;
}
