#include "Player.h"
#include "Skeleton.h"
#include "Math.h"
#include "Bullet.h"

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

void Player::Update(float deltaTime, Skeleton &skeleton, Vector2f &mousePosition)
{
	Vector2f playerPosition = sprite.getPosition();
	int speed = 4;
	boundingRectangle.setPosition(playerPosition);
	if (Keyboard::isKeyPressed(Keyboard::Scan::W))
	{
		sprite.setPosition(playerPosition + Vector2f{0,-1} *movementSpeed * deltaTime);
		boundingRectangle.setPosition(playerPosition + Vector2f{ 0,-1 }*movementSpeed * deltaTime);
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::A))
	{
		sprite.setPosition(playerPosition + Vector2f{ -1,0 }*movementSpeed * deltaTime);
		boundingRectangle.setPosition(playerPosition + Vector2f{ -1,0 }*movementSpeed * deltaTime);
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::S))
	{
		sprite.setPosition(playerPosition + Vector2f{ 0,1 }*movementSpeed * deltaTime);
		boundingRectangle.setPosition(playerPosition + Vector2f{ 0,1 }*movementSpeed * deltaTime);
	}
	if (Keyboard::isKeyPressed(Keyboard::Scan::D))
	{

		sprite.setPosition(playerPosition + Vector2f{ 1,0 }*movementSpeed * deltaTime);
		boundingRectangle.setPosition(playerPosition + Vector2f{ 1,0 }*movementSpeed * deltaTime);
	}

	//-----------------------------------bullet---------------------------------------------------------------------
	fireRateTimer += deltaTime;
	if (Mouse::isButtonPressed(Mouse::Button::Left) && fireRateTimer >= maxFireRate)
	{
		
		bullets.push_back(Bullet());
		bullets[bullets.size() - 1].Initialize(sprite.getPosition(), mousePosition, 3);
		fireRateTimer = 0;
	}
	for (size_t i = 0; i < bullets.size(); i++)
	{
		Vector2f bulletDirection;
		
		bullets[i].Update(deltaTime);

		if (skeleton.health > 0)
		{
			if (Math::checkRectCollision(bullets[i].GetGlobalBounds(), skeleton.sprite.getGlobalBounds()))
			{
				bullets.erase(bullets.begin() + i);
				skeleton.changeHealth(-10);
				cout << "Skeleton hp: " << skeleton.health << endl;
			}
		}
		
	}
	//-----------------------------------bullet---------------------------------------------------------------------

}

void Player::Draw(RenderWindow &window)
{
	window.draw(sprite);
	for (size_t i = 0; i < bullets.size(); i++)
	{
		bullets[i].Draw(window);
	}

	window.draw(boundingRectangle);
}
