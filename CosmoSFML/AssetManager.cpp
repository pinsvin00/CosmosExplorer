#include "AssetManager.h"

std::shared_ptr<sf::Texture> AssetManager::get_texture(std::string texture_name)
{
	for (const auto& element : textures) {
		if (element.second == texture_name)
			return element.first;
	}
	std::cout << "Unable to find texture " + texture_name << std::endl;
	return NULL;
}

std::shared_ptr<sf::Font> AssetManager::get_font(std::string font_name)
{
	for (const auto& element : fonts) {
		if (element.second == font_name)
			return element.first;
	}
	std::cout << "Unable to find font " + font_name << std::endl;
	return NULL;
}

void AssetManager::add_texture(std::string texture_name)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared < sf::Texture >() ;
	if (!texture->loadFromFile(texture_name)) {
		std::cout << "FATAL ERROR\n Couldn't open texture at " + texture_name << std::endl;
		abort();
	}
	textures.push_back(std::make_pair(texture, texture_name));
}
void AssetManager::add_texture(std::string texture_name, sf::Vector2u size)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared < sf::Texture >();
	if (!texture->loadFromFile(texture_name, sf::IntRect(0,0, size.x, size.y))) {
		std::cout << "FATAL ERROR\n Couldn't open texture at " + texture_name << std::endl;
		abort();
	}
	textures.push_back(std::make_pair(texture, texture_name));
}

void AssetManager::add_font(std::string font_name)
{
	std::shared_ptr<sf::Font> font;
	if (!font->loadFromFile("arial.ttf")) {
		std::cout << "FATAL ERROR\n Couldn't open font at " + font_name << std::endl;
		abort();
	}
	fonts.push_back(std::make_pair(font, font_name));
}
