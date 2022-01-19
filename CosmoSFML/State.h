#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
class IState {
public:
	virtual void process_input() {
		return;
	};
	sf::Time last_press;
	std::function<void(int)> sm_callback;
};
