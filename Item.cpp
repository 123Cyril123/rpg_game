#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Initialize(Vector2f position)
{
	shape.setSize({ 20.0f, 20.0f });
	shape.setFillColor(Color::Yellow);
	shape.setOutlineColor(Color::White);
	shape.setOutlineThickness(2.0f);

	shape.setOrigin({ 10.0f, 10.0f });
	shape.setPosition(position);
}

void Item::Update(float deltaTime)
{

}

void Item::Draw(RenderWindow& window)
{
	window.draw(shape);
}
