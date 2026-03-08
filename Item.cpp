#include "Item.h"
Texture Item::texture;
bool Item::textureLoaded = false;

Item::Item()
{
}

Item::~Item()
{
}

void Item::Initialize(Vector2f position)
{	
	if (!textureLoaded)
	{
		if (!texture.loadFromFile("Project1/assets/texture/items/item418.png"))
		{
			cout << "Chyba: Nepodarilo se nacist item418.png" << endl;
		}
		textureLoaded = true;
	}
	shape.setSize({ 30.0f, 30.0f });
	shape.setFillColor(Color::Yellow);
	shape.setOutlineColor(Color::White);
	shape.setOutlineThickness(2.0f);

	shape.setOrigin({ 20.0f, 20.0f });
	shape.setPosition(position);

	shape.setFillColor(Color::White);
	shape.setTexture(&texture);
	shape.setOutlineColor(Color::Transparent);
	shape.setOutlineThickness(2.0f);
}

void Item::Update(float deltaTime)
{

}

void Item::Draw(RenderWindow& window)
{
	window.draw(shape);
}
