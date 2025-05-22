#include "Level.h"
#include "Framework/Utilities.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	view = v;
	world = w;
	tileManager = tm;
	audioManager = new AudioManager();

	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	//Collectables Collected Text
	CollectablesCollectedText.setFont(font);
	CollectablesCollectedText.setCharacterSize(36);
	CollectablesCollectedText.setFillColor(sf::Color::Red);
	CollectablesCollectedText.setPosition(window->getSize().x, 0);
	CollectablesCollectedText.setString("Collected: ");

	world->AddGameObject(player);
	player.setInput(in);
	player.setWorld(w);

	//sets up enemy locations
	enemyArray[0].setPosition(1638, 384);
	enemyArray[1].setPosition(2363, 390);
	enemyArray[2].setPosition(3740, -275);
	enemyArray[3].setPosition(9800, 608);
	enemyArray[4].setPosition(3986, -275);
	enemyArray[5].setPosition(5955, -210);
	enemyArray[6].setPosition(6729, -285);
	enemyArray[7].setPosition(6767, 175);
	enemyArray[8].setPosition(7773, 212);
	enemyArray[9].setPosition(8628, 275);
	enemyArray[10].setPosition(9149, 947);
	enemyArray[11].setPosition(10171, 450);
	enemyArray[12].setPosition(10883, 643);
	enemyArray[13].setPosition(14650, -3);
	enemyArray[14].setPosition(15670, 39);
	enemyArray[15].setPosition(16180, 305);
	enemyArray[16].setPosition(16562, 341);
	enemyArray[17].setPosition(16363, -230);
	//adds enemies to world
	for (int i = 0; i < 5; i++) {
		world->AddGameObject(enemyArray[i]);
	}
}

Level::~Level()
{
	//Making pointers null
	window = nullptr;
	input = nullptr;
	gameState = nullptr;
	view = nullptr;
	world = nullptr;
	tileManager = nullptr;
	if (audioManager != nullptr) {
		delete audioManager;
		audioManager = nullptr;
	}
}

void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		input->setKeyUp(sf::Keyboard::Tab);
		gameState->setCurrentState(State::TILEEDITOR);
	}
	player.handleInput(dt);
	for (int i = 0; i < 5; i++) {
		enemyArray[i].handleInput(dt);
	}
}

// Update game objects
void Level::update(float dt)
{
	bg.update(dt);

	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	CollectablesCollectedText.setPosition(view->getCenter().x - viewSize.x / 14, view->getCenter().y - viewSize.y / 2);

	for (int i = 0; i < 5; i++) {
		if (enemyArray[i].CollisionWithTag("Player")) {
			player.ReduceHealth(0.01 * dt);
		}
	}

	if (player.CollisionWithTag("Collectable"))
	{
		// Player is Colliding with Collectable
		player.AddCollectable(); // Increment Collectable count
		tileManager->RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = player.getCollectableCount(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	//checks for dead player
	if ((player.getHealth() <= 0) || (player.getPosition().y > 1920))
	{
		player.setPosition(100, 100);
		player.setAlive(false);
		world->RemoveGameObject(player);
		view->setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		gameState->setCurrentState(State::DEAD);
	}

	//checks if enemy is alive then removes them if not
	for (int i = 0; i < 5; i++) {
		if (!enemyArray[i].isAlive()) {
			world->RemoveGameObject(enemyArray[i]);
		}
	}



	//Move the view to follow the player
	view->setCenter(view->getCenter().x, 360);
	
	sf::Vector2f playerPosition = player.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);
}

// Render level
void Level::render()
{
	window->draw(CollectablesCollectedText);

	window->draw(player);
	for (int i = 0; i < 5; i++) {
		if (enemyArray[i].isAlive())
		{
			window->draw(enemyArray[i]);
			//window->draw(enemyArray[i].getDebugCollisionBox());
		}
	}

	for (int i = 0; i < 5; i++) {
		if (enemyArray[i].isAlive())
		{
			window->draw(enemyArray[i]);
			//window->draw(enemyArray[i].getDebugCollisionBox());
		}
	}

	auto bullets = player.getBullets();
	for (auto& bullet : bullets)
	{
		window->draw(*bullet);
	}
	if (gameState->getCurrentState() == State::LEVEL)
	{
		tileManager->render(false);
	}

}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height) 
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}