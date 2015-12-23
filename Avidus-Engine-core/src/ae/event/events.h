#pragma once

#include <list>
#include <SFML\Graphics.hpp>

namespace ae {

	class EventHandler {
	private:
		friend class Avidus;

		typedef void(*onEvent)();

		sf::Event::EventType m_Type;
		std::list<onEvent> m_List;
	public:
		EventHandler(sf::Event::EventType type);
		~EventHandler();

		void addListener(onEvent listener);
	};
}