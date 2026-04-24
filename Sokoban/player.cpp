#include "player.h"

Player::Player(Game* g) {
	game = g;
	texture = game->loadtexture("textures/player.png");
	direction = 0;
	pos.x = 0;
	pos.y = 0;
	posRect = { pos.x, pos.y, TILE_SIZE, TILE_SIZE };
	spriteRect = { 0, 0, TILE_SIZE, TILE_SIZE };
}

void Player::move(int x, int y) {

	set_direction(x, y);
	int newplayer_x = pos.x + x;
	int newplayer_y = pos.y + y;

	if (game->hitwall(newplayer_x, newplayer_y)) {
		return;
	}

	if (!game->box_updated(x, y, newplayer_x, newplayer_y)) {
		return;
	}

	pos.x = newplayer_x;
	pos.y = newplayer_y;

	posRect.x = pos.x * TILE_SIZE;
	posRect.y = pos.y * TILE_SIZE;
}

void Player::reset(int x, int y) {

	direction = 0;
	pos.x = x;
	pos.y = y;
	posRect = { pos.x * TILE_SIZE, pos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	spriteRect = { 0, 0, TILE_SIZE, TILE_SIZE };
}

void Player::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &spriteRect, &posRect);
}

void Player::set_direction(int x, int y) {
	if (x > 0) {
		direction = 0;
	}
	else if (x < 0) {
		direction = 2;
	}
	else if (y > 0) {
		direction = 1;
	}
	else if (y < 0) {
		direction = 3;
	}

	spriteRect.x = direction * TILE_SIZE;
}