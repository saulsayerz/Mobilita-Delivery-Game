#include <stdio.h>
#include "point.h"

POINT MakePOINT(int X, int Y)
{
    POINT p;
    Absis(p) = X;
    Ordinat(p) = Y;
    return p;
}

void BacaPOINT(POINT *P)
{
    int x, y;
    scanf("%d %d", &x, &y);
    Absis(*P) = x;
    Ordinat(*P) = y;
}

void TulisPOINT(POINT P)
{
    printf("(%d,%d)", Absis(P), Ordinat(P));
}

boolean EQ(POINT P1, POINT P2)
{
    return ((Absis(P1) == Absis(P2)) && (Ordinat(P1) == Ordinat(P2)));
}

boolean NEQ(POINT P1, POINT P2)
{
    return !EQ(P1, P2);
}

boolean IsOrigin(POINT P)
{
    return ((Absis(P) == 0) && (Ordinat(P) == 0));
}

boolean IsOnSbX(POINT P)
{
    return (Ordinat(P) == 0);
}

boolean IsOnSbY(POINT P)
{
    return (Absis(P) == 0);
}

int Kuadran(POINT P)
{
    int kuadran = 0;
    if ((Absis(P) > 0) && (Ordinat(P) > 0))
    {
        kuadran = 1;
    }
    else if ((Absis(P) < 0) && (Ordinat(P) > 0))
    {
        kuadran = 2;
    }
    else if ((Absis(P) < 0) && (Ordinat(P) < 0))
    {
        kuadran = 3;
    }
    else if ((Absis(P) > 0) && (Ordinat(P) < 0))
    {
        kuadran = 4;
    }
    return kuadran;
}

POINT NextX(POINT P)
{
    Absis(P) = Absis(P) + 1;
    return P;
}

POINT NextY(POINT P)
{
    Ordinat(P) = Ordinat(P) + 1;
    return P;
}

POINT PlusDelta(POINT P, int deltaX, int deltaY)
{
    Absis(P) = Absis(P) + deltaX;
    Ordinat(P) = Ordinat(P) + deltaY;
    return P;
}

POINT MirrorOf(POINT P, boolean SbX)
{
    if (SbX)
    {
        Ordinat(P) = Ordinat(P) * (-1);
    }
    else
    {
        Absis(P) = Absis(P) * (-1);
    }
    return P;
}

void Geser(POINT *P, float deltaX, float deltaY)
{
    Absis(*P) = Absis(*P) + deltaX;
    Ordinat(*P) = Ordinat(*P) + deltaY;
}

void GeserKeSbX(POINT *P)
{
    Ordinat(*P) = 0;
}

void GeserKeSbY(POINT *P)
{
    Absis(*P) = 0;
}

void Mirror(POINT *P, boolean SbX)
{
    if (SbX)
    {
        Ordinat(*P) = Ordinat(*P) * (-1);
    }
    else
    {
        Absis(*P) = Absis(*P) * (-1);
    }
}