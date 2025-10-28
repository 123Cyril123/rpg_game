#include "Skeleton.h"

using namespace sf;

void Skeleton::Initialize() 
{	
	boundingRectangle.setFillColor(Color::Transparent);
	boundingRectangle.setOutlineColor(Color::Yellow);
	boundingRectangle.setOutlineThickness(3);
	sprite.scale({ 2,2 });
	size = { 64,64 };
	boundingRectangle.setSize({ size.x * sprite.getScale().x, size.y * sprite.getScale().y });
	
}

void Skeleton::Load()
{
	if (texture.loadFromFile("Project1/assets/enemy/textures/spriteSheet.png"))
	{
		int XIndex = 0;
		int YIndex = 2;

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect({ XIndex * size.x, YIndex * size.y }, { size.x,size.y }));
		sprite.setPosition({ 1800,100 });

	}
}

void Skeleton::Update() {
	boundingRectangle.setPosition(sprite.getPosition());
}

void Skeleton::Draw(RenderWindow &window)
{
	window.draw(sprite);
	window.draw(boundingRectangle);
}