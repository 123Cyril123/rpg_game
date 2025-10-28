#include "Math.h"
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;

Vector2f Math::normalizeVector(Vector2f vector)
{
	float m = sqrt(vector.x * vector.x + vector.y * vector.y);

	Vector2f normalizedVector;
	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
}
//collision on X axis 
//if (rect1.rightEdge > rect2.leftEdge && rect2.rightEdge > rect1.leftEdge) {
//	there is collision
//}
//
//collision on Y axis
//if (rect1.topEdge > rect2.bottomEdge && rect2.topEdge > rect1.bottomEdge) {
//	there is collision
//}
bool Math::checkRectCollision(FloatRect rect1, FloatRect rect2)
{	
	int rect1Left = rect1.position.x;
	int rect1Right = rect1Left + rect1.size.x;
	int rect2Left  = rect2.position.x;
	int rect2Right = rect2Left + rect2.size.x;

	int rect1Top = rect1.position.y;
	int rect1Bottom = rect1Top + rect1.size.y;
	int rect2Top = rect2.position.y;
	int rect2Bottom = rect2Top + rect2.size.y;

	if (rect2Left < rect1Right &&
		rect2Right > rect1Left &&
		rect2Top < rect1Bottom &&
		rect2Bottom > rect1Top)
	{
		return true;
	}
	
	return false;
}

