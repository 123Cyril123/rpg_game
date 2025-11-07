#include "map.h"


map::map() : sprite(tileSheetTexture) {
	cout << "object has been created" << endl;
}
map::~map()
{
}

void map::Initialize()
{

}

void map::Load()
{
    if (!tileSheetTexture.loadFromFile("Project1/assets/world/tileSheet.png")) {
        cout << "Failed to load texture!" << endl;
    }
    else {
        int XIndex = 0;
        int YIndex = 0;

        sprite.setTexture(tileSheetTexture);  
        cout << "Texture loaded successfully!" << endl;
        sprite.setTextureRect(IntRect({ XIndex * 16, YIndex * 16 }, { 16,16 }));
        sprite.setPosition({ 0,0 });
        sprite.scale({ 3, 3 });
    }
}

void map::Update()
{

}

void map::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
