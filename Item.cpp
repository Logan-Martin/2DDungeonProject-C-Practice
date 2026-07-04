#include "Item.h"

using namespace DungeonGame;

void Item::SetItemIndex(int newIndex)
{
	ItemIndex = newIndex;
}

void Item::Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState)
{
	ItemData& currItem = worldState.Items[ItemIndex];	

	if (currItem.Alive)
	{
		Vector2d vecToPlayer = currItem.Position - playerState.PlayerPosition;
		if (vecToPlayer.GetLength() < 30.0f)
		{
			currItem.Alive = false;

			playerState.ItemInventory.push_back(currItem.Type);
		}

	}
	Position = currItem.Position - Vector2d(Size.X * 0.5f, Size.Y * 0.5f);
	Visible = currItem.Alive;
}