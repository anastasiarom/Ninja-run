#include "Player.h"

Player::Player(AnimationManager& A, Level& lev, int x, int y) :Entity(A, x, y)
{
	option("Player", 0, 100, "stay");
	STATE = stay; 
	obj = lev.GetAllObjects();
	score = 0;
	onLadder=shoot=pause=win=one=false;
	sound = true;
}

Player::~Player()
{
	key.clear();
}

void Player::Keyboard()      
{
	if (key["L"])
	{
		dir = 1;
		if (STATE != slide && STATE != attack&&STATE!=dead) dx = -0.15;
		if (STATE == slide) dx = -0.05;
		if (STATE == stay) STATE = run;
	}
	if (key["R"])
	{
		dir = 0;
		if (STATE != slide && STATE != attack&&STATE != dead) dx = 0.15;
		if (STATE == slide) dx = 0.05;
		if (STATE == stay) STATE = run;
	}
	if (key["Up"])
	{
		if (onLadder) STATE = climb;
		if (STATE == stay || STATE == run) 
		{ 
			dy = -0.38; 
			STATE = jump; 
			anim.play("jump"); 
		}
		if (STATE == climb) dy = -0.05;
	}
	if (key["Down"])
	{
		if (STATE == stay || STATE == run) STATE = slide; 
		if (STATE == climb) dy = 0.05;
	}
	if (key["Space"])
	{
		STATE = attack;
		shoot = true;
	}	
	if (key["Esc"]) pause = true;
	/////////////////////если клавиша отпущена///////////////////////////
	if (!(key["R"] || key["L"]))
	{
		dx = 0;
		if (STATE == run) STATE = stay;
	}
	if (!(key["Up"] || key["Down"]))
		if (STATE == climb) dy = 0;
	if (!key["Down"])
		if (STATE == slide) STATE = stay; 
	if (!key["Space"])
	{
		if (STATE == attack) STATE = stay;
		shoot = false;
	}	
	if (!key["Esc"]) pause = false;
	key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] =key["Esc"]= false;
}

void Player::Animation(float time)        
{
	if (STATE == stay) anim.set("stay");
	if (STATE == run) anim.set("run");
	if (STATE == jump)
	{
		anim.set("jump");
		if (!one&&sound) soundJump.play();
		one = true;
	}
	else one = false;
	if (STATE == slide) anim.set("slide");
	if (STATE == climb)
	{
		anim.set("climb");
		anim.pause();
		if (dy != 0) anim.play();
	}
	if (STATE == attack) anim.set("attack");
	if (Health<=0)
	{
		STATE = dead;
		dx = 0;
		anim.set("dead");
	}
	if (dir&&STATE!=dead) anim.flip();
	anim.tick(time);  
}

void Player::update(float time)                  //перемещение персонажа  (изменение координат х и у)
{
	Keyboard();
	Animation(time);
	if (STATE == climb) 
		if (!onLadder) STATE = stay;
	if (STATE != climb) dy += 0.0005 * time;     //сила притяжения, если мы не на лестнице
	onLadder = false;
	x += dx * time;               //перемещение по x                              
	Collision(0);                 //проверка на столкновение
	y += dy * time;               //перемещение по y
	Collision(1);                 //проверка на столкновение
}

void Player::Collision(int num)
{
	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (dy > 0 && num == 1) 
				{ 
					y = obj[i].rect.top - h;  
					dy = 0;   
					STATE = stay; 
				}
				if (dy < 0 && num == 1) 
				{ 
					y = obj[i].rect.top + obj[i].rect.height;   
					dy = 0; 
				}
				if (dx > 0 && num == 0) 
					x = obj[i].rect.left - w; 
				if (dx < 0 && num == 0) 
					x = obj[i].rect.left + obj[i].rect.width; 
			}
			if (obj[i].name == "ladder") 
			{ 
				onLadder = true; 
				if (STATE == climb) 
					x = obj[i].rect.left;  
			}
		    if (obj[i].name == "water"|| obj[i].name == "stake")
			{
				STATE = dead;		
				y = obj[i].rect.top + obj[i].rect.height - h;
				dy = 0;
				Health = 0;
			}
			if (obj[i].name == "top"&& y < obj[i].rect.top - 50) 
			{ 
				y = obj[i].rect.top + obj[i].rect.height - h;   
				dy = 0; 
				STATE = stay; 
			}
			if (obj[i].name == "win") win = true;
		}
}