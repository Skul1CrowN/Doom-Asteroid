#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Rocket
{
private:
	sf::Texture* rocket_texture;
	sf::RectangleShape rocket_sprite;

	sf::Vector2f velocity;
	float angle;
	float speed;

public:
	Rocket(sf::Texture* texture, sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnRocket(sf::Vector2f player_position);

	void updateRocket(float deltaTime);

	void renderRocket(sf::RenderTarget& target);
};

