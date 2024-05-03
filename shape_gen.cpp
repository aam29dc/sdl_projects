#include <SDL.h>
#undef main
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int WIDTH = 800;
const int HEIGHT = 800;

/* generate a shape with a number of sides 
* \param num the number of sides
* \param x the center of the x position
* \param y the center of the y position
* \param rad the width of the shape
* \param rot the rotation of the shape
* \returns void
*/
void drawShape(const unsigned int num, const int x = 0, const int y = 0,
	const unsigned int rad = 10, const float rot = 0.0f) {

	SDL_Point pt = { 0 }, pt2 = { 0 };

	unsigned int n = 1;

	pt.x = (int)(rad * cos(0+rot)) + x;
	pt.y = (int)(rad * sin(0+rot)) + y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	while (n <= num) {
		pt2.x = (int)(rad * cos(((n*2*M_PI)/num) + rot)) + x;
		pt2.y = (int)(rad * sin(((n*2*M_PI)/num) + rot)) + y;

		SDL_RenderDrawLine(renderer, pt.x, pt.y, pt2.x, pt2.y);

		pt.x = pt2.x;
		pt.y = pt2.y;
		n++;
	}
}

/* generate shape with lines going from every point
* \param num the number of sides
* \param x the x offset of the center
* \param y the y offset of the center
* \param rad the radius or size of the shape
* \param rot the rotation of the shape
* \returns void
*/
void drawLinedShape(const unsigned int num, const int x = 0, const int y = 0,
	const unsigned int rad = 10, const float rot = 0.0f) {

	SDL_Point pt = { 0 }, pt2 = { 0 };

	pt.x = (int)(rad * cos(0 + rot)) + x;
	pt.y = (int)(rad * sin(0 + rot)) + y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (unsigned n = 1; n <= num; n++) {
		pt.x = (int)(rad * cos(((n * 2 * M_PI) / num) + rot)) + x;
		pt.y = (int)(rad * sin(((n * 2 * M_PI) / num) + rot)) + y;
		for (unsigned m = n+1; m <= num; m++) {
			pt2.x = (int)(rad * cos(((m * 2 * M_PI) / num) + rot)) + x;
			pt2.y = (int)(rad * sin(((m * 2 * M_PI) / num) + rot)) + y;
			SDL_RenderDrawLine(renderer, pt.x, pt.y, pt2.x, pt2.y);
		}
	}
}

int main() {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer)) {

		}
	}

	int n = 1;
	int dir = 1;
	float rot = 0;
	float r_dir = 1;

	while (true) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		drawLinedShape(n, WIDTH / 2, HEIGHT / 2, 400, rot);
		drawLinedShape(n, WIDTH / 2, HEIGHT / 2, 400 / 2, rot);

		SDL_RenderPresent(renderer);

		SDL_Delay(2000);
		n += dir;
		rot = rot + (float)r_dir*0.1f;

		if (rot >= 2 * M_PI || rot <= 0) {
			r_dir = -r_dir;
		}

		if (n == 30 || n == 0) {
			dir = -dir;
		}
	}

	return 0;
}