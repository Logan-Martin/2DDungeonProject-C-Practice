#include "Hero.h"

using namespace DungeonGame;

void Hero::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState) 
{
	Vector2d direction(0.0f, 0.0f);
	if (playerState.WantsToGoUP)
	{
		direction.Y = -1.0f;
	}
	else if (playerState.WantsToGoDown)
	{
		direction.Y = 1.0f;
	}

	if (playerState.WantsToGoLeft)
	{
		direction.X = -1.0f;
	}
	else if (playerState.WantsToGoRight)
	{
		direction.X = 1.0f;
	}
	direction.Normalize();

	Vector2d newPosition = playerState.PlayerPosition;

	// Speed check:
	if (playerState.isSprinting == true) {
		playerState.WalkSpeed_CURR = playerState.WalkSpeed_RUNNING;
	}
	else {
		playerState.WalkSpeed_CURR = playerState.WalkSpeed_DEFAULT;
	}
	//
	newPosition += direction * playerState.WalkSpeed_CURR * deltaSeconds;

	if (worldState.IsWalkableTile(newPosition))
	{
		playerState.PlayerPosition = newPosition;
	}

	worldState.CameraPosition = playerState.PlayerPosition;

	Position = playerState.PlayerPosition - Vector2d(Size.X * 0.5f , Size.Y * 0.85f );
}