#pragma once
#include"lib.h"

class Animation
{
private:
	std::vector<IntRect>frames, frames_flip; // массив кадров, и массив перевернутых кадров для зеркальной анимации
	double currentFrame, speed;              //текущий кадр,скорость
	bool loop, flip, isPlaying;              //зациклена анимация или нет, зеркальный или нет, проигрывать анимацию или нет
	Sprite sprite;
public:
	Animation();
	void tick(float time);                   //смена кадров в анимации
	friend class AnimationManager;
};

