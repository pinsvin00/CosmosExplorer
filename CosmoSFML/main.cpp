#include <iostream>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "GameManager.h"
#include <ctime>
//#include <SFML/Graphics.hpp>

sf::Clock cloc;
int main()
{
   srand(time(NULL));
   sf::RenderWindow window(sf::VideoMode(1280, 720), "Cosmos Explorer");
   GameManager gm;
   window.setFramerateLimit(60);
   sf::Font font;
   if (!font.loadFromFile("res/arial.ttf")) {
      std::cout << "Unable to load arial.ttf\n";
      return -1;
   }
   std::vector<sf::Text> menu_options;
   int font_size = 30;
   int gap = 50;
   menu_options.push_back(sf::Text("Start Game", font, 50));
   menu_options.push_back(sf::Text("Options", font, 50));
   menu_options.push_back(sf::Text("Exit game", font, 50));

   sf::Time last_time = cloc.getElapsedTime();
   sf::Time last_press = cloc.getElapsedTime();
   while (window.isOpen())
   {
      sf::Event event;
      sf::Time delta = cloc.getElapsedTime() - last_time;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed)
            window.close();
      }
      window.clear();
      if (gm.state == MENU) {
         //ok
         gm.menu.process_input();
         gm.menu.selector.setPosition(v2f(0, (font_size + gap) * (float)gm.menu.selected_option) + v2f(0, 150));
         gm.menu.selector.setFillColor(sf::Color::Cyan);
         window.draw(gm.menu.selector);
         sf::Text cosmox("CosmoXplorer", font, 100);
         cosmox.setPosition(v2f(0, 0));
         window.draw(cosmox);
         sf::Vector2f pos = sf::Vector2f(0, 150);
         for (auto& element : menu_options) {
            element.setPosition(pos);
            element.setFillColor(sf::Color::White);
            pos.y += 75;
            window.draw(element);
         }
      }
      else if (gm.state == GAME) {
         gm.env.process_input();
         gm.env.process();
         window.draw(gm.env);
      }
      window.display();
      last_time = cloc.getElapsedTime();
   }
   return 0;
}