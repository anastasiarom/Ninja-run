#pragma once
#include"lib.h"
#include "Animation.h"

class AnimationManager
{
private:
	std::string currentAnim;                        //��� ������� ��������
	std::map<std::string, Animation> animList;      //������ �� ��������
public:
	~AnimationManager();
	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step, bool Loop ); //�������� �������� �������
	void loadFromXML(std::string fileName, Texture& image);    //�������� �������� �� xml �����
	void draw(RenderWindow& window, int x, int y);             //����� �� ����� ������� �������� � ���������� x,y
	void set(std::string name);                                //����� ��������
	void flip(bool b = 1);                                     //����� ������� �������� �� ����������
	void tick(float time);                                     //����� ������ � ��������
	void pause();                                              //��������� ��������
	void play();                                               //���������� ��������
	void play(std::string name);                               //���������� ��������
	float getH();                                              //���������� ������ �������� �����
	float getW();                                              //���������� ������ �������� �����
	void loop(bool, std::string);                              //������������� ������������� �� ���������� ��������
};

