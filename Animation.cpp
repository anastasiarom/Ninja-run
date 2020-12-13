#include "Animation.h"

Animation::Animation()
{
	currentFrame = 0;
	isPlaying = true;
	flip = false;
	loop = true;
}
void Animation::tick(float time)           //смена кадров в анимации
{
	if (!isPlaying)return;
	currentFrame += speed * time;

	if (currentFrame > frames.size())   //если за пределами количества кадров
	{
		currentFrame -= frames.size();
		if (!loop) 
		{ 
			isPlaying = false; 
			return; 
		}
	}
	int i = currentFrame;                         //выставление текущего кадра
	if (flip) sprite.setTextureRect(frames_flip[i]);
	else
		sprite.setTextureRect(frames[i]);
}

