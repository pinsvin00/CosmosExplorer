#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Utils.h"
#include "Player.h"
#include "Planet.h"
#include "PlanetSystem.h"
#include "AssetManager.h"
#define M 100
template <class T1>
void gravity_forces(Planet planet, T1& phys_o);

class Environment : IState , public sf::Drawable {
public:
	Environment(std::function<void(int)> callback, std::shared_ptr<AssetManager> am);
	Environment() = default;
	std::vector<v2f> v;
	Ship ship;
	PlayerCharacter player;
	std::vector<IPhysObject> o;
	sf::Texture tree;
	sf::Texture water;
	sf::Texture mountain;
	sf::Texture rock;
	std::shared_ptr<AssetManager> am;
	std::vector<PlanetObject> planet_objects;
	std::function<void(int)> sm_callback;
	PlanetSystem main;
	sf::View camera;
	void process_player_vertices();
	void process_camera();
	void process_player_matrix();
	float zoom = 1.0f;
	bool is_player_out = true;

	void on_load();
	void process();
	void process_planets();
	void process_player();
	void process_input() override;
	sf::Vector2u getSize(int type, v2f scale);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

template<class T1>
inline void gravity_forces(Planet planet, T1& phys_o)
{
	v2f dis = v2f(planet.planet.getPosition().x - phys_o.getPosition().x,
		planet.planet.getPosition().y - phys_o.getPosition().y);
	float dis_sq = sqrt(dis.x * dis.x + dis.y * dis.y);
	float r = distance_beetween(phys_o.getPosition(), planet.planet.getPosition());
	float f = (phys_o.mass * planet.mass) / (dis_sq * dis_sq);
	phys_o.gravity_acceleration.x += ((f * dis.x) / dis_sq) / phys_o.mass;
	phys_o.gravity_acceleration.y += ((f * dis.y) / dis_sq) / phys_o.mass;
	return;
}

