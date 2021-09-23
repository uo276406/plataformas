#pragma once

#include "Game.h"

class Text
{
public:
	Text(string content, float x, float y, Game* game);
	void draw();
	string content; // texto
	int x,y, width, heigth;
	
	Game* game; // referencia al juego
};


