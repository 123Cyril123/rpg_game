#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class map
{
private:
	Texture tileSheetTexture;
	Sprite sprite;
	

public:
	map();
	~map();

	void Initialize();
	void Load();
	void Update();
	void Draw(RenderWindow& window);
};

