#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"

#include "Audio.h"
#include "Space.h" // importar

#include "Pad.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer l?neas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Space* space;
	float scrollX;
	int mapWidth;
	list<Tile*> tiles;

	Audio* audioBackground;
	Text* textPoints;
	int points;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	Tile* cup; // Elemento de final de nivel
	
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	// Elementos de interfaz
	Actor* buttonJump;
	Actor* buttonShoot;
	Pad* pad;

};

