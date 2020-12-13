#include "Animation.h"

Animation::Animation()
{
	currentFrame = 0;
	isPlaying = true;
	flip = false;
	loop = true;
}
void Animation::tick(float time)           //����� ������ � ��������
{
	if (!isPlaying)return;
	currentFrame += speed * time;

	if (currentFrame > frames.size())   //���� �� ��������� ���������� ������
	{
		currentFrame -= frames.size();
		if (!loop) 
		{ 
			isPlaying = false; 
			return; 
		}
	}
	int i = currentFrame;                         //����������� �������� �����
	if (flip) sprite.setTextureRect(frames_flip[i]);
	else
		sprite.setTextureRect(frames[i]);
}

