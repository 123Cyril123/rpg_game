#include "Skeleton.h"

void Skeleton::Initialize() 
{

}

void Skeleton::Load()
{
	if (texture.loadFromFile("Project1/assets/enemy/textures/spriteSheet.png"))
	{
		int XIndex = 0;
		int YIndex = 2;

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect({ XIndex * 64, YIndex * 64 }, { 64,64 }));
		sprite.scale({ 2,2 });
		sprite.setPosition({ 1800,100 });

	}
}

void Skeleton::Update() {

}

void Skeleton::Draw(RenderWindow &window)
{
	window.draw(sprite);
}