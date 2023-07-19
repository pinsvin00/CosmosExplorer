#ifndef PLAYER_H
#define PLAYER_H
#include "globals.h"
#include <vector>
#include "Menu.h"
#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>
v2f aggregate(std::vector<v2f> v);


extern sf::Clock cloc;

struct Engine {
   float throttle = 0.0f;
   float fuel = 100.0f;
   bool isWorking = false;
   float power = 0.0f;
   float max_power = 15.0f;
   float grow = 0.1f;
   void process() {
      float a_max = max_power * throttle;
      if (a_max <= power) {
         power -= grow;
      }
      else {
         power += grow;
      }
   }
};

class PlayerCharacter : public sf::Drawable, public IPhysObject {
public:
   PlayerCharacter();
   sf::RectangleShape player_c;
   sf::Transform t;
   void move(v2f m);
   void setPosition(v2f n_position);
   v2f getPosition();
   void setRotation(float n_rotation);
   void rotate(float deg);
   float getRotation();
   v2f mdir = NULL_VEC;
   float rotation;
private:
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
      sf::Transform transform_character;
      transform_character.rotate(rotation, player_c.getPosition());
      target.draw(player_c, transform_character);
   }
};

class Ship : public sf::Drawable, public IPhysObject {
public:
   sf::RectangleShape fueltank;
   sf::Transform t_fueltank;

   sf::RectangleShape engine_collider;
   sf::Sprite engine_sprite;
   Engine engine;
   std::shared_ptr<sf::Texture> engine_t;
   sf::Transform t_engine;

   sf::CircleShape nose;
   sf::Transform t_nose;

   Ship(std::shared_ptr<sf::Texture> texture);
   Ship() = default;

   void move(v2f m);
   v2f getPosition();
   void setPosition(v2f n_pos);
   float getRotation();
   void rotate(float deg);
   void setRotation(float new_rotation);

   //CHARACTER
private:
   float rotation = 0.0f;
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
      sf::Transform tn;
      tn.rotate(rotation, v2f(0, 200) + nose.getPosition());
      target.draw(nose, tn);
      sf::Transform tt;
      tt.rotate(rotation, fueltank.getPosition());
      target.draw(fueltank, tt);
      sf::Transform te;
      te.rotate(rotation, engine_sprite.getPosition() - v2f(0, 260));
      target.draw(engine_sprite, te);
   }
};
#endif
