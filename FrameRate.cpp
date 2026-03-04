#include "FrameRate.h"
#include <iostream>

FrameRate::FrameRate() : frameRateText(font), timer(0) 
{

}


FrameRate::~FrameRate()
{
}

void FrameRate::Initialize()
{ 
	frameRateText.setCharacterSize(20);
	frameRateText.setFillColor(Color::White);
	frameRateText.setOutlineColor(Color::Black);
	frameRateText.setOutlineThickness(1.0f);
	frameRateText.setPosition({ 20.f, 60.f });

}

void FrameRate::Load()
{
	if (!font.openFromFile("Project1/assets/fonts/Arial.ttf"))
	{
		cout << "font not loaded";
	}
	else
	{
		cout << "font loaded";
		frameRateText.setFont(font);
	}
}

void FrameRate::Update(float deltaTime, Skeleton& skeleton)
{	
	timer += deltaTime;

	if (timer >= 100)
	{
		float fps = 1.0f / (deltaTime / 1000);
		frameRateText.setString(to_string((int)fps) + " fps");
		timer = 0;
	}

	

}

void FrameRate::Draw(RenderWindow& window)
{
	window.draw(frameRateText);

}
