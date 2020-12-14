#pragma once
#include"AnimationManager.h"
#include"Level.h"

class Entity
{
protected:
	float x, y, dx, dy, w, h;    //х, у, w, h данные прямоугольника анимации, dx, dy скорость по x и y 
	AnimationManager anim;       //для работы с анимацией динамического объекта
	std::vector<Object> obj;     //массив с объектами карты
	bool life, dir;  //жизнь, вправо(0)(или влево (1))
	float timer, timer_end;
	std::string Name;     //имя анимации
	int Health;  //количество жизней
public:
	Entity(AnimationManager& A, int X, int Y);
	virtual void update(float time) = 0;   //изменяет положение в игровом пространстве динамического объекта 
	void draw(RenderWindow& window);       //вывод анимации на экран
	FloatRect getRect();                   //возвращает прямоугольник анимации
	void option(std::string NAME, float SPEED = 0, int HEALTH = 10, std::string FIRST_ANIM = "");  //устанавливаем основные параметры динамического объекта
	float getX();
	void setX(float);
	float getY();
	void setY(float);
	float getH();
	float getDX();
	void setDX(float);
	float getDY();
	void setDY(float);
	int getHealth();
	void setHealth(int);
	std::string getName();
	bool getLife();
	bool getDir();
};

