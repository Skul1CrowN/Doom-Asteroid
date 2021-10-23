#include "Enemy.h"

sf::Sprite& Enemy::getEnemy()
{
	return this->enemy_sprite;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->enemy_sprite.getGlobalBounds();
}

Enemy::Enemy(sf::Texture* enemy_texture,int maxHp,int level,float speed,int score,sf::Vector2f enemy_position,float scale)
{
	//Load Texture
	this->enemy_texture = enemy_texture;
	this->enemy_sprite.setTexture(*this->enemy_texture);

	//Init stats
	this->maxHp = maxHp;
	this->hp = this->maxHp;
	this->level = level;

	this->speed = speed;
	this->score = score;

	//Position
	this->enemy_sprite.setScale(sf::Vector2f(scale, scale));
	this->enemy_sprite.setPosition(enemy_position);
	this->enemy_sprite.setOrigin(sf::Vector2f(
		this->enemy_sprite.getLocalBounds().width / 2,
		this->enemy_sprite.getLocalBounds().height / 2)
	);
	this->enemy_sprite.setPosition(enemy_position);
}

void Enemy::receiveDamage(int damage)
{
	this->hp -= damage;
}

void Enemy::updateEnemy()
{
	//Movement
	this->enemy_sprite.rotate(0.5f * speed);
	this->enemy_sprite.move(sf::Vector2f(-speed, 0));
}

void Enemy::renderEnemies(sf::RenderTarget& target)
{
	target.draw(this->enemy_sprite);
}
