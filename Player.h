#pragma once
#include"Entity.h"

class Player :public Entity
{
public:
	enum { stay, run, slide, jump, climb, glid, attack,dead } STATE;  //перечисление состо€ий персонажа, соответствующих имеющимс€ анимаци€м
	bool onLadder, shoot,pause,win,one, sound;                       //на лестнице, в атаке или нет,пауза, выиграл или нет, пауза или нет,был ли проигран, звуковой эффект, включЄн ли звук
	std::map<std::string, bool> key;                                  //данные о нажатых клавишах
	int score;                                                        //количество собранных монет
	Sound soundJump, soundCoin;                                       //звуковые эффекты прыжка и сбора монеток
	Player(AnimationManager& A, Level& lev, int x, int y);
	~Player();
	void Keyboard();                   //определ€ет состо€ние персонажа в зависимости от нажатой клавиши
	void Animation(float time);        //мен€ет анимацию в зависимости от состо€ни€
	void update(float time);           //измен€ет положение в игровом пространстве персонажа
	void Collision(int num);           //проверка на пересечение с объектами карты
};

