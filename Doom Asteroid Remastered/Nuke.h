#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Nuke
{
private:
	sf::Texture* nuke_texture;
	sf::RectangleShape nuke_sprite;

	sf::Vector2f velocity;
	float angle;
	float speed;

public:
	Nuke(sf::Texture* texture, sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnNuke(sf::Vector2f player_position);

	void updateNuke(float deltaTime);

	void renderNuke(sf::RenderTarget& target);
};

