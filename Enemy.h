#pragma once
#include "Entity.h"
class Enemy :public Entity
{
public:
	Enemy(AnimationManager& a, Level& lev, int x, int y);
	void update(float time);
};

