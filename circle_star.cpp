<SDL.h>
#undef main
#include <iostream>
#include "game.hpp"
#include <SDL_image.h>
#include <fstream>

#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool createTexture(SDL_Texture* tex, const std::string file) {
	SDL_Surface* surf;
	if ((surf = IMG_Load(file.c_str())) == NULL) {
		return false;
	}

	if ((tex = SDL_CreateTextureFromSurface(renderer, surf)) == NULL) {
		return false;
	}

	SDL_FreeSurface(surf);

	return true;
}

const int HEIGHT = 1024;
const int WIDTH = 1024;

void negateColor(SDL_Color* c) {
	if (c->r == 0) c->r = 255;
	else c->r = 255 - c->r;

	if (c->g == 0) c->g = 255;
	else c->g = 255 - c->g;

	if (c->b == 0) c->b = 255;
	else c->b = 255 - c->b;
	SDL_SetRenderDrawColor(renderer, c->r, c->g, c->b, 255);
}

#include <cmath>

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN, &window, &renderer)) {

		}
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Point pt = { 0 };

	const int r = (1024 / 2) + (1024 / 4);
	const int sx = WIDTH / 2;
	const int sy = HEIGHT / 2;
	int shift = 1;
	int dir = 1;
	int n = 0;
	int m = 0;

	SDL_Color c = { 255,255,255,255 };

	SDL_Point circle = { 0 };
	circle.x = 0;
	circle.y = 0;
	int circleR = 0;

	SDL_Rect cent = { 0 };
	cent.x = (WIDTH / 2) - 100;
	cent.y = (HEIGHT / 2) - 100;
	cent.w = 200;
	cent.h = 200;

	SDL_RenderSetClipRect(renderer, &cent);

	while (true) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		while (n <= 150) {
			pt.x = sin(n) * r;
			pt.y = cos(n) * r;
			SDL_RenderDrawLine(renderer, sx + circle.x, sy + circle.y, pt.x + sx, pt.y + sy);
			SDL_RenderDrawLine(renderer, sx - circle.x, sy - circle.y, pt.x + sx, pt.y + sy);
			n++;
		}
		n = 0;
		circle.x = (sin(m) * circleR);
		circle.y = (cos(m) * circleR);
		m++;
		circleR += dir;
		if (circleR == 0 || circleR == 400) dir = -dir;

		SDL_RenderPresent(renderer);
		SDL_Delay(10);

	}
	while (true);

	return 0;
}