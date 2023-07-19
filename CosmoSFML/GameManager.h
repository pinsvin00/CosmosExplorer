#pragma once
#include <functional>
#include <iostream>
#include "Menu.h"
#include "Environment.h"
#include "AssetManager.h"
class GameManager {
public:
   GameManager() {
      std::function<void(int)> f = std::bind(&GameManager::state_change_callback, this, std::placeholders::_1);
      am = std::make_shared<AssetManager>();
      am->add_texture("menu.png");
      am->add_texture("engine.png", sf::Vector2u(160, 160));
      am->add_texture("tree.png");
      am->add_texture("rock.png");
      am->add_texture("water.png");
      am->add_texture("mountain.png");
      am->add_font("arial.ttf");
      menu = Menu(f);
      env = Environment(f, am);
      state = MENU;
   }
   void state_change_callback(int state);
   std::shared_ptr<AssetManager> am;
   Menu menu;
   Environment env;
   int state;
};