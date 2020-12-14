#pragma once
#include"AnimationManager.h"
#include"Level.h"

class Entity
{
protected:
	float x, y, dx, dy, w, h;    //�, �, w, h ������ �������������� ��������, dx, dy �������� �� x � y 
	AnimationManager anim;       //��� ������ � ��������� ������������� �������
	std::vector<Object> obj;     //������ � ��������� �����
	bool life, dir;  //�����, ������(0)(��� ����� (1))
	float timer, timer_end;
	std::string Name;     //��� ��������
	int Health;  //���������� ������
public:
	Entity(AnimationManager& A, int X, int Y);
	virtual void update(float time) = 0;   //�������� ��������� � ������� ������������ ������������� ������� 
	void draw(RenderWindow& window);       //����� �������� �� �����
	FloatRect getRect();                   //���������� ������������� ��������
	void option(std::string NAME, float SPEED = 0, int HEALTH = 10, std::string FIRST_ANIM = "");  //������������� �������� ��������� ������������� �������
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

