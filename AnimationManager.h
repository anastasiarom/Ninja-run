#pragma once
#include"lib.h"
#include "Animation.h"

class AnimationManager
{
private:
	std::string currentAnim;                        //имя текущей анимации
	std::map<std::string, Animation> animList;      //массив из анимаций
public:
	~AnimationManager();
	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step, bool Loop ); //создание анимаций вручную
	void loadFromXML(std::string fileName, Texture& image);    //загрузка анимации из xml файла
	void draw(RenderWindow& window, int x, int y);             //вывод на экран текущей анимации в координаты x,y
	void set(std::string name);                                //смена анимации
	void flip(bool b = 1);                                     //смена текущей анимации на зеркальную
	void tick(float time);                                     //смена кадров в анимации
	void pause();                                              //остановка анимации
	void play();                                               //продолжить анимацию
	void play(std::string name);                               //продолжить анимацию
	float getH();                                              //возвращает высоту текущего кадра
	float getW();                                              //возвращает ширину текущего кадра
	void loop(bool, std::string);                              //устанавливает зацикливается ли конкретная анимация
};

