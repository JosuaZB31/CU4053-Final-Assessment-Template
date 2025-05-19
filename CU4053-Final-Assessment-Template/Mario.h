#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Projectiles.h"
#include "Framework/World.h"

class Mario :
    public GameObject
{
    int health;
    sf::Texture marioSpriteSheet;
    Animation Walk;
    Animation Swim;
    Animation Duck;
    Animation* currentAnimation;

    int CollectableCount = 0;

    std::vector<Projectiles*> bullets;

    World* world;


public:
    Mario();
    void handleInput(float dt) override;

    void AddCollectable() { CollectableCount++; }
    int getCollectableCount() { return CollectableCount; }
    void ReduceHealth(float h);
    float getHealth() { return health; }

    void setWorld(World* world) { this->world = world; }

    std::vector<Projectiles*>& getBullets() { return bullets; }
};

