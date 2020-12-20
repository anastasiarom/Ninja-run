#include "Enemy.h"

Enemy:: Enemy(AnimationManager& a, Level& lev, int x, int y) :Entity(a, x, y)
{
	option("Enemy", 0.03, 15, "move");
}

void Enemy:: update(float time)
{
	x += dx * time;
	timer += time;
	if (timer > 7000)
	{ 
		dx *= -1;
		timer = 0;
		if (dx < 0) anim.flip(1);
		else anim.flip(0);
	}
	if (Health <= 0) 
	{
		anim.set("dead"); dx = 0;
		y += dy * time;
		timer_end += time;
		if (timer_end > 4000) life = false;
	}
	anim.tick(time);
}