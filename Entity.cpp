#include "Entity.h"

Entity::Entity(AnimationManager& A, int X, int Y)
{
	anim = A;
	x = X;
	y = Y;
	dir = 0;
	life = true;
	timer = 0;
	timer_end = 0;
	dx = dy = 0;
}

void Entity::draw(RenderWindow& window)
{
	anim.draw(window, x, y + h);
}

FloatRect Entity::getRect()
{
	return FloatRect(x, y, w, h);
}

void Entity::option(std::string NAME, float SPEED, int HEALTH, std::string FIRST_ANIM)
{
	Name = NAME;                                
	if (FIRST_ANIM != "") anim.set(FIRST_ANIM); 
	w = anim.getW();                           
	h = anim.getH();                           
	dx = SPEED;                               
	Health = HEALTH;                            
}

float Entity::getX()
{
	return x;
}

void Entity::setX(float X)
{
	x += X;
}

float Entity::getY()
{
	return y;
}

void Entity::setY(float Y)
{
	y += Y;
}

float Entity::getH()
{
	return h;
}

float Entity::getDX()
{
	return dx;
}

void Entity::setDX(float DX)
{
    dx = DX;
}

float Entity::getDY()
{
	return dy;
}

void Entity::setDY(float DY)
{
	dy = DY;
}

int Entity::getHealth()
{
	return Health;
}

void Entity::setHealth(int h)
{
	if (h == 0) Health = h;
	else Health -= h;
}

std::string Entity::getName()
{
	return Name;
}

bool Entity::getLife()
{
	return life;
}

bool Entity::getDir()
{
	return dir;
}
