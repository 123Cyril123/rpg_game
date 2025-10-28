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

