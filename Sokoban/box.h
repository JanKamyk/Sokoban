#pragma once

#include "utils.h"

class Box {
public:
	Box(int x, int y);
	void update(int x, int y, bool complete);
	vec2 get_pos();
	SDL_Rect* get_rect();
	bool get_in_goal();

private:
	vec2 pos;
	SDL_Rect rect;
	bool in_goal;
};