#include"Game.h"

void currentWindow(RenderWindow& window, Windows& W)
{
    Music music;
    music.openFromFile("files/theme.mp3");
    music.setLoop(true);
    if(W.sound&&W.currentWindow!="pause") music.play();
    Font font;
    font.loadFromFile("files/Mistral.ttf");
    Text text("", font, 55);
    text.setOutlineColor(Color::Black);
    while (window.isOpen())
    {
        View view(FloatRect(0,0, 1920, 1080));
        window.setView(view);
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)window.close();
        if (Mouse::isButtonPressed(Mouse::Left)) W.click = true;
        if (W.sound == false && music.getStatus() == SoundSource::Status::Playing && W.currentWindow == "setup") { music.pause(); W.sound = true; }
        else
            if (W.sound == true && music.getStatus() == SoundSource::Status::Paused&&W.currentWindow == "setup") music.play();
        if ((!W.isGame)||(W.isGame &&(W.currentWindow == "pause")&&!W.start))
        {
            W.checkClick(window, W);
            W.windows[W.currentWindow].Draw(window);
            if (W.currentWindow == "victory")
            {
                std::ostringstream Score;
                Score << W.score;
                text.setString("" + Score.str()+"/236");
                text.setPosition(view.getCenter().x+10, view.getCenter().y+84);
                window.draw(text);
            }
            if (W.currentWindow == "setup"&&W.sound==false)
            {
                Texture b;
                b.loadFromFile("files/setup.png");
                Sprite button(b);
                button.setTextureRect(IntRect(1960,90,165,160));
                button.setPosition(view.getCenter().x -128, view.getCenter().y -195);
                window.draw(button);
            }
        }
        if (W.isGame&& W.start)
        {
           W.start = false;
           RunGame(W.lvl,window, W);
        }
        if ((!W.start && ((W.isGame && W.currentWindow != "pause"&& W.currentWindow != "setup" && !W.restart) || W.restart)) || W.end) return;
        window.display();
    }
}

