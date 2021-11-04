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
	this->maxHp = 10;
	this->hp = this->maxHp;

	this->hpBar.setSize(sf::Vector2f(40.f, 2.5f));
	this->hpBar.setFillColor(sf::Color(51, 255, 255));
	this->hpBar.setOrigin(sf::Vector2f(
		this->hpBar.getLocalBounds().width / 2,
		this->hpBar.getLocalBounds().height / 2)
	);

	this->hpBarMax.setSize(sf::Vector2f(40.f, 2.5f));
	this->hpBarMax.setFillColor(sf::Color(11, 71, 71));
	this->hpBarMax.setOrigin(sf::Vector2f(
		this->hpBarMax.getLocalBounds().width / 2,
		this->hpBarMax.getLocalBounds().height / 2)
	);
}

int& Mine::getHealth()
{
	return this->hp;
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
	this->hp -= damage;
}

void Mine::updateMine(float deltaTime)
{
	this->mine_position = this->mine_sprite.getPosition();

	this->velocity = sf::Vector2f(speed * sinf(angle * 3.141592 / 180) * deltaTime, speed * -cosf(angle * 3.141592 / 180) * deltaTime);
	this->speed -= deltaTime * this->acceleration;
	if (this->speed < 0)
		this->speed = 0;
	this->mine_sprite.move(this->velocity);

	//HpBar
	this->hpBar.setPosition(sf::Vector2f(this->mine_position) + sf::Vector2f(0.f, 20.f));
	this->hpBar.setSize(sf::Vector2f(40.f * (float)this->hp / this->maxHp, 2.5f));

	this->hpBarMax.setPosition(sf::Vector2f(this->mine_position) + sf::Vector2f(0.f, 20.f));
}

void Mine::renderMine(sf::RenderTarget& target)
{
	target.draw(this->mine_sprite);
	target.draw(this->hpBarMax);
	target.draw(this->hpBar);
}
