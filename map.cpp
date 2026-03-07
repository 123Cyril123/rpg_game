#include "map.h"

tMap::tMap() :
    sprLayer1(texLayer1), sprLayer2(texLayer2),
    sprLayer3_A(texLayer3), sprLayer3_B(texLayer3),
    sprLayer4_A(texLayer4), sprLayer4_B(texLayer4)
{
    cout << "Map object has been created" << endl;
}

tMap::~tMap() {}

void tMap::Initialize() {}

void tMap::Load()
{
    if (!texLayer1.loadFromFile("Project1/assets/texture/Clouds 3/1.png")) cout << "Chyba: 1.png" << endl;
    if (!texLayer2.loadFromFile("Project1/assets/texture/Clouds 3/2.png")) cout << "Chyba: 2.png" << endl;
    if (!texLayer3.loadFromFile("Project1/assets/texture/Clouds 3/3.png")) cout << "Chyba: 3.png" << endl;
    if (!texLayer4.loadFromFile("Project1/assets/texture/Clouds 3/4.png")) cout << "Chyba: 4.png" << endl;

    sprLayer1.setTexture(texLayer1, true);
    sprLayer2.setTexture(texLayer2, true);

    sprLayer3_A.setTexture(texLayer3, true);
    sprLayer3_B.setTexture(texLayer3, true);

    sprLayer4_A.setTexture(texLayer4, true);
    sprLayer4_B.setTexture(texLayer4, true);

    Vector2u velikostObrazku = texLayer1.getSize();
    float scaleX = 1980.0f / velikostObrazku.x;
    float scaleY = 1050.0f / velikostObrazku.y;

    sprLayer1.setScale({ scaleX, scaleY });
    sprLayer2.setScale({ scaleX, scaleY });
    sprLayer3_A.setScale({ scaleX, scaleY });
    sprLayer3_B.setScale({ scaleX, scaleY });
    sprLayer4_A.setScale({ scaleX, scaleY });
    sprLayer4_B.setScale({ scaleX, scaleY });

    sprLayer3_B.setPosition({ 1980.f, 0.f });
    sprLayer4_B.setPosition({ 1980.f, 0.f });
}

void tMap::Update(float deltaTime)
{
    float speed3 = 0.05f * deltaTime;
    float speed4 = 0.15f * deltaTime;

    sprLayer3_A.move({ -speed3, 0.f });
    sprLayer3_B.move({ -speed3, 0.f });

    sprLayer4_A.move({ -speed4, 0.f });
    sprLayer4_B.move({ -speed4, 0.f });

    if (sprLayer3_A.getPosition().x <= -1980.f) sprLayer3_A.setPosition({ 1980.f, 0.f });
    if (sprLayer3_B.getPosition().x <= -1980.f) sprLayer3_B.setPosition({ 1980.f, 0.f });

    if (sprLayer4_A.getPosition().x <= -1980.f) sprLayer4_A.setPosition({ 1980.f, 0.f });
    if (sprLayer4_B.getPosition().x <= -1980.f) sprLayer4_B.setPosition({ 1980.f, 0.f });
}

void tMap::Draw(RenderWindow& window)
{
    window.draw(sprLayer1);
    window.draw(sprLayer2);

    window.draw(sprLayer3_A);
    window.draw(sprLayer3_B);

    window.draw(sprLayer4_A);
    window.draw(sprLayer4_B);
}