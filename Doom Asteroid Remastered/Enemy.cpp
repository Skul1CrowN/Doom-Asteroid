#include "Enemy.h"

int& Enemy::getHp()
{
	return this->hp;
}

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

	//For Fun
	this->phase = 0;
}

void Enemy::receiveDamage(int damage)
{
	this->hp -= damage;
}

void Enemy::updateEnemy(float deltaTime)
{
	//Movement
	this->enemy_sprite.rotate(0.5f * speed * deltaTime);
	this->enemy_sprite.move(sf::Vector2f(-speed * deltaTime, 0));

	//For Fun
	if (this->level == 10)
	{
		//Phase Change
		this->phase += (int)(deltaTime * 1500.f);
		this->phase %= 540;

		//Red
		if (phase >= 0 && phase < 180)
			this->red = 128 + (int)(127.f * 0.5*(cos(phase * 3.141592 / 180) + 1));
		else if(phase >= 180 && phase < 360)
			this->red = 0;
		else
			this->red = 128 + (int)(127.f * 0.5*(-cos(phase*3.141592/180) + 1));
		//Green
		if (phase >= 0 && phase < 360)
			this->green = 128 + (int)(127.f * 0.5*(-cos(phase * 3.141592 / 180) + 1));
		else
			this->green = 0;
		//Blue
		if (phase >= 0 && phase < 180)
			this->blue = 0;
		else
			this->blue = 128 + (int)(127.f * 0.5*(cos(phase * 3.141592 / 180) + 1));
		
		this->enemy_sprite.setColor(sf::Color(red,green,blue));
	}
}

void Enemy::renderEnemies(sf::RenderTarget& target)
{
	target.draw(this->enemy_sprite);
}
