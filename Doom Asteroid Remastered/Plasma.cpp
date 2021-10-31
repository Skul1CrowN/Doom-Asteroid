#include "Plasma.h"

Plasma::Plasma(sf::Texture* texture,sf::Vector2f player_position,float angle)
{
	this->plasma_texture = texture;

	this->plasma.setRadius(5.f);
	this->plasma.setOrigin(sf::Vector2f(2.5f, 2.5f));
	this->plasma.setTexture(this->plasma_texture);

	this->plasma.setPosition(player_position);
	this->speed = 1800.f;
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

void Plasma::updatePlasma(float deltaTime)
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->plasma.move(this->velocity);
}

void Plasma::renderPlasma(sf::RenderTarget& target)
{
	target.draw(this->plasma);
}
