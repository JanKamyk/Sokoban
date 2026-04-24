#pragma once

#include "sokoban.h"

class Player {

public:
	Player(class Game* g);
	void move(int x, int y);
	void reset(int x, int y);
	void draw(SDL_Renderer* renderer);

private:
	void set_direction(int x, int y);
	int direction;
	vec2 pos;
	SDL_Texture* texture;
	SDL_Rect posRect, spriteRect;
	class Game* game;
};

