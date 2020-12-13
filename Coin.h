#pragma once
#include "Entity.h"
class Coin :public Entity
{
public:
	Coin(AnimationManager& a, Level& lev, int x, int y);
	void update(float time);
};

