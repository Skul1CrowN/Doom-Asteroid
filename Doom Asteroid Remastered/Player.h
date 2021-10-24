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
	int maxIntegrity;
	int hp;
	int maxHp;
	int shield;
	int maxShield;

	//Hull Breach
	bool hull_breach;
	float repaired;
	float repairRequired;
	float decayRate;

	//Combat
	int damage;
	int weapon_type;

	float speed;
	
	int score;

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
	int& getIntegrity();
	int& getMaxIntegrity();
	int& getHp();
	int& getHpMax();
	int& getShield();
	int& getShieldMax();

	bool& getHullBreach();
	float& getRepaired();
	float& getRepairRequired();

	int& getDamage();
	
	void receivedDamage(int damage);

	void receivedWorldDamage(int damage);

	void updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime);

	void renderPlayer(sf::RenderTarget& target);
};