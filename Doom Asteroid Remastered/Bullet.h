#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<vector>
class Bullet
{
private:
	sf::RectangleShape bullet;

	float angle;
	float speed;
	sf::Vector2f velocity;
public:
	Bullet(sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnBullet(sf::Vector2f player_position);

	void updateBullet();

	void renderBullet(sf::RenderTarget& target);
};