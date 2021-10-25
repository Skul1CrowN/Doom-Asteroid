#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<vector>
class Laser
{
private:
	sf::RectangleShape laser;

	float angle;
	float speed;
	sf::Vector2f velocity;
public:
	Laser(sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnLaser(sf::Vector2f player_position);

	void updateLaser();

	void renderLaser(sf::RenderTarget& target);
};