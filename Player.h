#pragma once
#include"Entity.h"

class Player :public Entity
{
public:
	enum { stay, run, slide, jump, climb, glid, attack,dead } STATE;  //������������ �������� ���������, ��������������� ��������� ���������
	bool onLadder, shoot,pause,win,one, sound;                       //�� ��������, � ����� ��� ���,�����, ������� ��� ���, ����� ��� ���,��� �� ��������, �������� ������, ������� �� ����
	std::map<std::string, bool> key;                                  //������ � ������� ��������
	int score;                                                        //���������� ��������� �����
	Sound soundJump, soundCoin;                                       //�������� ������� ������ � ����� �������
	Player(AnimationManager& A, Level& lev, int x, int y);
	~Player();
	void Keyboard();                   //���������� ��������� ��������� � ����������� �� ������� �������
	void Animation(float time);        //������ �������� � ����������� �� ���������
	void update(float time);           //�������� ��������� � ������� ������������ ���������
	void Collision(int num);           //�������� �� ����������� � ��������� �����
};

