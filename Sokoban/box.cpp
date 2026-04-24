#include "box.h"

Box::Box(int x, int y)
{
	update(x, y, false);
}


void Box::update(int x, int y, bool complete)
{
	pos.x = x;
	pos.y = y;

	rect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

	in_goal = complete;
}

vec2 Box::get_pos()
{
	return pos;
}

SDL_Rect* Box::get_rect()
{
	return &rect;
}

bool Box::get_in_goal()
{
	return in_goal;
}
