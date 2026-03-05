#include "Player.h"
#include "Skeleton.h"
#include "Math.h"
#include "Bullet.h"

using namespace std;
using namespace sf;


void Player::Initialize()
{	
	boundingRectangle.setFillColor(Color::Transparent);
	boundingRectangle.setOutlineColor(Color::Transparent);
	boundingRectangle.setOutlineThickness(3);
	sprite.scale({ 2,2 });
	size = { 32,32 };
	/*boundingRectangle.setSize({ size.x * sprite.getScale().x, size.y * sprite.getScale().y});*/
	boundingRectangle.setSize({ 24.f, 38.f }); 

	boundingRectangle2.setFillColor(Color::Transparent);
	boundingRectangle2.setOutlineColor(Color::Transparent);
	boundingRectangle2.setOutlineThickness(3);
	boundingRectangle2.setSize({ 50,50 });
	
}

void Player::Load()
{
	if (texture.loadFromFile("Project1/assets/player/textures/mainChar.png")) // Project1/assets/player/textures/characters.png
	{
		

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect({ XIndex * size.x, YIndex * size.y }, { size.x,size.y }));
		sprite.setPosition({ 1700, 800 });
	}
	else {
		return;
	}
}

	void Player::Update(float deltaTime, Skeleton & skeleton, Vector2f & mousePosition)
	{
		Vector2f playerPosition = sprite.getPosition();
		Vector2f movementDirection(0.f, 0.f); 

		if (Keyboard::isKeyPressed(Keyboard::Scan::W))
		{
			movementDirection.y -= 1.f;
			YIndex = 2;
			isFacingLeft = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::S))
		{
			movementDirection.y += 1.f;
			YIndex = 0;
			isFacingLeft = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::A))
		{
			movementDirection.x -= 1.f;
			YIndex = 1;
			isFacingLeft = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::D))
		{
			movementDirection.x += 1.f;
			YIndex = 1;
			isFacingLeft = false;
		}

		if (isFacingLeft)
		{
			sprite.setTextureRect(IntRect({ (XIndex + 1) * size.x, YIndex * size.y }, { -size.x, size.y }));
		}
		else {
			sprite.setTextureRect(IntRect({ XIndex * size.x, YIndex * size.y }, { size.x, size.y }));
		}
		
					

		if (movementDirection.x != 0.f || movementDirection.y != 0.f)
		{
			movementDirection = Math::normalizeVector(movementDirection);

			float currentSpeed = movementSpeed;
			if (Keyboard::isKeyPressed(Keyboard::Scan::LShift))
			{
				currentSpeed = 2.0f * movementSpeed;
			}

			Vector2f newPosition = playerPosition + (movementDirection * movementSpeed * currentSpeed * deltaTime);

			float playerWidth = 64.f;
			float playerHeight = 64.f;

			if (newPosition.x < 0.f)
				newPosition.x = 0.f;
			else if (newPosition.x > 1980.f - playerWidth)
				newPosition.x = 1980.f - playerWidth;

			if (newPosition.y < 0.f)
				newPosition.y = 0.f;
			else if (newPosition.y > 1050.f - playerHeight)
				newPosition.y = 1050.f - playerHeight;

			sprite.setPosition(newPosition);
			boundingRectangle.setPosition(newPosition + Vector2f(20.f, 18.f));
			boundingRectangle2.setPosition(newPosition + Vector2f(7.f, 7.f));
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
	window.draw(boundingRectangle2);
}
