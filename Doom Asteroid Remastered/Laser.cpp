#include "Laser.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include<cmath>
Laser::Laser(sf::Vector2f player_position, float angle)
{
	this->laser.setSize(sf::Vector2f(80.f, 5.f));
	this->laser.setOrigin(sf::Vector2f(40.f, 2.5f));
	this->laser.setFillColor(sf::Color::Green);

	this->laser.setPosition(player_position);
	this->laser.setRotation(90 + angle);
	this->angle = angle;
	this->speed = 6.5f;
}

sf::FloatRect Laser::getGlobalBounds()
{
	return this->laser.getGlobalBounds();
}

sf::Vector2f Laser::get_position()
{
	return this->laser.getPosition();
}

void Laser::spawnLaser(sf::Vector2f player_position)
{
	this->laser.setPosition(player_position);
}

void Laser::updateLaser()
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180), speed * -cosf(angle * 3.141592 / 180));
	this->laser.move(this->velocity);
}

void Laser::renderLaser(sf::RenderTarget& target)
{
	target.draw(this->laser);
}