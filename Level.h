#pragma once
#include"lib.h"

struct Object
{
    std::string name;
    Rect<float> rect;
};

struct Layer
{
    std::vector<Sprite> tiles;    //вектор тайлов слоя
};

class Level
{
private:
    int width, height, tileWidth, tileHeight;//ширина карты, высота карты, ширина тайла, высота тайла
    int firstTileID;                       //айди первого тайла
    Texture tilesetImage;                  //текстура карты
    std::vector<Object> objects;           //вектор объектов
    std::vector<Layer> layers;             //вектор слоёв
public:
    bool LoadFromFile(std::string filename, std::string image);  //false если не смогли загрузить файл
    Object GetObject(std::string name);                //возвращает первый объект с заданным именем
    std::vector<Object> GetObjects(std::string name);  //возвращает вектор объектов с заданным именем
    std::vector<Object> GetAllObjects();               //возвращает вектор со всеми объектами
    void Draw(RenderWindow& window);                   //выводит (рисует) в окно все слои
};

