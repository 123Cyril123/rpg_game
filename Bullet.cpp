#include "Bullet.h"
#include "Math.h"

Texture Bullet::texture;
bool Bullet::textureLoaded = false;

Bullet::Bullet() : speed(0)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const Vector2f &position, const Vector2f &target, float speed)
{	
	this->speed = speed; 
	rectangleshape.setSize({ 20,20 });
	rectangleshape.setPosition(position);
	direction = Math::normalizeVector(target - position);

	if (!textureLoaded)
	{
		if (!texture.loadFromFile("Project1/assets/texture/meteorite.png"))
		{
			cout << "Chyba: Nepodarilo se nacist meteorite.png" << endl;
		}
		else {
			texture.setSmooth(true);
			textureLoaded = true;
		}
	}

	rectangleshape.setFillColor(Color::White);
	rectangleshape.setTexture(&texture);
	rectangleshape.setOutlineColor(Color::Transparent);
	rectangleshape.setOutlineThickness(2.0f);
}

void Bullet::Load()
{

}


void Bullet::Update(float deltaTime)
{
	rectangleshape.setPosition(rectangleshape.getPosition() + direction * speed * deltaTime);
}

void Bullet::Draw(RenderWindow &window)
{
	window.draw(rectangleshape);
}
