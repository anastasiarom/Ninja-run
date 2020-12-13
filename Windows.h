#pragma once
#include"Level.h"

class Windows
{
public:
	std::map<std::string, Level> windows;                 //асоциативный массив с окнами GUI
	std::string currentWindow;                            //имя текущего окна
	bool click, isGame, restart, start, end, sound;       //нажата ли кнопка, находится ли пользователь в процессе игры, запущен ли уровень заново, происходит ли запуск сначала, закончен ли уровень, есть ли звук 
	int score;                                            //количество монеток собранных за уровень
	int lvl;                                              //номер уровня
	Windows();
	~Windows();
	void loadAllWindows();                                //загружаем окна GUI в асоциативный массив
	void checkClick(RenderWindow& window, Windows& W);    //проверяет какая кнопка нажата
	void setWindow(std::string name);                     //смена текущего окна
};

