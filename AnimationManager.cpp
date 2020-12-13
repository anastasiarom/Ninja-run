#include "AnimationManager.h"


AnimationManager::~AnimationManager()
{
	animList.clear();
}

void AnimationManager::create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step, bool Loop)
{
	Animation a;
	a.speed = speed;
	a.loop = Loop;
	a.sprite.setTexture(texture);
	a.sprite.setOrigin(0, h);

	for (int i = 0; i < count; i++)
	{
		a.frames.push_back(IntRect(x + i * step, y, w, h));
		a.frames_flip.push_back(IntRect(x + i * step + w, y, -w, h));
	}
	animList[name] = a;
	currentAnim = name;
}
void AnimationManager::loadFromXML(std::string fileName, Texture& image)
{
	TiXmlDocument animFile(fileName.c_str());

	animFile.LoadFile();

	TiXmlElement* head;
	head = animFile.FirstChildElement("sprites");

	TiXmlElement* animElement;
	animElement = head->FirstChildElement("animation");
	while (animElement)
	{
		Animation anim;
		currentAnim = animElement->Attribute("title");
		int delay = atoi(animElement->Attribute("delay"));
		anim.speed = 1.0 / delay;
		anim.sprite.setTexture(image);

		TiXmlElement* cut;
		cut = animElement->FirstChildElement("cut");
		while (cut)
		{
			int x = atoi(cut->Attribute("x"));
			int y = atoi(cut->Attribute("y"));
			int w = atoi(cut->Attribute("w"));
			int h = atoi(cut->Attribute("h"));

			anim.frames.push_back(IntRect(x, y, w, h));
			anim.frames_flip.push_back(IntRect(x + w, y, -w, h));
			cut = cut->NextSiblingElement("cut");
		}

		anim.sprite.setOrigin(0, anim.frames[0].height);

		animList[currentAnim] = anim;
		animElement = animElement->NextSiblingElement("animation");
	}
}
void AnimationManager::draw(RenderWindow& window, int x = 0, int y = 0)      //����� �� ����� ������� �������� � ���������� x,y
{
	animList[currentAnim].sprite.setPosition(x, y);
	window.draw(animList[currentAnim].sprite);
}
void AnimationManager::set(std::string name)
{
	currentAnim = name;
	animList[currentAnim].flip = 0;
}
void AnimationManager::flip(bool b) { animList[currentAnim].flip = b; }

void AnimationManager::tick(float time) { animList[currentAnim].tick(time); }

void AnimationManager::pause() { animList[currentAnim].isPlaying = false; }

void AnimationManager::play() { animList[currentAnim].isPlaying = true; }

void AnimationManager::play(std::string name) { animList[name].isPlaying = true; }

bool AnimationManager::isPlaying() { return animList[currentAnim].isPlaying; }

float AnimationManager::getH() { return animList[currentAnim].frames[0].height; }

float AnimationManager::getW() { return animList[currentAnim].frames[0].width; }

void AnimationManager::loop(bool l, std::string name) { animList[name].loop = l; }