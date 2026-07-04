#include "RoomRenderer.h"

using namespace DungeonGame;

void RoomRenderer::InitializeRoomTiles(SDL_Renderer* pRenderer, const std::string& floorFilepath, const std::string& wallFilepath)
{
	FloorTexture = LoadTexture(pRenderer, floorFilepath);
	WallTexture = LoadTexture(pRenderer, wallFilepath);
}

void RoomRenderer::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{

	int columnsRendered = 0;
	int rowsRendered = 0;

	for (unsigned int i = 0; i < worldState.Tiles.size(); ++i)
	{
		char currentTile = worldState.Tiles[i];

		switch (currentTile)
		{
		case '#':
			MyTexture = WallTexture;
			break;
		case '.':
			MyTexture = FloorTexture;
			break;
		default:
			MyTexture = nullptr;
			break;
		}


		if (MyTexture != nullptr)
		{
			SDL_Rect destRect = { 
				columnsRendered * (int)worldState.TileSizeInPixels.X + (int)baseTranslation.X ,
				rowsRendered * (int)worldState.TileSizeInPixels.Y + (int)baseTranslation.Y ,
				(int)worldState.TileSizeInPixels.X,
				(int)worldState.TileSizeInPixels.Y };
			SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
		}

		columnsRendered++;
		if (columnsRendered % worldState.TilesPerRow == 0 )
		{
			rowsRendered++;
			columnsRendered = 0;
		}

	}

}
