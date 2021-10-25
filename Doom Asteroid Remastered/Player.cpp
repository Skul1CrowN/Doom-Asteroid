#include "Player.h"

#include<cmath>
#include<iostream>

Player::Player(sf::Texture* texture)
{
	this->player_texture = texture;
	this->player_sprite.setTexture(*this->player_texture);
	this->player_sprite.setScale(sf::Vector2f(0.15f, 0.15f));
	this->player_sprite.setPosition(sf::Vector2f(50.f, 540.f));
	this->angle = 0;

	this->maxIntegrity = 1000;
	this->integrity = this->maxIntegrity;
	this->maxHp = 100;
	this->hp = this->maxHp;
	this->maxShield = 50;
	this->shield = 0;

	this->hull_breach = 0;
	this->repaired = 0.f;
	this->repairRequired = 10.f;
	this->decayRate = 0.2;

	this->damage = 1;
	this->weapon_type = 1;
	this->laser_ammo = 0;
	this->plasma_ammo = 0;

	this->speed = 500.f;

	this->maxDelayShoot = 0.35f;
	this->delayShoot = this->maxDelayShoot;
}

std::vector<Bullet>& Player::get_bullets()
{
	return this->bullets;
}

std::vector<Laser>& Player::get_lasers()
{
	return this->lasers;
}

std::vector<Plasma>& Player::get_plasmas()
{
	return this->plasmas;
}

sf::FloatRect Player::getGlobalBounds()
{
	return this->player_sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
	return this->player_sprite.getPosition();
}

int& Player::getIntegrity()
{
	return this->integrity;
}

int& Player::getMaxIntegrity()
{
	return this->maxIntegrity;
}

int& Player::getHp()
{
	return this->hp;
}

int& Player::getHpMax()
{
	return this->maxHp;
}

int& Player::getShield()
{
	return this->shield;
}

int& Player::getShieldMax()
{
	return this->maxShield;
}

bool& Player::getHullBreach()
{
	return this->hull_breach;
}

float& Player::getRepaired()
{
	return this->repaired;
}

float& Player::getRepairRequired()
{
	return this->repairRequired;
}

int& Player::getDamage()
{
	return this->damage;
}

void Player::repairHP(int hp)
{
	this->hp += hp;
	if (this->hp > this->maxHp)
		this->hp = this->maxHp;
}

void Player::receivedShield(int shield)
{
	this->shield += shield;
	if (this->shield > this->maxShield)
		this->shield = this->maxShield;
}

void Player::gainLaserAmmo(int amount)
{
	this->laser_ammo += amount;
}

void Player::gainPlasmaAmmo(int amount)
{
	this->plasma_ammo += amount;
}

void Player::receivedDamage(int damage)
{
	if (this->shield > 0)
	{
		this->shield -= damage;
		if (this->shield < 0)
			this->shield = 0;
	}
	else
	{
		this->hp -= damage;
		if (this->hp < 0)
			this->hp = 0;
	}
}

void Player::receivedWorldDamage(int damage)
{
	this->integrity -= damage;
	if (this->integrity < 0)
		this->integrity = 0;
}

void Player::updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime)
{
	//Check Hull breach
	if (this->hp <= 0)
	{
		this->hull_breach = 1;
	}

	if (this->hull_breach)
		this->player_sprite.setColor(sf::Color(128, 128, 128));
	else
		this->player_sprite.setColor(sf::Color(255, 255, 255));

	//Update Position
	this->player_position = this->player_sprite.getPosition();

	//Update Center
	this->player_sprite.setOrigin(sf::Vector2f(
		this->player_sprite.getLocalBounds().width / 2,
		this->player_sprite.getLocalBounds().height / 2)
	);

	//Rotation
	this->mouse_distance = mouse_position - player_position;
	if (mouse_distance.y < 0)
		this->angle = -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	else
		this->angle = 180 + -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	if (!this->hull_breach)
		this->player_sprite.setRotation(this->angle);

	//Movement
	if (!this->hull_breach)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player_position.y > 50.f)
		{
			this->player_sprite.move(0.0f, -(this->speed) * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_position.x > 50.f)
		{
			this->player_sprite.move(-(this->speed) * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player_position.y < window->getSize().y - 50.f)
		{
			this->player_sprite.move(0.0f, this->speed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_position.x < window->getSize().x - 50.f)
		{
			this->player_sprite.move(this->speed * deltaTime, 0.0f);
		}
	}

	//Combat
	if (!this->hull_breach)
	{
		//Shoot
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->delayShoot >= this->maxDelayShoot)
		{
			switch (this->weapon_type)
			{
			case 1:
				this->bullets.push_back(Bullet(player_position, angle));
				break;
			case 2:
				if (this->laser_ammo > 0)
				{
					this->laser_ammo--;
					this->lasers.push_back(Laser(player_position, angle));
				}
				break;
			case 3:
				if (this->plasma_ammo > 0)
				{
					this->plasma_ammo--;
					this->plasmas.push_back(Plasma(player_position, angle));
				}
				break;
			default:
				break;
			}
			this->delayShoot = 0;
		}
		//Switch Weapon
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			this->weapon_type = 1;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.35f;
			this->maxDelayShoot = 0.35f;
			this->damage = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && this->laser_ammo > 0)
		{
			this->weapon_type = 2;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.55f;
			this->maxDelayShoot = 0.55f;
			this->damage = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && this->plasma_ammo > 0)
		{
			this->weapon_type = 3;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.1f;
			this->maxDelayShoot = 0.1f;
			this->damage = 1;
		}
	}

	//Hull Breach
	if (this->hull_breach)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->repaired += deltaTime;
		}
		else
		{
			this->repaired -= deltaTime * this->decayRate;
			if (this->repaired < 0)
				this->repaired = 0;
		}

		if (this->repaired >= this->repairRequired)
		{
			this->hp += this->maxHp * 0.4f;
			this->hull_breach = 0;
			this->repaired = 0;
			this->repairRequired += 5.f;
			this->decayRate += 0.15f;
			if (this->repairRequired > 90.f)
				this->repairRequired = 90.f;
			if (this->decayRate > 1.7f)
				this->decayRate = 1.7f;
		}
	}

	//Time Update
	if (this->delayShoot < this->maxDelayShoot)
		this->delayShoot += deltaTime;
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].renderBullet(target);
	}
	for (int i = 0; i < this->lasers.size(); i++)
	{
		this->lasers[i].renderLaser(target);
	}
	for(int i = 0;i < this->plasmas.size();i++)
	{
		this->plasmas[i].renderPlasma(target);
	}
	target.draw(player_sprite);
}