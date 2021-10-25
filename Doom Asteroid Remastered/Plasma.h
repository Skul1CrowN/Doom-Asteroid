#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Plasma
{
private:
	sf::CircleShape plasma;

	float speed;
	float angle;
	sf::Vector2f velocity;

public:
	Plasma(sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnPlasma(sf::Vector2f player_position);

	void updatePlasma();

	void renderPlasma(sf::RenderTarget& target);
};

