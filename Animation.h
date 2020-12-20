#pragma once
#include"lib.h"

class Animation
{
private:
	std::vector<IntRect>frames, frames_flip; // ������ ������, � ������ ������������ ������ ��� ���������� ��������
	double currentFrame, speed;              //������� ����,��������
	bool loop, flip, isPlaying;              //��������� �������� ��� ���, ���������� ��� ���, ����������� �������� ��� ���
	Sprite sprite;
public:
	Animation();
	void tick(float time);                   //����� ������ � ��������
	friend class AnimationManager;
};

