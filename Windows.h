#pragma once
#include"Level.h"

class Windows
{
public:
	std::map<std::string, Level> windows;                 //������������ ������ � ������ GUI
	std::string currentWindow;                            //��� �������� ����
	bool click, isGame, restart, start, end, sound;       //������ �� ������, ��������� �� ������������ � �������� ����, ������� �� ������� ������, ���������� �� ������ �������, �������� �� �������, ���� �� ���� 
	int score;                                            //���������� ������� ��������� �� �������
	int lvl;                                              //����� ������
	Windows();
	~Windows();
	void loadAllWindows();                                //��������� ���� GUI � ������������ ������
	void checkClick(RenderWindow& window, Windows& W);    //��������� ����� ������ ������
	void setWindow(std::string name);                     //����� �������� ����
};

