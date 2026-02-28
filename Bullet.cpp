#include "Bullet.h"
#include "Math.h"

Bullet::Bullet() : speed(0)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(const Vector2f &position, const Vector2f &target, float speed)
{	
	this->speed = speed; 
	rectangleshape.setSize({ 10,5 });
	rectangleshape.setPosition(position);
	direction = Math::normalizeVector(target - position);
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
