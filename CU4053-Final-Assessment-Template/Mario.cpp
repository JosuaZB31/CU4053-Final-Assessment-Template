#include "Mario.h"

Mario::Mario()
{
	marioSpriteSheet.loadFromFile("gfx/MarioSheetT.png");
	setSize(sf::Vector2f(15 * 4, 21 * 4));
	setPosition(400, 0);
	setTexture(&marioSpriteSheet);

	Walk.addFrame(sf::IntRect(0, 0, 15, 21));
	Walk.addFrame(sf::IntRect(15, 0, 15, 21));
	Walk.addFrame(sf::IntRect(30, 0, 15, 21));
	Walk.addFrame(sf::IntRect(45, 0, 15, 21));
	Walk.setFrameSpeed(1.f / 10.f);

	Swim.addFrame(sf::IntRect(0, 21, 16, 20));
	Swim.addFrame(sf::IntRect(16, 21, 16, 20));
	Swim.addFrame(sf::IntRect(32, 21, 16, 20));
	Swim.setFrameSpeed(1.f / 2.4);

	Duck.addFrame(sf::IntRect(0, 44, 17, 17));
	//Duck.addFrame(sf::IntRect(17, 44, 17, 17));
	Duck.setFrameSpeed(1.f / 2.f);
	currentAnimation = &Walk;

	setTag("Player");
	health = 100;

}
void Mario::ReduceHealth(float h)
{
	health -= h;
}
void Mario::handleInput(float dt)
{
	velocity.x = 0.f;
	setTextureRect(currentAnimation->getCurrentFrame());
	if (input->isKeyDown(sf::Keyboard::A))
	{
		velocity.x = -200;
		currentAnimation = &Walk;
		currentAnimation->setFlipped(true);
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		velocity.x = 200;
		currentAnimation = &Walk;
		currentAnimation->setFlipped(false);
	}
	else if (input->isKeyDown(sf::Keyboard::C))
	{
		currentAnimation = &Duck;
	}
	else if (input->isKeyDown(sf::Keyboard::Up))

	{
		currentAnimation = &Swim;
	}

	else
	{
		currentAnimation->reset();
		currentAnimation = &Walk;
	}
	if (input->isKeyDown(sf::Keyboard::W) && canJump)
	{
		Jump(160.f);
	}


	if (input->isKeyDown(sf::Keyboard::E))
	{
		input->setKeyUp(sf::Keyboard::E);
		// Create a new projectile
		Projectiles* bullet = new Projectiles();
		if (currentAnimation->getFlipped() == false) {
			sf::Vector2f BulletPos = getPosition() - sf::Vector2f(-120, 0);
			bullet->setPosition(BulletPos);
		}
		else if (currentAnimation->getFlipped() == true) {
			sf::Vector2f BulletPos = getPosition() + sf::Vector2f(0, 0);
			bullet->setPosition(BulletPos);
		}
		// Calculate the position of the mouse
		sf::Vector2f MousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());

		// Calculate the direction from the bullet's position to the mouse position
		sf::Vector2f direction = MousePos - getPosition();

		// Normalize the direction vector
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f normalizedDirection = direction / magnitude;

		// Set the velocity of the bullet to be in the direction of the mouse
		// Adjust the speed as needed by multiplying the normalized direction by the desired speed
		if (currentAnimation->getFlipped() == true) {
			bullet->setVelocity(-1000, 0); // You can adjust the speed by changing 1000.f
		}
		else if (currentAnimation->getFlipped() == false) {
			bullet->setVelocity(1000, 0);
		}

		// Add the bullet to the list of bullets
		bullets.push_back(bullet);

		// Add the bullet to the world
		world->AddGameObject(*bullet);
	}
	currentAnimation->animate(dt);
	
}
