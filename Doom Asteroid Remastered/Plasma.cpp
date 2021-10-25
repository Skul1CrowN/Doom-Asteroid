#include "Plasma.h"

Plasma::Plasma(sf::Vector2f player_position,float angle)
{
	this->plasma.setRadius(5.f);
	this->plasma.setOrigin(sf::Vector2f(2.5f, 2.5f));
	this->plasma.setFillColor(sf::Color(0, 200, 255));

	this->plasma.setPosition(player_position);
	this->speed = 2.f;
	this->angle = angle;
}

sf::FloatRect Plasma::getGlobalBounds()
{
	return this->plasma.getGlobalBounds();
}

sf::Vector2f Plasma::get_position()
{
	return this->plasma.getPosition();
}

void Plasma::spawnPlasma(sf::Vector2f player_position)
{
	this->plasma.setPosition(player_position);
}

void Plasma::updatePlasma()
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180), speed * -cosf(angle * 3.141592 / 180));
	this->plasma.move(this->velocity);
}

void Plasma::renderPlasma(sf::RenderTarget& target)
{
	target.draw(this->plasma);
}
