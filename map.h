#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;

class map
{
private:
	Texture tileSheetTexture;
	const static int spritesSize = 10;
	std::vector<Sprite> sprites;
	int tileHeight;
	int tileWidth;
	int totalTilesX;
	int totalTilesY;
	

public:		
	map();
	~map();

	void Initialize();
	void Load();
	void Update();
	void Draw(RenderWindow& window);
};



 


