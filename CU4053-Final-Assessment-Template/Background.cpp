#include "Background.h"

Background::Background()
{
	texture.loadFromFile("gfx/MiniSlugBackground.jpg");
	texture.setRepeated(true);
	setTexture(&texture);
	setSize(sf::Vector2f(1920, 1080));
	setPosition(0, -500);
	setScale(4, 4);

}

Background::~Background()
{
}

void Background::update(float dt)
{
	static float offsetX = 0.0f;

	float scrollSpeed = 0.f; //pixels per second

	//Move the offset based on delta time and scroll speed
	offsetX += scrollSpeed * dt;


	//Wrapping the offset avoid going past the texture size
	if (offsetX > texture.getSize().x)
	{
		offsetX -= texture.getSize().x;
	}

	//updating the texture rect to create the scrolling effect
	setTextureRect(sf::IntRect(static_cast<int>(offsetX), 0, 1920, 1200));
}
