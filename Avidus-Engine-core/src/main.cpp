#include <ae/avidus.h>
#include <ae/event/events.h>
#include <iostream>

using namespace ae;
using namespace sf;

class Game : public Avidus {
private:
	RenderWindow* window;
	CircleShape* shape;
public:
	Game() {

	}

	~Game() {
		delete shape;
	}

	void onEventClosed(sf::Event event) {
		window->close();
		std::cout << "Closed!" << std::endl;
	}

	void Init() override {
		using namespace std::placeholders;

		window = CreateWindow("SFML Test", 200, 200);
		shape = new CircleShape(100.f);
		shape->setFillColor(Color::Red);

		Closed->addListener(std::bind(&Game::onEventClosed, this, _1));
	}
	void Tick() override {
		std::cout << "FPS: " << GetFPS() << std::endl << "UPS: " << GetUPS() << std::endl;
	}

	void Update() override {
		using sf::Keyboard;

		if (isKeyPressed(Keyboard::Key::A)) {
			std::cout << "Left" << std::endl;
		}
	}

	void Draw() override {
		window->draw(*shape);
	}
};

int main() {
	Game game;
	game.Start();
	return 0;
}