#include <SFML/Graphics.hpp>

int main(void) {
	sf::RenderWindow window(sf::VideoMode(200, 200), "Avidus Engine");
	sf::CircleShape shape(100.f);
	window.setFramerateLimit(60);
	shape.setFillColor(sf::Color::Blue);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}