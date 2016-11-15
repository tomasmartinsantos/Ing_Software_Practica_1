// Practica_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


static const int  ANCHO_MUNDO = 80;
static const char PERSONAJE = '*';
static const char MOVER_DER = 'd';
static const char MOVER_IZQ = 'a';
static const char BALA = 'o';
static const char DISPARO_DER = 'p';
static const char DISPARO_IZQ = 'o';
static const int  FPS = 20;
static const int  MILISEG_FRAME = 1000 / FPS;
int               posicion = -1;
int               posicionBala = -1;
bool              disparoActivado = false;

void pintarMundo(const char personaje)
{
	for (int i = 0; i < 10; i++)
		printf("\n");

	int i = 0;
	while (i < ANCHO_MUNDO)
	{
		if (i == ANCHO_MUNDO / 2)
		{
			printf("%c", personaje);
			posicion = i;
		}
		else
			printf("_");
		i++;
	}
	printf("\r");
}

void moverYDisparar()
{
	char tecla;
	if (disparoActivado)
	{
		if (posicionBala < posicion)
			posicionBala -= 1;
		else
			posicionBala += 1;
	}

	else if (_kbhit())
	{
		tecla = _getch();
		if (tecla == MOVER_DER && (posicion + 1) < ANCHO_MUNDO)
			posicion += 1;
		else if (tecla == MOVER_IZQ && (posicion - 1) > -1)
			posicion -= 1;
		else if (tecla == DISPARO_DER && !disparoActivado)
		{
			posicionBala = posicion + 1;
			disparoActivado = true;
		}
		else if (tecla == DISPARO_IZQ && !disparoActivado)
		{
			posicionBala = posicion - 1;
			disparoActivado = true;
		}
	}
}

void pintar()
{
	int i = 0;
	while (i < ANCHO_MUNDO)
	{
		if (i == posicion)
			printf("%c", PERSONAJE);
		else if (i == posicionBala)
		{
			if ((posicionBala + 1 >= ANCHO_MUNDO) || (posicionBala - 1 <= -1))
				disparoActivado = false;
			else
				printf("%c", BALA);
		}
		else
			printf("_");
		i++;
	}
	printf("\r");
}

int main()
{
	pintarMundo(PERSONAJE);
	while (true)
	{
		moverYDisparar();
		pintar();
		Sleep(MILISEG_FRAME);
	}

	return 0;
}