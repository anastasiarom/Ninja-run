#pragma once
#include"Entity.h"

class MovingPlatform : public Entity
{
public:
	MovingPlatform(AnimationManager& a, Level& lev, int x, int y);
	void update(float time);
};

