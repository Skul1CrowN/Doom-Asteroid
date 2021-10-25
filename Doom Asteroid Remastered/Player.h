#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include "Bullet.h"
#include "Laser.h"

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
	// 1 Normal GUn
	// 2 Laser Shot
	// 3 Rocket Launcher
	// 4 Tri-Cannon Gun
	// 5 Mine Launcher

	float speed;
	
	int score;

	//Mormal Bullet
	std::vector<Bullet> bullets;

	//Laser Shot
	std::vector<Laser> lasers;
	int laser_ammo;

	//Time
	float delayShoot;
	float maxDelayShoot;
public:
	Player(sf::Texture* texture);

	std::vector<Bullet>& get_bullets();
	std::vector<Laser>& get_lasers();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
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
	
	void repairHP(int hp);

	void receivedShield(int shield);

	void gainLaserAmmo(int amount);

	void receivedDamage(int damage);

	void receivedWorldDamage(int damage);

	void updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime);

	void renderPlayer(sf::RenderTarget& target);
};