#include "Enemy.h"
#include <chrono>
#include <thread>


Enemy::Enemy()
{

    speed = 300;
    bool isWaiting(false);
    velocity.x = speed;
    waitDuration = 2.0f;
    setTag("Enemy");

    enemySpriteSheet.loadFromFile("gfx/tooth walker sprite-Sheet.png");
    setSize(sf::Vector2f(16 * 4, 44 * 4));
    setPosition(400, 400);
    setTexture(&enemySpriteSheet);

    //creates idle animation for enemy
    idle.addFrame(sf::IntRect(32, 80, 16, 44));
    idle.addFrame(sf::IntRect(96, 80, 16, 44));
    idle.addFrame(sf::IntRect(160, 80, 16, 44));
    idle.addFrame(sf::IntRect(224, 80, 16, 44));

    idle.setFrameSpeed(1.f / 4.f);
    //creates walk animation for enemy
    walk.addFrame(sf::IntRect(32, 16, 16, 44));
    walk.addFrame(sf::IntRect(96, 16, 16, 44));
    walk.addFrame(sf::IntRect(158, 16, 16, 44));
    walk.addFrame(sf::IntRect(220, 16, 16, 44));
    walk.addFrame(sf::IntRect(282, 16, 16, 44));
    walk.addFrame(sf::IntRect(350, 16, 16, 44));

    walk.setFrameSpeed(1.f / 4.f);
    //creates  death animation for enemy
    Death.addFrame(sf::IntRect(188, 80, 16, 44));
    Death.addFrame(sf::IntRect(350, 80, 16, 44));
    Death.addFrame(sf::IntRect(31, 144, 16, 44));
    Death.addFrame(sf::IntRect(91, 144, 16, 44));

    Death.setFrameSpeed(1.f / 3.f);


    currentAnimation = &walk;
    setTextureRect(currentAnimation->getCurrentFrame());
}

void Enemy::handleInput(float dt)
{
    setTextureRect(currentAnimation->getCurrentFrame());

    // Handle collision
    if (CollisionWithTag("Wall")) {
        std::cout << "Colliding with wall" << std::endl;
        isWaiting = true;
        waitStartTime = std::chrono::steady_clock::now(); // Start the wait timer
        idle.setFlipped(velocity.x < 0);
        setPosition((getPosition().x - (velocity.x / 100)), getPosition().y);
        PreVelo = velocity.x;
        velocity.x = 0;
        return;
    }

    if (isWaiting) {
        currentAnimation = &idle; // Switch to idle animation
        // Calculate the elapsed time since we started waiting
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - waitStartTime;

        if (elapsed.count() >= waitDuration) {
            // Done waiting
            isWaiting = false;
            velocity.x = PreVelo;
            velocity.x = -velocity.x; // Reverse velocity
            walk.setFlipped(velocity.x < 0); // Flip based on new direction
            idle.setFlipped(velocity.x < 0); // Flip based on new direction
            currentAnimation = &walk;
        }
    }
    //detects if bullet hits enemy 
    if (CollisionWithTag("Bullet")) {
        currentAnimation = &Death;
        velocity.x = 0;
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - waitStartTime;

        if (elapsed.count() >= waitDuration) {
            setAlive(false);
        }

    }
    currentAnimation->animate(dt);

}