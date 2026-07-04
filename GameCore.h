#pragma once
#include "SDL.h"
#include <string>
#include <vector>

namespace DungeonGame
{

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{
		}

		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{
		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d& rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d& rhs) const 
		{
			return Vector2d(*this) += rhs;
		}

		Vector2d& operator-=(const Vector2d& rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d& rhs) const
		{
			return Vector2d(*this) -= rhs;
		}

		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}

		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f) 
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}


	};

	enum ItemType
	{
		Item_FOOD,
		Item_KNIFE
	};


	struct PlayerState
	{
		bool hasFinishedGame;

		bool WantsToGoUP;
		bool WantsToGoDown;
		bool WantsToGoLeft;
		bool WantsToGoRight;
		// new -7/4/2026:
		bool isSprinting;
		float WalkSpeed_DEFAULT = 150.0f;
		float WalkSpeed_RUNNING = WalkSpeed_DEFAULT * 1.5f;
		float WalkSpeed_CURR;

		Vector2d PlayerPosition;
		std::vector<ItemType> ItemInventory;
	};


	struct ItemData
	{
		bool Alive;
		ItemType Type;
		Vector2d Position;
	};

	struct WorldState 
	{
		int TilesPerRow;
		std::string Tiles;
		Vector2d TileSizeInPixels;

		Vector2d CameraPosition;


		std::vector<ItemData> Items;


		bool IsWalkableTile(const Vector2d& inPosition);
	};

	void InitializeGame(SDL_Renderer* pRenderer, PlayerState& playerState, WorldState& worldState);

	void GetInput(PlayerState& playerState, const WorldState& worldState);
	void UpdateGame(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	void RenderGame(SDL_Renderer* pRenderer, const PlayerState& playerState, const WorldState& worldState);

	void CleanupGame(PlayerState& playerState, WorldState& worldState);

}