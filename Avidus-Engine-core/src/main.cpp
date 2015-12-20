#include <ae/avidus.h>
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

	void Init() override {
		window = CreateWindow("SFML Test", 200, 200);
		shape = new CircleShape(100.f);
		shape->setFillColor(Color::Red);
	}

	void Tick() override {
		std::cout << "FPS: " << GetFPS() << std::endl << "UPS: " << GetUPS() << std::endl;
	}

	void Update() override {

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