#include "Bullet.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include<cmath>
Bullet::Bullet(sf::Vector2f player_position, float angle)
{
	this->bullet.setSize(sf::Vector2f(15.f, 5.f));
	this->bullet.setOrigin(sf::Vector2f(7.5f, 2.5f));
	this->bullet.setFillColor(sf::Color::Yellow);

	this->bullet.setPosition(player_position);
	this->bullet.setRotation(90 + angle);
	this->angle = angle;
	this->speed = 1.3f;
}

sf::FloatRect Bullet::getGlobalBounds()
{
	return this->bullet.getGlobalBounds();
}

sf::Vector2f Bullet::get_position()
{
	return bullet.getPosition();
}

void Bullet::spawnBullet(sf::Vector2f player_position)
{
	this->bullet.setPosition(player_position);
}

void Bullet::updateBullet()
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180), speed * -cosf(angle * 3.141592 / 180));
	this->bullet.move(this->velocity);
}

void Bullet::renderBullet(sf::RenderTarget& target)
{
	target.draw(this->bullet);
}