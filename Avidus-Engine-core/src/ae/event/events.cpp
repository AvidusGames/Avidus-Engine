#include "events.h"

namespace ae {
	EventHandler::EventHandler(sf::Event::EventType type) : m_Type(type) { }

	EventHandler::~EventHandler() {

	}

	void EventHandler::addListener(onEvent listener) {
		m_List.push_back(listener);
	}

	void EventHandler::dispatch(sf::Event event) {
		for (std::list<onEvent>::iterator i = m_List.begin(); i != m_List.end(); ++i)
			(*i)(event);
	}
}