#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;

class HighScore
{
public:
	int currentHighScore = 0;
	void writeToFile(int score, string file);
	void loadFromFile(string file);
};

