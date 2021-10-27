#include "Enemy.h"

int& Enemy::getHp()
{
	return this->hp;
}

int& Enemy::getLevel()
{
	return this->level;
}

int& Enemy::getScore()
{
	return this->score;
}

sf::Sprite& Enemy::getEnemy()
{
	return this->enemy_sprite;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return this->enemy_sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition()
{
	return this->enemy_sprite.getPosition();
}

Enemy::Enemy(sf::Texture* enemy_texture, int maxHp, int level, float speed, int score, sf::Vector2f enemy_position, float scale, int type)
{
	//Load Texture
	this->enemy_texture = enemy_texture;
	this->enemy_sprite.setTexture(*this->enemy_texture);

	//Init stats
	this->maxHp = maxHp;
	this->hp = this->maxHp;
	this->level = level;

	this->move_phase = 0;
	this->speed = speed;
	this->score = score;
	this->type = type;

	//Position
	this->enemy_sprite.setScale(sf::Vector2f(scale, scale));
	this->enemy_sprite.setPosition(enemy_position);
	this->enemy_sprite.setOrigin(sf::Vector2f(
		this->enemy_sprite.getLocalBounds().width / 2,
		this->enemy_sprite.getLocalBounds().height / 2)
	);
	this->enemy_sprite.setPosition(enemy_position);

	//For Fun
	this->color_phase = 0;
}

void Enemy::receiveDamage(int damage)
{
	this->hp -= damage;
}

void Enemy::updateEnemy(sf::RenderWindow* window, sf::Vector2f player_position,bool hull_breach,float deltaTime)
{
	//Movement
	this->enemy_position = this->enemy_sprite.getPosition();
	if (this->type == 0)//Line
	{
		this->enemy_sprite.rotate(0.5f * speed * deltaTime);
		this->enemy_sprite.move(sf::Vector2f(-speed * deltaTime, 0));
	}
	else if (this->type == 1)//Sine Wave
	{
		this->move_phase += (int)(deltaTime * 700.f);
		this->move_phase %= 360;
		this->enemy_sprite.rotate(0.5f * speed * deltaTime);
		this->enemy_sprite.move(sf::Vector2f(-speed * deltaTime, speed * sin(this->move_phase * 3.141592 / 180)* deltaTime));
		if (this->enemy_sprite.getPosition().y - this->getGlobalBounds().height / 2 < 0 || this->enemy_sprite.getPosition().y + this->getGlobalBounds().height / 2 > window->getSize().y)
			this->move_phase = -this->move_phase;
	}
	else if (this->type == 2)//Inverse Sine Wave
	{
		this->move_phase += (int)(deltaTime * 800.f);
		this->move_phase %= 360;
		this->enemy_sprite.rotate(0.5f * speed * deltaTime);
		this->enemy_sprite.move(sf::Vector2f(-speed * deltaTime, -speed * sin(this->move_phase * 3.141592 / 180) * deltaTime));
		if (this->enemy_sprite.getPosition().y - this->getGlobalBounds().height/2< 0 || this->enemy_sprite.getPosition().y + this->getGlobalBounds().height / 2 > window->getSize().y)
			this->move_phase = -this->move_phase;
	}
	else if (this->type == 3)//Track Player
	{
		this->player_distance = player_position - this->enemy_position;
		this->pve_angle = atanf(this->player_distance.x / this->player_distance.y);
		this->enemy_sprite.rotate(0.5f * speed * deltaTime);
		float distance =  sqrt( pow(this->player_distance.x, 2) + pow(this->player_distance.y, 2) );
		if(!hull_breach)
			this->enemy_sprite.move(this->player_distance / distance * speed * deltaTime );
		else
			this->enemy_sprite.move(sf::Vector2f(-speed * deltaTime, 0));
	}


	//For Fun
	if (this->level == 10)
	{
		//Phase Change
		this->color_phase += (int)(deltaTime * 1500.f);
		this->color_phase %= 540;

		//Red
		if (color_phase >= 0 && color_phase < 180)
			this->red = 128 + (int)(127.f * 0.5*(cos(color_phase * 3.141592 / 180) + 1));
		else if(color_phase >= 180 && color_phase < 360)
			this->red = 0;
		else
			this->red = 128 + (int)(127.f * 0.5*(-cos(color_phase*3.141592/180) + 1));
		//Green
		if (color_phase >= 0 && color_phase < 360)
			this->green = 128 + (int)(127.f * 0.5*(-cos(color_phase * 3.141592 / 180) + 1));
		else
			this->green = 0;
		//Blue
		if (color_phase >= 0 && color_phase < 180)
			this->blue = 0;
		else
			this->blue = 128 + (int)(127.f * 0.5*(cos(color_phase * 3.141592 / 180) + 1));
		
		this->enemy_sprite.setColor(sf::Color(red,green,blue));
	}
}

void Enemy::renderEnemies(sf::RenderTarget& target)
{
	target.draw(this->enemy_sprite);
}
