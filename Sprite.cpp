#include "Sprite.h"
#include <string>

using namespace DungeonGame;

std::vector<Sprite::LoadedTexture> Sprite::s_LoadedTextures;

Sprite::Sprite() :
	MyTexture(nullptr),
	Position(0.0f,0.0f),
	Size(64.0f,64.0f),
	Visible(true)
{
}

void Sprite::Initialize(SDL_Renderer* pRenderer, const std::string& imageFilepath)
{
	MyTexture = LoadTexture(pRenderer, imageFilepath);
}

void Sprite::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
}

void Sprite::Render(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState, const Vector2d& baseTranslation)
{
	if (Visible && MyTexture != nullptr )
	{
		SDL_Rect destRect = { (int)Position.X + (int)baseTranslation.X , (int)Position.Y + (int)baseTranslation.Y , (int)Size.X, (int)Size.Y };
		SDL_RenderCopy(pRenderer, MyTexture, nullptr, &destRect);
	}
}

void Sprite::CleanUp()
{
}

void Sprite::CleanUpTextures()
{
	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++)
	{
		SDL_DestroyTexture(s_LoadedTextures[i].Texture);
	}
	s_LoadedTextures.clear();
}


SDL_Texture* Sprite::LoadTexture(SDL_Renderer* pRenderer, const std::string& imageFilepath)
{

	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++)
	{
		if (s_LoadedTextures[i].Filename == imageFilepath)
		{
			return s_LoadedTextures[i].Texture;
		}
	}

	SDL_Surface* pBmp = SDL_LoadBMP(imageFilepath.c_str());
	SDL_SetColorKey(pBmp, SDL_TRUE, SDL_MapRGB(pBmp->format, 0, 255, 0));
	SDL_Texture* retTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp);

	LoadedTexture loadedTexture = { imageFilepath , retTexture};
	s_LoadedTextures.push_back(loadedTexture);

	return retTexture;
}


