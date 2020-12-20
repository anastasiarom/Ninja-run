#include "Coin.h"

Coin::Coin(AnimationManager& a, Level& lev, int x, int y) :Entity(a, x, y)
{
	option("Coin", 0, 1, "move");
}

void Coin::update(float time)
{
	if (Health <= 0) life = false;
	anim.tick(time);
}