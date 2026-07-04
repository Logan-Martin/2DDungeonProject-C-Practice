#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "GameCore.h"

using namespace DungeonGame;

int main() 
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* pWindow = SDL_CreateWindow("Dungeon Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	PlayerState playerState = {};
	WorldState worldState = {};

	InitializeGame(pRenderer, playerState, worldState);

	int frameStartTicks, frameEndTicks = 0;
	int deltaTicks = 0;


	while (!playerState.hasFinishedGame) {

		if (deltaTicks < 1 )
		{
			frameStartTicks = SDL_GetTicks();
			SDL_Delay(1);
			frameEndTicks = SDL_GetTicks();
			deltaTicks = frameEndTicks - frameStartTicks;
		}

		frameStartTicks = SDL_GetTicks();

		GetInput(playerState, worldState);

		float deltaSeconds = (float)deltaTicks / 1000.0f;
		UpdateGame(deltaSeconds, playerState, worldState);
		RenderGame(pRenderer, playerState, worldState);

		frameEndTicks = SDL_GetTicks();
		deltaTicks = frameEndTicks - frameStartTicks;
	}

	CleanupGame(playerState, worldState);

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	return 0;
}
