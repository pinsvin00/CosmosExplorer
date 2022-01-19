#include "Menu.h"

//void Menu::process()
//{
//	selector.setPosition(v2f(0, (font_size + gap) * (float)selected_option) + v2f(0, 300));
//}

void Menu::process_input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
		std::cout << (cloc.getElapsedTime() - last_press).asSeconds() << std::endl;
		selected_option--;
		last_press = cloc.getElapsedTime();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
		std::cout << (cloc.getElapsedTime() - last_press).asSeconds() << std::endl;
		selected_option++;
		last_press = cloc.getElapsedTime();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (cloc.getElapsedTime() - last_press).asSeconds() >= 0.5f) {
		std::cout << (cloc.getElapsedTime() - last_press).asSeconds() << std::endl;
		choose();
		last_press = cloc.getElapsedTime();
	}
}
