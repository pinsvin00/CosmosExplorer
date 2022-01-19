#ifndef SM_H

#define SM_H
#include <SFML/Graphics.hpp>
#include "globals.h"
#include "State.h"
#include <iostream>
#include <functional>
extern sf::Clock cloc;

class Menu : IState{
public:
	Menu(std::function<void(int)> callback) {
		selector.setSize(v2f(400, 50));
		selector.setFillColor(sf::Color::Cyan);
		this->sm_callback = callback;
	}
	Menu() = default;

	int selected_option = 0;
	sf::RectangleShape selector;
	sf::Sprite graphic_menu;
	void choose() {
		sm_callback(selected_option);
	}
	void process_input() override;
};
#endif
