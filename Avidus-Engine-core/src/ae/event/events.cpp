#include "events.h"

namespace ae {
	EventHandler::EventHandler(sf::Event::EventType type) : m_Type(type) { }

	EventHandler::~EventHandler() {

	}

	void EventHandler::addListener(onEvent listener) {
		m_List.push_back(listener);
	}
}