#include "Nuke.h"

Nuke::Nuke(sf::Texture* texture, sf::Vector2f player_position, float angle)
{
	this->nuke_texture = texture;
	this->nuke_sprite.setSize(sf::Vector2f(80.f, 60.f));
	this->nuke_sprite.setOrigin(sf::Vector2f(40.f, 15.f));
	this->nuke_sprite.setTexture(this->nuke_texture);

	this->nuke_sprite.setPosition(player_position);
	this->nuke_sprite.setRotation(-90 + angle);
	this->angle = angle;
	this->speed = 800.f;
}

sf::FloatRect Nuke::getGlobalBounds()
{
	return this->nuke_sprite.getGlobalBounds();
}

sf::Vector2f Nuke::get_position()
{
	return this->nuke_sprite.getPosition();
}

void Nuke::spawnNuke(sf::Vector2f player_position)
{
	this->nuke_sprite.setPosition(player_position);
}

void Nuke::updateNuke(float deltaTime)
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->nuke_sprite.move(this->velocity);
}

void Nuke::renderNuke(sf::RenderTarget& target)
{
	target.draw(this->nuke_sprite);
}