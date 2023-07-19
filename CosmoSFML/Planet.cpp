#include "Planet.h"
Planet::Planet(sf::Vector3f color, float mass, float rad, v2f pos)
{
   planet.setFillColor(sf::Color(color.x, color.y, color.z));
   planet = sf::CircleShape(rad, 60);
   planet.setOrigin(rad, rad);
   planet.setPosition(pos);

   this->mass = mass;
}


Planet::Planet(int type, float mass, float radius, float orbit_rad, float rad, float rad_growth, v2f center)
{
   this->planet_type = type;
   planet = sf::CircleShape(radius, 360);
   switch (planet_type) {
   case GREEN:
      planet.setFillColor(sf::Color(0, 152, 26));
      break;
   case MATERIAL:
      planet.setFillColor(sf::Color::Color(20, 20, 20));
      break;
   case ENERGY:
      planet.setFillColor(sf::Color::Cyan);
      break;
   case INDUSTRIAL:
      planet.setFillColor(sf::Color::Red);
      break;
   case GAS:
      planet.setFillColor(sf::Color::Yellow);
      break;
   }
   float atmosphere_h = 4000.0f;
   atmosphere = sf::CircleShape((radius + 9000.0f), 60);
   atmosphere.setFillColor(sf::Color(0, 192, 232));
   atmosphere.setOrigin(radius + 9000.0f, radius + 9000.0f);
   //atmosphere.setPosition(pos);
   planet.setOrigin(radius, radius);
   this->orbit_radius = orbit_rad;
   this->rad = rad;
   this->rad_growth = rad_growth;
   this->mass = mass;
}

void Planet::initiate_enviorment()
{
   float ang_pos = (rand() % 60) + 20 / 360.0f;
   while (ang_pos <= 360.0f) {
      float range = (rand() % 10) + 1 / 360.0f;
      int type = rand() % WATER;
      for (float i = ang_pos; i < ang_pos + range;) {
         i += 10.0f;
         PlanetObject a = PlanetObject(type, ang_pos);
         this->objects.push_back(a);
      }
      ang_pos += range;
   }
}

v2f Planet::getPosition()
{
   return planet.getPosition();
}

void Planet::setPosition(v2f n_position)
{
   planet.setPosition(n_position);
   atmosphere.setPosition(n_position);
}

void Planet::move(v2f m)
{
   this->planet.move(m);
}

void Planet::rotate(float deg)
{
   this->rotation += deg;
}

void Planet::setRotation(float n_rotation)
{
   rotation = n_rotation;
}

float Planet::getRotation()
{
   return rotation;
}

void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(this->planet);
}

PlanetObject::PlanetObject(int type, float ang_pos) {
   this->collides = true;
   this->ang_pos = ang_pos;
   this->rot = ang_pos;
   this->type = type;
}

v2f PlanetObject::getPosition()
{
   return NULL_VEC;
}

void PlanetObject::setPosition(v2f n_pos)
{
   this->pos = n_pos;
}
