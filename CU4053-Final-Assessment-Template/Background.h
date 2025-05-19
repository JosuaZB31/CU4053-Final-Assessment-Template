#pragma once
#include"Framework/GameObject.h"
class Background :
    public GameObject
{
    sf::Texture texture; 
public:
    Background();
    ~Background();

    void update(float dt) override;
};

