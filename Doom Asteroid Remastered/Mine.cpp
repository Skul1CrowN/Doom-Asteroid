#include "Mine.h"

Mine::Mine(sf::Texture* texture, sf::Vector2f player_position, float angle)
{
	this->mine_texture = texture;
	this->mine_sprite.setSize(sf::Vector2f(40.f, 40.f));
	this->mine_sprite.setOrigin(sf::Vector2f(20.f, 20.f));
	this->mine_sprite.setTexture(this->mine_texture);

	this->mine_sprite.setPosition(player_position);
	this->mine_sprite.setRotation(angle);
	this->angle = angle;
	this->speed = 400.f;
	this->acceleration = 200.f;
	this->health = 10;
}

int& Mine::getHealth()
{
	return this->health;
}

sf::FloatRect Mine::getGlobalBounds()
{
	return this->mine_sprite.getGlobalBounds();
}

sf::Vector2f Mine::get_position()
{
	return this->mine_sprite.getPosition();
}

void Mine::spawnMine(sf::Vector2f player_position)
{
	this->mine_sprite.setPosition(player_position);
}

void Mine::receivedDamage(int damage)
{
	this->health -= damage;
}

void Mine::updateMine(float deltaTime)
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->speed -= deltaTime * this->acceleration;
	if (this->speed < 0)
		this->speed = 0;
	this->mine_sprite.move(this->velocity);
}

void Mine::renderMine(sf::RenderTarget& target)
{
	target.draw(this->mine_sprite);
}
