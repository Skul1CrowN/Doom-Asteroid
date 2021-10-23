#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include "Bullet.h"

class Player
{
private:
	//Sprite
	sf::Texture* player_texture;
	sf::Sprite player_sprite;

	//Position
	sf::Vector2f player_position;
	sf::Vector2f mouse_distance;
	float angle;

	//Stat
	int integrity;
	int hp;
	int maxHp;
	float speed;
	int weapon_type;
	int score;
	bool is_immobility;

	//Mormal Bullet
	std::vector<Bullet> bullets;
	int normal_damage = 1;

	//Time
	float delayShoot;
	float maxDelayShoot;
public:
	Player(sf::Texture* texture);

	std::vector<Bullet>& get_bullets();
	sf::FloatRect getGlobalBounds();

	void updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime);

	void renderPlayer(sf::RenderTarget& target);
};