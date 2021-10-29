#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include "Bullet.h"
#include "Laser.h"
#include "Plasma.h"
#include "Rocket.h"
#include "TriCannon.h"
#include "Mine.h"

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
	float speed;

	//Hull Breach
	bool hull_breach;
	float repaired;
	float repairRequired;
	float decayRate;

	//Combat
	int normal_damage;
	int laser_damage;
	int plasma_damage;
	int rocket_damage;
	int flak_damage;
	int tri_damage;
	int mine_damage;
	int weapon_type;
	//Time
	float delayShoot;
	float maxDelayShoot;
	// 1 Normal GUn
	// 2 Laser Shot
	// 3 Plasma Gun
	// 4 Rocket Launcher
	// 5 Tri-Cannon Gun
	// 6 Mine Launcher

	//Mormal Bullet
	std::vector<Bullet> bullets;

	//Laser Shot
	std::vector<Laser> lasers;
	int laser_ammo;

	//Plasma Gun
	std::vector<Plasma> plasmas;
	int plasma_ammo;

	//Rocket Launcher
	sf::Texture* rocket_texture;
	std::vector<Rocket> rockets;
	std::vector<Bullet> flaks;
	int rocket_ammo;

	//Tri Cannon
	sf::Texture* mine_texture;
	std::vector<TriCannon> tricannons;
	int tri_ammo;

	//Mine Launcher
	std::vector<Mine> mines;
	int mine_ammo;

	//System
	bool menu_cooldown;
public:
	Player(sf::Texture* texture, sf::Texture* rocket, sf::Texture* mine, int integrity);

	std::vector<Bullet>& get_bullets();
	std::vector<Laser>& get_lasers();
	std::vector<Plasma>& get_plasmas();
	std::vector<Rocket>& get_rockets();
	std::vector<Bullet>& get_flaks();
	std::vector<Mine>& get_mines();
	std::vector<TriCannon>& get_tricannons();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	int& getIntegrity();
	int& getMaxIntegrity();
	int& getHp();
	int& getHpMax();
	int& getShield();
	int& getShieldMax();
	int& getWeaponType();
	int& getLaserAmmo();
	int& getPlasmaAmmo();
	int& getRocketAmmo();
	int& getTriAmmo();
	int& getMineAmmo();
	void explosionFlak(sf::Vector2f position);

	bool& getHullBreach();
	float& getRepaired();
	float& getRepairRequired();

	int& getNormalDamage();
	int& getLaserDamage();
	int& getPlasmaDamage();
	int& getRocketDamage();
	int& getFlakDamage();
	int& getTriDamage();
	int& getMineDamage();

	void setMenuFreeze(bool menu_cooldown);
	
	void repairHP(int hp);

	void receivedShield(int shield);

	void gainLaserAmmo(int amount);
	void gainPlasmaAmmo(int amount);
	void gainRocketAmmo(int amount);
	void gainTriAmmo(int amount);
	void gainMineAmmo(int amount);

	void receivedDamage(int damage);

	void receivedWorldDamage(int damage);

	void updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime);

	void renderPlayer(sf::RenderTarget& target);
};