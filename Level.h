#pragma once
#include"lib.h"

struct Object
{
    std::string name;
    Rect<float> rect;
    Sprite sprite;
};

struct Layer
{
    std::vector<Sprite> tiles;    //������ ������ ����
};

class Level
{
private:
    int width, height, tileWidth, tileHeight;//������ �����, ������ �����, ������ �����, ������ �����
    int firstTileID;                       //���� ������� �����
    Rect<float> drawingBounds;             //������ ����� �����, ������� ������
    Texture tilesetImage;                  //�������� �����
    std::vector<Object> objects;           //������ ��������
    std::vector<Layer> layers;             //������ ����
public:
    bool LoadFromFile(std::string filename, std::string image);  //false ���� �� ������ ��������� ����
    Object GetObject(std::string name);                //���������� ������ ������ � �������� ������
    std::vector<Object> GetObjects(std::string name);  //���������� ������ �������� � �������� ������
    std::vector<Object> GetAllObjects();               //���������� ������ �� ����� ���������
    void Draw(RenderWindow& window);                   //������� (������) � ���� ��� ����
};

