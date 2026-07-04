#include "GameCore.h"
#include "Sprite.h"
#include <string>
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"

namespace DungeonGame 
{
	std::vector<Sprite*> SpriteList;
	
	bool WorldState::IsWalkableTile(const Vector2d& inPosition)
	{
		int column = (int)(inPosition.X / TileSizeInPixels.X);
		int row = (int)(inPosition.Y / TileSizeInPixels.Y);

		char currentTile = ' ';
		int index = row * TilesPerRow + column;

		if (index >= 0 && index < (int)Tiles.size() )
		{
			currentTile = Tiles[index];
		}

		return currentTile == '.';
	}


	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState)
	{
		playerState.hasFinishedGame = false;

		playerState.WantsToGoUP = false;
		playerState.WantsToGoDown = false;
		playerState.WantsToGoLeft = false;
		playerState.WantsToGoRight = false;
		//
		playerState.isSprinting = false;
		playerState.WalkSpeed_CURR = playerState.WalkSpeed_DEFAULT;


		worldState.TilesPerRow = 8;
		worldState.TileSizeInPixels = Vector2d(64.0f, 64.0f);
		worldState.Tiles =
			" ###### "
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			"#......#"
			" ###### "
			;

		worldState.Items.push_back({true, Item_FOOD, Vector2d(3.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y)});
		worldState.Items.push_back({true, Item_FOOD, Vector2d(3.0f * worldState.TileSizeInPixels.X, 8.0f * worldState.TileSizeInPixels.Y) });
		worldState.Items.push_back({ true, Item_KNIFE, Vector2d(4.0f * worldState.TileSizeInPixels.X, 10.0f * worldState.TileSizeInPixels.Y) });


		RoomRenderer* roomRenderer = new RoomRenderer;
		roomRenderer->InitializeRoomTiles(pRenderer, "Assets/GrassTile.bmp", "Assets/TreeBoarder.bmp");
		SpriteList.push_back(roomRenderer);

		Hero* newHero = new Hero;
		newHero->Initialize(pRenderer, "Assets/plrSpriteWalkDown.bmp");
		newHero->Size = Vector2d(128.0f, 128.0f);
		playerState.PlayerPosition = Vector2d(4.0f * worldState.TileSizeInPixels.X, 3.0f * worldState.TileSizeInPixels.Y);
		//newHero->Position = Vector2d(4.0f * worldState.TileSizeInPixels.X , 3.0f * worldState.TileSizeInPixels.Y );
		SpriteList.push_back(newHero);


		for (unsigned int i = 0; i < worldState.Items.size(); ++i )
		{
			std::string ItemFilepath = "Assets/Food1.bmp";
			switch (worldState.Items[i].Type)
			{
			case Item_FOOD : 
				ItemFilepath = "Assets/Food1.bmp";
				break;
			case Item_KNIFE :
				ItemFilepath = "Assets/Knife.bmp";
				break;
			}

			Item* newItem = new Item;
			newItem->Initialize(pRenderer, ItemFilepath);
			newItem->SetItemIndex(i);
			SpriteList.push_back(newItem);
		}

		//Sprite* newSprite2 = new Sprite;
		//newSprite2->Initialize(pRenderer, "Assets/Food1.bmp");
		//newSprite2->Position = Vector2d(100.0f, 220.0f);
		//newSprite2->Size = Vector2d(64.0f,64.0f);
		//SpriteList.push_back(newSprite2);
	}

	void GetInput(PlayerState& playerState, const WorldState& worldState)
	{
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0 ) 
		{
			if (e.type == SDL_QUIT)
			{
				playerState.hasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN )
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.hasFinishedGame = true;
					break;

				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUP = true;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = true;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = true;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = true;
					break;
				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					playerState.isSprinting = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_w:
				case SDLK_UP:
					playerState.WantsToGoUP = false;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					playerState.WantsToGoDown = false;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					playerState.WantsToGoLeft = false;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					playerState.WantsToGoRight = false;
					break;

				case SDLK_LSHIFT:
				case SDLK_RSHIFT:
					playerState.isSprinting = false;
					break;
				}
			}

		}
	}

	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
	{
		//testDistance.Normalize();
		//testSprite.Position += testDistance * 50.0f * deltaSeconds;

		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Update(deltaSeconds, playerState, worldState);
		}

	}

	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState)
	{
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->Render(pRenderer, playerState, worldState,  Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - worldState.CameraPosition);
		}

		SDL_RenderPresent(pRenderer);

	}

	void CleanupGame(PlayerState& playerState, WorldState& worldState)
	{
		for (unsigned int i = 0; i < SpriteList.size(); ++i)
		{
			SpriteList[i]->CleanUp();
			delete SpriteList[i];
		}
		SpriteList.clear();

		Sprite::CleanUpTextures();
	}
}