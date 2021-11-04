#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Mine
{
private:
	sf::Texture* mine_texture;
	sf::RectangleShape mine_sprite;
	int maxHp;
	int hp;

	sf::Vector2f mine_position;

	sf::Vector2f velocity;
	float acceleration;
	float angle;
	float speed;

	//Mine HpBar
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarMax;
public:
	Mine(sf::Texture* texture, sf::Vector2f player_position, float angle);

	int& getHealth();

	sf::FloatRect getGlobalBounds();
	sf::Vector2f get_position();

	void spawnMine(sf::Vector2f player_position);

	void receivedDamage(int damage);

	void updateMine(float deltaTime);

	void renderMine(sf::RenderTarget& target);
};

