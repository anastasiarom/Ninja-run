#include "Level.h"

bool Level::LoadFromFile(std::string filename, std::string image)
{
    TiXmlDocument levelFile(filename.c_str());
    if (!levelFile.LoadFile())     // Загружаем XML-карту
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }
    // Работаем с контейнером map
    TiXmlElement* map;
    map = levelFile.FirstChildElement("map");
   
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));
    // Берем описание тайлсета и идентификатор первого тайла
    TiXmlElement* tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));
    // Пытаемся загрузить тайлсет
    Image img;
    if (!img.loadFromFile(image))
    {
        std::cout << "Failed to load tileset." << std::endl;
        return false;
    }
    //img.createMaskFromColor(Color(255, 255, 255));
    tilesetImage.loadFromImage(img);
    tilesetImage.setSmooth(false);
    // Получаем количество столбцов и строк тайлсета
    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;
    // Вектор из прямоугольников изображений (TextureRect)
    std::vector<Rect<int> > subRects;
    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            Rect<int> rect;
            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;
            subRects.push_back(rect);
        }
    // Работа со слоями
    TiXmlElement* layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;
        
        // Контейнер <data>
        TiXmlElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");
        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }
        // Контейнер <tile> - описание тайлов каждого слоя
        TiXmlElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");
        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }
        int x = 0;
        int y = 0;
        while (tileElement)
        {
            int tileGID;
            if (tileElement->Attribute("gid") == NULL)
            {
                tileGID=0;
            }
            else
                tileGID = atoi(tileElement->Attribute("gid"));

                int subRectToUse = tileGID - firstTileID;
                
                // Устанавливаем TextureRect каждого тайла
                if (subRectToUse >= 0)
                {
                    Sprite sprite;
                    sprite.setTexture(tilesetImage);
                    sprite.setTextureRect(subRects[subRectToUse]);
                    sprite.setPosition(x * tileWidth, y * tileHeight);     
                    sprite.setColor(Color(255, 255, 255, 255));
                    layer.tiles.push_back(sprite);
                }
                tileElement = tileElement->NextSiblingElement("tile");  
                x++;
                if (x >= width)
                {
                    x = 0;
                    y++;
                    if (y >= height)
                        y = 0;
                }
        }
        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }
    // Работа с объектами
    TiXmlElement* objectGroupElement;
    // Если есть слои объектов
    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            // Контейнер <object>
            TiXmlElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement)
            {
                // Получаем все данные - тип, имя, позиция, etc
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }
                // Экземпляр объекта
                Object object;
                object.name = objectName;
                object.sprite = sprite;

                Rect <float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;
                               
                objects.push_back(object);
                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }
    return true;
}

Object Level::GetObject(std::string name)
{
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::GetObjects(std::string name)
{
    std::vector<Object> vec;
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            vec.push_back(objects[i]);

    return vec;
}

std::vector<Object> Level::GetAllObjects()
{
    return objects;
};

void Level::Draw(RenderWindow& window)
{
    for (int layer = 0; layer < layers.size(); layer++)
        for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
            window.draw(layers[layer].tiles[tile]);
}

