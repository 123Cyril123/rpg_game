#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Math
{
public:
	static Vector2f normalizeVector(Vector2f vector);
	static bool checkRectCollision(FloatRect rect1, FloatRect rect2);
};

