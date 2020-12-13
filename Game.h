#pragma once
#include"Player.h"
#include"Enemy.h"
#include"MovingPlatform.h"
#include"Coin.h"
#include"Windows.h"

void currentWindow(RenderWindow&, Windows&);
bool StartGame(int,RenderWindow&, Windows&);
void RunGame(int,RenderWindow&, Windows&);
void NinjaRun();