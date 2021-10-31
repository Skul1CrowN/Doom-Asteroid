#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class TriCannon
{
private:
	sf::Texture* tri_texture;
	sf::RectangleShape tricannon;

	float speed;
	float angle;
	sf::Vector2f velocity;

public:
	TriCannon(sf::Texture *texture,sf::Vector2f player_position, float angle);

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnTriCannon(sf::Vector2f player_position);

	void updateTriCannon(float deltaTime);

	void renderTriCannon(sf::RenderTarget& target);
};