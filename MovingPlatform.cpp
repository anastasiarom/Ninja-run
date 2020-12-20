#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(AnimationManager& a, Level& lev, int x, int y) :Entity(a, x, y)
{
	option("MovingPlatform", 0.05, 0, "move");
}

void MovingPlatform::update(float time)
{
	x += dx * time;
	timer += time;
	if (timer > 6000) 
	{ 
		dx *= -1; 
		timer = 0; 
	}
	anim.tick(time);
}