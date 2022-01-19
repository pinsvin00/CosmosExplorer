#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "globals.h"
extern AssetManager am;
enum planet_types {
	GREEN,
	INDUSTRIAL,
	ENERGY,
	MATERIAL,
	GAS
};

enum obj_types {
	TREE,
	ROCK,
	MOUNTAIN,
	WATER
};

class PlanetObject : public IStaticObject {
public:	
	PlanetObject(int type, float ang_pos);
	unsigned int type;
	float ang_pos;
	std::vector<sf::RectangleShape> colliders;
	bool collides;
	v2f getPosition();
	void setPosition(v2f n_pos);
	void setRotation(float rot) {
		this->rot = rot;
	}
	v2f pos;
	float rot;
};

class Planet : public IPhysObject , public sf::Drawable{
public:
	sf::CircleShape planet;
	sf::CircleShape atmosphere;
	Planet() = default;
	int planet_type;
	float orbit_radius = 0.0f;
	float rad = 0.0f;
	float rad_growth = 0.0f;
	std::vector<PlanetObject> objects;
	std::vector<std::pair<int, float>> biomes;
	Planet(sf::Vector3f color, float mass, float radius, v2f pos);
	Planet(int type,float mass, float radius, float orbit_rad, float rad, float rad_growth, v2f center);


	void initiate_enviorment();

	v2f getPosition();
	void setPosition(v2f n_position);
	void move(v2f m);
	float rotation;
	void rotate(float deg);
	void setRotation(float n_rotation);
	float getRotation();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};