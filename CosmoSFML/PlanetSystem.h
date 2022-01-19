#pragma once
#include <vector>
#include <iostream>
#include "Planet.h"
#include "AssetManager.h"
class PlanetSystem {
public:
	PlanetSystem();
	std::vector<Planet> planets;
	Planet main_planet;
};
