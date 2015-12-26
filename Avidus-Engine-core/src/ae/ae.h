#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "event\Events.h"

namespace ae {

	class Avidus {
	private:
		friend class Input;

		sf::RenderWindow* m_Window;
		sf::Clock* m_Clock;
		sf::Time m_TimeBetweenFrames;

		bool m_hasFocus;
		unsigned int m_FramesPerSecond, m_UpdatesPerSecond;
	public:
		// Misc
		EventHandler* Closed;
		EventHandler* Resized;
		EventHandler* LostFocus;
		EventHandler* GainedFocus;
		EventHandler* TextEntered;

		// Keyboard
		EventHandler* KeyPressed;
		EventHandler* KeyReleased;

		// Mouse
		EventHandler* MouseWheelMoved;
		EventHandler* MouseButtonPressed;
		EventHandler* MouseButtonReleased;
		EventHandler* MouseMoved;
		EventHandler* MouseEntered;
		EventHandler* MouseLeft;
	protected:
		Avidus() : m_hasFocus(true), m_FramesPerSecond(0), m_UpdatesPerSecond(0) { }

		virtual ~Avidus() {
			delete m_Clock;
			delete m_Window;
		}

		sf::RenderWindow* CreateWindow(const char *name, int width, int height) {
			m_Window = new sf::RenderWindow(sf::VideoMode(width, height), name);
			m_Window->setFramerateLimit(240);
			return m_Window;
		}
	public:
		void Start() {
			// Misc
			Closed = new EventHandler(sf::Event::Closed);
			Resized = new EventHandler(sf::Event::Resized);
			LostFocus = new EventHandler(sf::Event::LostFocus);
			GainedFocus = new EventHandler(sf::Event::GainedFocus);
			TextEntered = new EventHandler(sf::Event::TextEntered);

			// Keyboard
			KeyPressed = new EventHandler(sf::Event::KeyPressed);
			KeyReleased = new EventHandler(sf::Event::KeyReleased);

			// Mouse
			MouseWheelMoved = new EventHandler(sf::Event::MouseWheelMoved);
			MouseButtonPressed = new EventHandler(sf::Event::MouseButtonPressed);
			MouseButtonReleased = new EventHandler(sf::Event::MouseButtonReleased);
			MouseMoved = new EventHandler(sf::Event::MouseMoved);
			MouseEntered = new EventHandler(sf::Event::MouseEntered);
			MouseLeft = new EventHandler(sf::Event::MouseLeft);

			Init();
			Run();
		}

		bool isKeyPressed(sf::Keyboard::Key k) const
		{
			bool const pressed = m_hasFocus && sf::Keyboard::isKeyPressed(k);
			return pressed;
		}

		sf::Vector2i mousePosition() const
		{
			return sf::Mouse::getPosition(*m_Window);
		}

		bool isMouseButtonPressed(sf::Mouse::Button b) const
		{
			return m_hasFocus && sf::Mouse::isButtonPressed(b);
		}
	protected:
		virtual void Init() = 0;
		virtual void Tick() { }
		virtual void Update() { }
		virtual void Draw() = 0;

		sf::Time GetTimeBetweenFrames() const { return m_TimeBetweenFrames; }
		const unsigned int GetFPS() const { return m_FramesPerSecond; }
		const unsigned int GetUPS() const { return m_UpdatesPerSecond; }
	private:
		void Run() {
			m_Clock = new sf::Clock();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			sf::Event event;
			while (m_Window->isOpen())
			{
				m_TimeBetweenFrames = m_Clock->restart();
				timer += m_TimeBetweenFrames.asSeconds();
				updateTimer += m_TimeBetweenFrames.asSeconds();

				using sf::Event;
				while (m_Window->pollEvent(event)) {
					if (event.type == sf::Event::Closed) m_Window->close();
					switch (event.type) {
						// Misc
						case Event::Closed: Closed->dispatch(event); break;
						case Event::Resized: Resized->dispatch(event); break;
						case Event::LostFocus: m_hasFocus = false; LostFocus->dispatch(event); break;
						case Event::GainedFocus: m_hasFocus = true; GainedFocus->dispatch(event); break;
						case Event::TextEntered: TextEntered->dispatch(event); break;

						// Keyboard
						case Event::KeyPressed: KeyPressed->dispatch(event); break;
						case Event::KeyReleased: KeyReleased->dispatch(event); break;

						// Mouse
						case Event::MouseWheelMoved: MouseWheelMoved->dispatch(event); break;
						case Event::MouseButtonPressed: MouseButtonPressed->dispatch(event); break;
						case Event::MouseButtonReleased: MouseButtonReleased->dispatch(event); break;
						case Event::MouseMoved: MouseMoved->dispatch(event); break;
						case Event::MouseEntered: MouseEntered->dispatch(event); break;
						case Event::MouseLeft: MouseLeft->dispatch(event); break;

						case Event::Count:
						default:
							std::cout << "unknown sf::Event::type: " << event.type << std::endl;
						break;
					}
				}

				if (updateTimer >= updateTick) {
					updateTimer = 0.0f;
					Update();
					updates++;					
				}
				m_Window->clear();
				Draw();
				m_Window->display();
				frames++;				
				if (timer >= 1.0f) {
					timer = 0.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					Tick();
				}
			}
		}
	};

}