#include "Player.h"
#include "Skeleton.h"
#include "Math.h"

using namespace std;
using namespace sf;


void Player::Initialize()
{	
	boundingRectangle.setFillColor(Color::Transparent);
	boundingRectangle.setOutlineColor(Color::Red);
	boundingRectangle.setOutlineThickness(3);
	sprite.scale({ 4,4 });
	size = { 32,32 };
	boundingRectangle.setSize({ size.x * sprite.getScale().x, size.y * sprite.getScale().y});
	
	
}

void Player::Load()
{
	if (texture.loadFromFile("Project1/assets/player/textures/characters.png"))
	{
		int XIndex = 0;
		int YIndex = 0;

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect({ XIndex * size.x, YIndex * size.y }, { size.x,size.y }));
		sprite.setPosition({ 1700, 800 });
	}
	else {
		return;
	}
}

void Player::Update(Skeleton &skeleton)
{
	Vector2f playerPosition = sprite.getPosition();
	int speed = 4;
	boundingRectangle.setPosition(playerPosition);
	if (Keyboard::isKeyPressed(Keyboard::Scan::W))
	{
		sprite.setPosition({ playerPosition.x, playerPosition.y - speed });
		boundingRectangle.setPosition({ playerPosition.x, playerPosition.y - speed });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::A))
	{
		sprite.setPosition({ playerPosition.x - speed, playerPosition.y });
		boundingRectangle.setPosition({ playerPosition.x - speed, playerPosition.y });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::S))
	{
		sprite.setPosition({ playerPosition.x, playerPosition.y + speed });
		boundingRectangle.setPosition({ playerPosition.x, playerPosition.y + speed });
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::D))
	{

		sprite.setPosition({ playerPosition.x + speed, playerPosition.y });
		boundingRectangle.setPosition({ playerPosition.x + speed, playerPosition.y });
	}
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		RectangleShape bullet({ 10,5 });
		bullets.push_back(bullet);
		bullets[bullets.size() - 1].setPosition(sprite.getPosition());
	}
	for (size_t i = 0; i < bullets.size(); i++)
	{
		Vector2f bulletDirection;
		bulletDirection = skeleton.sprite.getPosition() - bullets[i].getPosition();
		bulletDirection = Math::normalizeVector(bulletDirection);
		bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed);
	}

	if (Math::checkRectCollision(sprite.getGlobalBounds(), skeleton.sprite.getGlobalBounds()))
	{
		cout << "Collision" << endl;
	}
	else
		cout << "No collision" << endl;
}

void Player::Draw(RenderWindow &window)
{
	window.draw(sprite);
	for (size_t i = 0; i < bullets.size(); i++)
	{
		window.draw(bullets[i]);
	}

	window.draw(boundingRectangle);
}
