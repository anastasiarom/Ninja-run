#include "Windows.h"

Windows::Windows()
{
	currentWindow = "start";
	click = isGame = restart = start = end = false;
	sound = true;
}

Windows::~Windows()
{
	windows.clear();
}

void Windows::loadAllWindows()
{
	windows["start"].LoadFromFile("files/start.tmx", "files/start.png");
	windows["level"].LoadFromFile("files/select.tmx", "files/select.png");
	windows["setup"].LoadFromFile("files/setup.tmx", "files/setup.png");
	windows["pause"].LoadFromFile("files/pause.tmx", "files/pause.png");
	windows["fail"].LoadFromFile("files/fail.tmx", "files/fail.png");
	windows["victory"].LoadFromFile("files/victory.tmx", "files/victory.png");
}

void Windows::setWindow(std::string name)
{
	currentWindow = name;
}

void Windows::checkClick(RenderWindow& window, Windows& W)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	if(click)
	{
		std::vector<Object> obj;
		obj = windows[currentWindow].GetAllObjects();
		for (int i = 0; i < obj.size(); i++)
			if(obj[i].rect.contains(pixelPos.x, pixelPos.y))
			{
				if (obj[i].name == "play") setWindow("level");
				if (obj[i].name == "setup")
				{
					isGame = false;
					restart = false;
					start = false;
					end = false;
					setWindow("setup");
				}
				if (obj[i].name == "sound")
				{
					if(sound==true) sound = false;
					else sound = true;
				}
				if (obj[i].name == "level")
				{
					isGame = false;
					restart = false;
					start = false;
					end = false;
					setWindow("level");
				}
				if (obj[i].name == "1"|| obj[i].name == "2"|| obj[i].name == "3")
				{
					isGame = true;
					start = true;
					lvl = stoi(obj[i].name);
					setWindow("start");
				}
				if (obj[i].name == "exit") exit(0);
				if (obj[i].name == "back")
				{
					setWindow("level");
				    isGame = true;
				}
				if (obj[i].name == "restart")
				{
					isGame = true;
					restart = true;
					if (W.currentWindow == "fail" || W.currentWindow == "victory")
					{
						restart = false;
						start = true;
					}
					setWindow("start");
				}
				if (obj[i].name == "start")
				{
					isGame = false;
					if(W.currentWindow == "pause") end = true;
					setWindow("start");
				}
			}
	}
	click=false;
}