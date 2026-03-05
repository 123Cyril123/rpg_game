#include "HighScore.h"

void HighScore::writeToFile(int score, string file)
{
	if (score > currentHighScore)
	{
		currentHighScore = score;
		ofstream f(file);
		if (f.is_open())
		{
			f << currentHighScore;
			f.close();
		}
	}
}

void HighScore::loadFromFile(string file)
{
	ifstream f(file);

	if (f.is_open())
	{
		f >> currentHighScore;
	}
	else {
		currentHighScore = 0;
	}
	f.close();
}
