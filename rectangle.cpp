#include <SDL.h>
#undef main
#include <iostream>
#include <math.h>
#include <SDL_mixer.h>

int main() {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int FPS = 60;
	const int DELAY_TIME = 100/FPS;
	Uint32 frameStart, frameTime = 0;
	const int SCREEN_WIDTH = 1440;
	const int SCREEN_HEIGHT = 900;

	using namespace std;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0) {
		if ((window = SDL_CreateWindow("x", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) != 0) {
			if (renderer = SDL_CreateRenderer(window, -1, 0)) {
				cout << "SDL, window, and renderer: success.\n";
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) {
					cout << "SDL mixer: success\n";
				}
			}
		}

	}
	else return 0;

	SDL_Delay(1000);

	SDL_Rect topleft = { 0 };
	topleft.x = 0;
	topleft.y = 0;
	topleft.w = SCREEN_WIDTH / 2;
	topleft.h = SCREEN_WIDTH / 2;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	Mix_Chunk* birds[6] = { Mix_LoadWAV("assets/bird1.wav"), Mix_LoadWAV("assets/bird2.wav"), Mix_LoadWAV("assets/bird3.wav"), Mix_LoadWAV("assets/bird4.wav"), Mix_LoadWAV("assets/bird5.wav"), Mix_LoadWAV("assets/bird6.wav") };
	SDL_Rect recO = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, 1};	// rectangle Outer
	int size = 0, height = SCREEN_HEIGHT, width = SCREEN_WIDTH;
	unsigned count = 1;
	Uint8 r = 255, b = 255, g = 255;

	bool quit = false;
	bool reverse_s = false;	//reverse order of sounds
	bool reverse_r = false;	//reverse order of rectangle
	int scale = -4;

	while (!quit) {
		frameStart = SDL_GetTicks();

		SDL_SetRenderDrawColor(renderer, r, g, b, 0);
		SDL_RenderDrawRect(renderer, &recO);
		SDL_RenderPresent(renderer);

		recO.x = recO.x - 2;
		recO.y = recO.y - 2;
		recO.w = (3 + 4 * size);
		recO.h = (3 + 4 * size);

		size++;

		if (recO.x <= 0 || recO.y <= 0 || recO.w >= width || recO.h >= height) {	//loop with differnt color
			if (!reverse_s) Mix_PlayChannel(-1, birds[count % 6], 1);
			else Mix_PlayChannel(-1, birds[5 - (count % 6)], 1);

			if (count !=0 && count % 6 == 0) reverse_s = !reverse_s;

			recO.x = SCREEN_WIDTH / 2;
			recO.y = SCREEN_HEIGHT / 2;
			recO.w = 1;
			recO.h = 1;
			size = 0;

			height += scale;
			width += scale;

			switch (count % 6) {
			case 0:
				r = 255;
				g = 0;
				b = 0;
				break;
			case 1:
				r = 0;
				g = 255;
				b = 0;
				break;
			case 2:
				r = 0;
				g = 0;
				b = 255;
				break;
			case 3:
				r = 255;
				g = 255;
				b = 0;
				break;
			case 4:
				r = 255;
				g = 0;
				b = 255;
				break;
			case 5:
				r = 0;
				g = 255;
				b = 255;
				break;
			default:
				break;
			}

			if (height <= 1 || height >= SCREEN_HEIGHT || width <= 1 || width >= SCREEN_WIDTH) {	// restart loop
				if (reverse_r) {
					height = SCREEN_HEIGHT;
					width = SCREEN_WIDTH;
					scale = -4;
					reverse_r = false;
				}
				else {
					height = 1;
					width = 1;
					scale = 4;
					size = 0;
					reverse_r = true;
				}
			}

			count++;
		}

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)DELAY_TIME - frameTime);
		}
	}

	Mix_FreeChunk(*birds);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}