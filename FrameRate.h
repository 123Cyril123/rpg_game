#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h"
using namespace sf;
using namespace std;

class FrameRate
{
private:
	Font font;
	Text frameRateText;
	float timer;

public:
	FrameRate();
	~FrameRate();


	

	void Load();
	void Update(float deltaTime, Skeleton& skeleton);
	void Draw(RenderWindow& window);
	void Initialize();
};