bool StartGame(int l,RenderWindow& window, Windows &W )
{
    View view(FloatRect(0, 0, 1920, 1080));
    Level lvl;
    Texture bg, ninja, dynamic;
    switch (l)
    {
    case 1: {
        lvl.LoadFromFile("files/Level.tmx", "files/Tileset.png");
        bg.loadFromFile("files/bg.png");
    }
    case 2: {
        lvl.LoadFromFile("files/level2.tmx", "files/Tileset2.png");
        bg.loadFromFile("files/bg2.png");
    }
    case 3: {
        lvl.LoadFromFile("files/level3.tmx", "files/Tileset3.png");
        bg.loadFromFile("files/bg3.png");
    }
    }
    Sprite background(bg);
    background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);
    ninja.loadFromFile("files/Sprite.png");
    AnimationManager anim;
    anim.loadFromXML("files/Spritelist.xml", ninja);
    anim.loop(0, "jump");
    anim.loop(0, "dead");
    Object pl = lvl.GetObject("player");
    Player Ninja(anim, lvl, pl.rect.left, pl.rect.top);
    SoundBuffer Buffer1,Buffer2;
    Buffer1.loadFromFile("files/jump.wav");
    Sound sound(Buffer1);
    Ninja.soundJump = sound;
    Buffer2.loadFromFile("files/coin.wav");
    Sound sd(Buffer2);
    Ninja.soundCoin = sd;
    dynamic.loadFromFile("files/dynamic.png");
    AnimationManager turtle;
    turtle.create("move", dynamic, 0, 100, 150, 80, 6, 0.0025, 150, 1);
    turtle.create("dead", dynamic, 0, 180, 150, 70, 1, 0, 0, 1);
    AnimationManager bat;
    bat.create("move", dynamic, 0, 250, 150, 80, 4, 0.004, 150, 1);
    bat.create("dead", dynamic, 600, 250, 150, 80, 1, 0, 0, 1);
    AnimationManager moving_p;
    moving_p.create("move", dynamic, 10, 600, 220, 40, 1, 0, 0, 1);
    AnimationManager coin;
    coin.create("move", dynamic, 0, 40, 75, 60, 10, 0.005, 75, 1);
    std::list<Entity*>  entities;
    std::list<Entity*>::iterator it;
    std::vector<Object> ent;
    ent = lvl.GetObjects("turtle");
    for (int i = 0; i < ent.size(); i++)
        entities.push_back(new Enemy(turtle, lvl, ent[i].rect.left, ent[i].rect.top));
    ent = lvl.GetObjects("bat");
    for (int i = 0; i < ent.size(); i++)
        entities.push_back(new Enemy(bat, lvl, ent[i].rect.left, ent[i].rect.top));
    ent = lvl.GetObjects("platform");
    for (int i = 0; i < ent.size(); i++)
        entities.push_back(new MovingPlatform(moving_p, lvl, ent[i].rect.left, ent[i].rect.top));
    ent = lvl.GetObjects("coin");
    for (int i = 0; i < ent.size(); i++)
        entities.push_back(new Coin(coin, lvl, ent[i].rect.left, ent[i].rect.top));
    Clock clock;  
    Sprite sc(dynamic), life(dynamic), line(dynamic);
    sc.setTextureRect(IntRect(20, 680, 210, 90));
    life.setTextureRect(IntRect(500, 680, 310, 90));
    line.setTextureRect(IntRect(580, 630, 200, 30));
    int s = 200;
    Font font;
    font.loadFromFile("files/Mistral.ttf");
    Text text("", font, 30);
    text.setOutlineColor(Color::Black);
    int t=0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); 
        clock.restart(); 
        time = time / 500;        
        if (time > 40) time = 40;
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed) window.close();
        if (Keyboard::isKeyPressed(Keyboard::Left)) Ninja.key["L"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Right)) Ninja.key["R"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Up)) Ninja.key["Up"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Down)) Ninja.key["Down"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Space)) Ninja.key["Space"] = true;
        if (Keyboard::isKeyPressed(Keyboard::Escape)) Ninja.key["Esc"] = true;
        if (Ninja.pause)
        {
            W.setWindow("pause");
            currentWindow(window, W);
            if (W.restart)
            {
                W.restart = false;
                return true;
            }
            if (W.end)
            {
                W.end = false;
                return false;
            }
        }
        if (W.sound == false) Ninja.sound = false;
        if (Ninja.getHealth() <= 0)
        {
            s = 0;
            t++;
        }
        line.setTextureRect(IntRect(580, 630, s, 30));
        if (Ninja.win)
        {
            W.isGame = false;
            W.score = Ninja.score;
            W.setWindow("victory");
            return false;
        }
        for (it = entities.begin(); it != entities.end();)
        {
            Entity* e = *it;
            e->update(time);
            if (e->getLife() == false) 
            { 
                it = entities.erase(it); 
                delete e; 
            }
            else it++;
        }
        Ninja.update(time);
        if (Ninja.getHealth() <= 0 && Ninja.STATE == Player::dead && t > 2000)
        {
            W.isGame = false;
            W.setWindow("fail");
            return false;
        }
        for (it = entities.begin(); it != entities.end(); it++)
        {
            //1. враги
            if ((*it)->getName() == "Enemy")
            {
                Entity* enemy = *it;
                if (enemy->getHealth() <= 0) continue;
                if (Ninja.getRect().intersects(enemy->getRect()))
                    if (Ninja.getY() + Ninja.getH() < enemy->getY() + 5) { enemy->setDX(0); enemy->setDY(0.1); Ninja.setDY(-0.2); enemy->setHealth(0); }
                    else if (!Ninja.shoot)
                    {
                        Ninja.setHealth(10);
                        if (s >= 0) s -= 20;
                        line.setTextureRect(IntRect(580, 630, s, 30));
                        if (Ninja.getDir()) 
                        { 
                            Ninja.setX(10); 
                            Ninja.setY(-20); 
                        }
                        else 
                        { 
                            Ninja.setX(-10); 
                            Ninja.setY(-20); 
                        }
                    }
                    else
                    {
                        enemy->setDX(0);
                        enemy->setHealth(0);
                    }
            }
            //2. движущиеся платформы
            if ((*it)->getName() == "MovingPlatform")
            {
                Entity* movPlat = *it;
                if (Ninja.getRect().intersects(movPlat->getRect()))
                    if (Ninja.getDY() > 0)
                        if (Ninja.getY() + Ninja.getH() < movPlat->getY() + movPlat->getH())
                        {
                            Ninja.setY(movPlat->getY() - Ninja.getH()- Ninja.getY() + 5);
                            Ninja.setX((movPlat->getDX()) * time);
                            Ninja.setDY(0);
                            Ninja.STATE = Player::stay;
                        }
            }
            //3. монеты
            if ((*it)->getName() == "Coin")
            {
                Entity* coin = *it;
                if (Ninja.getRect().intersects(coin->getRect()))
                {
                    Ninja.score++;
                    coin->setHealth(0);
                    if(W.sound) Ninja.soundCoin.play();
                }
            }
        }
        view.setCenter(Ninja.getX(), 580);
        window.setView(view);
        std::ostringstream Score;
        Score << Ninja.score;
        text.setString("" + Score.str());
        text.setPosition(view.getCenter().x + 790, view.getCenter().y - 527);
        sc.setPosition(view.getCenter().x + 670, view.getCenter().y - 550);
        life.setPosition(view.getCenter().x + 350, view.getCenter().y - 548);
        line.setPosition(view.getCenter().x + 430, view.getCenter().y - 519);
        background.setPosition(view.getCenter());
        window.draw(background);
        lvl.Draw(window);
        for (it = entities.begin(); it != entities.end(); it++)
            (*it)->draw(window);
        Ninja.draw(window);
        window.draw(sc);
        window.draw(life);
        window.draw(line);
        window.draw(text);
        window.display();
    }
}

void RunGame(int l,RenderWindow& window, Windows& W) 
{
    if (StartGame(l,window,W)) RunGame(l,window, W); 
}

void NinjaRun()
{
    RenderWindow window(VideoMode(1920, 1080), "Ninja run");
    Windows W;
    W.loadAllWindows();
    currentWindow(window, W);
}