#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Item : public Sprite
	{
	public:
		void SetItemIndex(int newIndex);

		virtual void Update(float deltaSeconds, PlayerState& playerState, WorldState& worldState);
	private:
		int ItemIndex;
	};
}