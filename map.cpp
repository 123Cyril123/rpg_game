#include "map.h"

map::map() : tileWidth(32), tileHeight(32), totalTilesX(0), totalTilesY(0)
{   
    cout << "Map object has been created" << endl;
}

map::~map()
{
}

void map::Initialize()
{
    // optional for now
}

void map::Load()
{
    if (!tileSheetTexture.loadFromFile("Project1/assets/world/tileSheet2.png")) {
        cout << "Failed to load texture!" << endl;
        return;
    }

    // calculate how many tiles exist in the sheet
    totalTilesX = tileSheetTexture.getSize().x / tileWidth;
    totalTilesY = tileSheetTexture.getSize().y / tileHeight;

    cout << "Tiles in sheet: " << totalTilesX << " x " << totalTilesY << endl;

    // resize vector to hold all tiles
    sprites.clear();
    sprites.reserve(totalTilesX * totalTilesY);

    // generate grid of sprites
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            Sprite sprite(tileSheetTexture);
            sprite.setTexture(tileSheetTexture);
            sprite.setScale({ 3, 3 });
            Vector2f scale = sprite.getScale();
            sprite.setTextureRect(IntRect({ 4 * tileWidth, 0 * tileHeight }, { tileWidth, tileHeight }));
            sprite.setPosition({ static_cast<float>(0 + x * tileWidth * scale.x), static_cast<float>(0 + y * tileHeight * scale.y) });
            // optional scaling
            
            sprites.push_back(sprite);
        }
    }
    cout << "Map loaded successfully with " << sprites.size() << " tiles!" << endl;
}

void map::Update()
{
    // optional, implement animation or scrolling here
}

void map::Draw(RenderWindow& window)
{
    for (auto& sprite : sprites)
        window.draw(sprite);
}
