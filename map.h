#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class tMap
{
private:
    Texture texLayer1, texLayer2, texLayer3, texLayer4;
    Sprite sprLayer1, sprLayer2;

    Sprite sprLayer3_A, sprLayer3_B;
    Sprite sprLayer4_A, sprLayer4_B;

public:
    tMap();
    ~tMap();

    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(RenderWindow& window);
};



 


