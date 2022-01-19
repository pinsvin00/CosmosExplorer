#include "PlanetSystem.h"
PlanetSystem::PlanetSystem()
{
	int planet_count = (rand() % 5) + 5;
	main_planet = Planet(sf::Vector3f(255, 238, 0), 1.5e9, 1000, v2f(0, 0));
	float distance_from_main = 100000;
	int type;
	for (size_t i = 0; i < planet_count; i++) {
		//zalozenia do ruchu planet
		//najmniejsze na poczatku
		//najwieksze na koncu
		//najwolniejsze na koncu
		//najszybsze na poczatku

		float mass, radius, rad, rad_growth;
		rad_growth = 1.0f / (distance_from_main);
		radius = (rand() % (int)(distance_from_main / 20.0f)) + 34000.0f;
		mass = (rand() % (int)20e6) + 20e6;
		rad = rand() % 360;
		type = rand() % MATERIAL;
		if (i == 0) {
			type = GREEN;
		}
		Planet planet(type ,mass, radius, distance_from_main, rad, rad_growth, v2f(0, 0));
		distance_from_main += 150000;
		planet.initiate_enviorment();
		planet.setPosition(v2f(planet.orbit_radius * cos(planet.rad), planet.orbit_radius * sin(planet.rad)));
		planets.push_back(planet);
	}
}