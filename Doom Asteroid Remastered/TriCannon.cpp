#include "TriCannon.h"

TriCannon::TriCannon(sf::Vector2f player_position, float angle)
{
	this->tricannon.setSize(sf::Vector2f(15.f, 5.f));
	this->tricannon.setOrigin(sf::Vector2f(7.5f, 2.5f));
	this->tricannon.setFillColor(sf::Color(204,0,255));

	this->tricannon.setPosition(player_position);
	this->tricannon.setRotation(90 + angle);
	this->angle = angle;
	this->speed = 900.f;
}

sf::FloatRect TriCannon::getGlobalBounds()
{
	return this->tricannon.getGlobalBounds();
}

sf::Vector2f TriCannon::get_position()
{
	return this->tricannon.getPosition();
}

void TriCannon::spawnTriCannon(sf::Vector2f player_position)
{
	this->tricannon.setPosition(player_position);
}

void TriCannon::updateTriCannon(float deltaTime)
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->tricannon.move(this->velocity);
}

void TriCannon::renderTriCannon(sf::RenderTarget& target)
{
	target.draw(this->tricannon);
}