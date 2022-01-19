#include "Player.h"
v2f aggregate(std::vector<v2f> v)
{
	v2f s = NULL_VEC;
	for (auto element : v)
		s += element;
	return s;
}


Ship::Ship(std::shared_ptr<sf::Texture> texture)
{
	fueltank = sf::RectangleShape(v2f(160, 400)); 
	nose = sf::CircleShape(80, 20);
	nose.setOrigin(80, 80);
	engine_t = texture;
	
	engine_sprite.setTexture(*engine_t);
	engine_sprite.setOrigin(engine_t->getSize().x / 2.0f, engine_t->getSize().y / 2.0f);

	engine_collider.setOrigin(engine_t->getSize().x / 2.0f, engine_t->getSize().y / 2.0f);
	engine_collider.setSize(v2f(160, 160));
	fueltank.setOrigin(fueltank.getSize().x / 2.0f, fueltank.getSize().y / 2.0f);

	//offsets
	nose.move(0, -200);
	engine_sprite.move(0, 260);
	engine_collider.move(0, 260);
	mass = 50.0f;
}

void Ship::move(v2f m)
{
	nose.move(m);
	fueltank.move(m);
	engine_sprite.move(m);
	engine_collider.move(m);
}


void Ship::rotate(float deg)
{
	rotation += deg;
}

void Ship::setRotation(float new_rotation)
{
	rotation = new_rotation;
}

v2f Ship::getPosition()
{
	return fueltank.getPosition();
}

void Ship::setPosition(v2f n_pos)
{
	nose.setPosition(n_pos);
	engine_collider.setPosition(n_pos);
	engine_sprite.setPosition(n_pos);
	fueltank.setPosition(n_pos);
	nose.move(0, -200);
	engine_sprite.move(0, 260);
	engine_collider.move(0, 260);
}

float Ship::getRotation()
{
	return rotation;
}

PlayerCharacter::PlayerCharacter()
{
	player_c.setPosition(v2f(0.0f, 0.0f));
	mass = 50.0f;
	rotation = 0.0f;
	player_c.setSize(v2f(80, 200));
	player_c.setOrigin(40, 100);
	player_c.setFillColor(sf::Color::Green);
}

void PlayerCharacter::move(v2f m){
	player_c.move(m);
}

void PlayerCharacter::setPosition(v2f p)
{
	player_c.setPosition(p);
}

v2f PlayerCharacter::getPosition()
{
	return player_c.getPosition();
}

void PlayerCharacter::setRotation(float n_rotation)
{
	rotation = n_rotation;
}

void PlayerCharacter::rotate(float deg)
{
	rotation += deg;
}

float PlayerCharacter::getRotation()
{
	return rotation;
}
