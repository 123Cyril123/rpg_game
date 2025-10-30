#include "Skeleton.h"
#include <iostream>

using namespace std;
using namespace sf;


Skeleton::Skeleton() : sprite(texture), health(100), healthText(font)
{

}

Skeleton::~Skeleton()
{
}

void Skeleton::changeHealth(int hp)
{
	health += hp;
	healthText.setString(to_string(health) + " hp");
}

void Skeleton::Initialize()
{	
	boundingRectangle.setFillColor(Color::Transparent);
	boundingRectangle.setOutlineColor(Color::Yellow);
	boundingRectangle.setOutlineThickness(3);
	sprite.setPosition({ 1800,100 });
	sprite.scale({ 2,2 });
	size = { 64,64 };
	boundingRectangle.setSize({ size.x * sprite.getScale().x, size.y * sprite.getScale().y });

	healthText.setCharacterSize(20);
	healthText.setFillColor(Color::White);
	healthText.setPosition(sprite.getPosition());
	healthText.setString(to_string(health) + " hp");
	
}

void Skeleton::Load()
{
	if (texture.loadFromFile("Project1/assets/enemy/textures/spriteSheet.png"))
	{
		int XIndex = 0;
		int YIndex = 2;

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect({ XIndex * size.x, YIndex * size.y }, { size.x,size.y }));

	}

	if (!font.openFromFile("Project1/assets/fonts/Arial.ttf"))
	{
		cout << "health text font not loaded" << endl;
	}
	else
	{
		cout << "health text font loaded" << endl;
		healthText.setFont(font);
	}
}

void Skeleton::Update() {
	boundingRectangle.setPosition(sprite.getPosition());
	

}

void Skeleton::Draw(RenderWindow &window)
{	
	window.draw(healthText);
	window.draw(sprite);
	window.draw(boundingRectangle);
}