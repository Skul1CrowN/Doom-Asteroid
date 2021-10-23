#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	//Backgroud
	this->window = window;

	//Player
	this->player_texture.loadFromFile("Images/Spaceship.png");
	this->player.push_back(Player(&player_texture));

	//Enemy
	this->enemy_texture[0].loadFromFile("Images/Red Asteroid.png");
	this->enemy_texture[1].loadFromFile("Images/Blue Asteroid.png");
	this->enemy_texture[2].loadFromFile("Images/Green Asteroid.png");
	this->enemy_texture[3].loadFromFile("Images/Yellow Asteroid.png");
	this->enemy_texture[4].loadFromFile("Images/Pink Asteroid.png");

	this->maxEnemies = 30;
	this->maxDelaySpawn = 0.1f;
	this->delaySpawn = this->maxDelaySpawn;
	this->enemy_speed = 0.5f;
}

void Game::UpdateMousePos(sf::RenderWindow* window)
{
	this->mouse_position = sf::Vector2f(sf::Mouse::getPosition(*window));
}

void Game::SpawnEnemy()
{
	int spawn_normal = rand() % 5;
	int level_stat[] = { 1,2,3,4,5 };
	int hp_stat[] = { 1,2,3,4,5 };
	int score_stat[] = { 10,20,30,40,50 };
	int rand_scale = rand() % 65 + 40;
	float scale = (float)rand_scale / 100;
	int rand_posY = rand() % (1080 - (int)(120*scale)) + (int)(60*scale);
	sf::Vector2f enemy_pos = sf::Vector2f(1920, rand_posY);
	this->enemies.push_back(Enemy(&enemy_texture[spawn_normal], hp_stat[spawn_normal], level_stat[spawn_normal], enemy_speed, score_stat[spawn_normal],enemy_pos,scale));
}

void Game::Update(float deltaTime)
{
	this->UpdateMousePos(window);

	//Spawn Enemy
	if (this->delaySpawn >= this->maxDelaySpawn && enemies.size() < this->maxEnemies)
	{
		this->SpawnEnemy();
		this->delaySpawn = 0;
	}

	//Player Update
	for (int i = 0; i < player.size(); i++)
	{
		this->player[i].updatePlayer(window, mouse_position, deltaTime);
		//Bullet Update
		for (int j = 0; j < player[i].get_bullets().size(); j++)
		{
			this->player[i].get_bullets()[j].updateBullet();
			//Bullet vs Enemy
			for (int k = 0; k < enemies.size(); k++)
			{
				if (this->player[i].get_bullets()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
				{
					this->player[i].get_bullets().erase(this->player[i].get_bullets().begin() + j);
					this->enemies.erase(this->enemies.begin() + k);
					return;
				}
			}
			//Window Check
			if (this->player[i].get_bullets()[j].get_position().x > this->window->getSize().x || this->player[i].get_bullets()[j].get_position().x < 0 || this->player[i].get_bullets()[j].get_position().y > this->window->getSize().y || this->player[i].get_bullets()[j].get_position().y < 0)
			{
				this->player[i].get_bullets().erase(this->player[i].get_bullets().begin() + j);
				return;
			}
		}
	}

	//Update Enemy
	for (int i = 0; i < enemies.size(); i++)
	{
		this->enemies[i].updateEnemy();
		if (enemies[i].getEnemy().getPosition().x < 0)
		{
			this->enemies.erase(this->enemies.begin() + i);
			break;
		}
	}

	//Update Time
	if (this->delaySpawn < this->maxDelaySpawn)
		this->delaySpawn += deltaTime;
}

void Game::Render()
{
	this->window->clear();

	for (int i = 0; i < this->player.size(); i++)
		this->player[i].renderPlayer(*this->window);

	for (int i = 0; i < this->enemies.size(); i++)
		this->enemies[i].renderEnemies(*this->window);

	this->window->display();
}
