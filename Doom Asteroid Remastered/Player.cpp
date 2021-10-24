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
	this->integrity = 658;
	this->maxHp = 20;
	this->hp = this->maxHp;
	this->maxShield = 10;
	this->shield = 0;
	
	this->damage = 1;
	this->weapon_type = 1;

	this->speed = 1.f;

	this->maxDelayShoot = 0.35f;
	this->delayShoot = this->maxDelayShoot;

	this->score = 0;
}

std::vector<Bullet>& Player::get_bullets()
{
	return this->bullets;
}

sf::FloatRect Player::getGlobalBounds()
{
	return this->player_sprite.getGlobalBounds();
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

int& Player::getDamage()
{
	return this->damage;
}

void Player::updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime)
{
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
	this->player_sprite.setRotation(this->angle);

	//Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player_position.y > 50.f)
	{
		this->player_sprite.move(0.0f, -(this->speed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_position.x > 50.f)
	{
		this->player_sprite.move(-(this->speed), 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player_position.y < window->getSize().y - 50.f)
	{
		this->player_sprite.move(0.0f, this->speed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_position.x < window->getSize().x - 50.f)
	{
		this->player_sprite.move(this->speed, 0.0f);
	}

	//Combat
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->delayShoot >= this->maxDelayShoot)
	{
		this->bullets.push_back(Bullet(player_position, angle));
		this->delayShoot = 0;
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
	target.draw(player_sprite);
}