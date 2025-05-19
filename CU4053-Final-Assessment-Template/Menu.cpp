//#include<SFML/Graphics.hpp>
//#include<iostream>
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");
//
//	sf::Font font;
//	if (!font.loadFromFile("arial.ttf")) {
//		std::cerr << "Could not load font\n";
//		return -1;
//	}
//	sf::Text menu[3];
//	std::string menuItems[] = { "Start Game","Options","Exit" };
//	int selectedItem = 0;
//
//	for (int i = 0;i < 3;i++) {
//		menu[i].setFont(font);
//		menu[i].setString(menuItems[i]);
//		menu[i].setPosition(300, 200 + i * 50);
//		menu[i].setCharacterSize(40);
//		menu[i].setFillColor(i == selectedItem ? sf::Color::Red : sf::Color::White);
//	}
//	while (window.isOpen()) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//
//			if (event.type == sf::Event::KeyPressed) {
//				if (event.key.code == sf::Keyboard::Up) {
//					selectedItem = (selectedItem + 2) % 3;//loop backward
//				}
//				else if (event.key.code == sf::Keyboard::Down) {
//					selectedItem = (selectedItem + 1) % 3;//loop forward
//				}
//				else if (event.key.code == sf::Keyboard::Enter) {
//					if (selectedItem == 0) {
//						std::cout << "Start Game\n";
//					}
//					else if (selectedItem == 1) {
//						std::cout << "Options\n";
//					}
//					else if (selectedItem == 2) {
//						window.close();
//					}
//				}
//				//Update Menu Colors
//				for (int i = 0;i < 3;i++) {
//					menu[i].setFillColor(i == selectedItem ? sf::Color::Red : sf::Color::White);
//				}
//			}
//		}
//		window.clear();
//		for (int i = 0;i < 3;i++)
//			window.draw(menu[i]);
//		window.display();
//	}
//
//	return 0;
//
////}