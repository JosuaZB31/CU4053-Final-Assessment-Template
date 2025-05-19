#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <chrono>
#include <thread>


class Enemy : public GameObject
{

	int speed;
	Animation walk;
	Animation idle;
	Animation Death;

	Animation* currentAnimation;
	float waitDuration;
	sf::Texture enemySpriteSheet;

public:
	Enemy();
	void handleInput(float dt) override;
	bool isMoving;
	bool isWaiting = false;
	bool isLiving;
	std::chrono::time_point<std::chrono::steady_clock> waitStartTime;

	float PreVelo;

};