#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
class AssetManager
{
public:
	std::vector<std::pair<std::shared_ptr<sf::Texture>, std::string>> textures;
	std::vector<std::pair<std::shared_ptr<sf::Font>, std::string>> fonts;
	std::shared_ptr<sf::Texture> get_texture(std::string texture_name);
	std::shared_ptr<sf::Font> get_font(std::string texture_name);
	void add_texture(std::string texture_name);
	void add_texture(std::string texture_name, sf::Vector2u size);
	void add_font(std::string texture_name);
};

