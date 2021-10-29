#include "Rocket.h"

Rocket::Rocket(sf::Texture* texture, sf::Vector2f player_position, float angle)
{
	this->rocket_texture = texture;
	this->rocket_sprite.setSize(sf::Vector2f(80.f, 30.f));
	this->rocket_sprite.setOrigin(sf::Vector2f(40.f, 15.f));
	this->rocket_sprite.setTexture(this->rocket_texture);

	this->rocket_sprite.setPosition(player_position);
	this->rocket_sprite.setRotation(-90 + angle);
	this->angle = angle;
	this->speed = 1500.f;
}

sf::FloatRect Rocket::getGlobalBounds()
{
	return this->rocket_sprite.getGlobalBounds();
}

sf::Vector2f Rocket::get_position()
{
	return this->rocket_sprite.getPosition();
}

void Rocket::spawnRocket(sf::Vector2f player_position)
{
	this->rocket_sprite.setPosition(player_position);
}

void Rocket::updateRocket(float deltaTime)
{
	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->rocket_sprite.move(this->velocity);
}

void Rocket::renderRocket(sf::RenderTarget& target)
{
	target.draw(this->rocket_sprite);
}
