#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	//Backgroud
	this->window = window;

	//Font
	this->font.loadFromFile("Fonts/neuropol.ttf");

	//Player
	this->player_texture.loadFromFile("Images/Spaceship.png");
	this->player.push_back(Player(&player_texture));

	//Enemy
	this->enemy_texture[0].loadFromFile("Images/Red Asteroid.png");
	this->enemy_texture[1].loadFromFile("Images/Blue Asteroid.png");
	this->enemy_texture[2].loadFromFile("Images/Green Asteroid.png");
	this->enemy_texture[3].loadFromFile("Images/Yellow Asteroid.png");
	this->enemy_texture[4].loadFromFile("Images/Pink Asteroid.png");
	this->enemy_texture[5].loadFromFile("Images/Asteroid.png");

	this->maxEnemies = 10;
	this->maxDelaySpawn = 1.f;
	this->delaySpawn = this->maxDelaySpawn;
	this->enemy_speed = 300.f;

	this->InitUI();
}

void Game::InitUI()
{
	//HP UI
	this->hp_indicator.setFont(this->font);
	this->hp_indicator.setPosition(70.f, 45.f);
	this->hp_indicator.setCharacterSize(16);

	this->hp_texture.loadFromFile("Images/HP.png");
	this->hp_icon.setTexture(this->hp_texture);
	this->hp_icon.setScale(sf::Vector2f(0.10f, 0.10f));
	this->hp_icon.setPosition(50.f, 50.f);

	this->hpBar.setPosition(50.f, 70.f);

	this->hpBarMax.setPosition(50.f, 70.f);
	this->hpBarMax.setSize(sf::Vector2f(300.f, 10.f));

	//Shield UI
	this->shield_indicator.setFont(this->font);
	this->shield_indicator.setPosition(140.f, 45.f);
	this->shield_indicator.setCharacterSize(16);

	this->shield_texture.loadFromFile("Images/Shield.png");
	this->shield_icon.setTexture(this->hp_texture);
	this->shield_icon.setScale(sf::Vector2f(0.10f, 0.10f));
	this->shield_icon.setPosition(50.f, 50.f);

	this->shieldBar.setFillColor(sf::Color(102, 178, 255));
	this->shieldBar.setPosition(50.f, 65.f);

	this->shieldBarMax.setFillColor(sf::Color(0, 76, 153));
	this->shieldBarMax.setPosition(50.f, 65.f);
	this->shieldBarMax.setSize(sf::Vector2f(300.f, 5.f));

	//Integrity UI
	this->integrity_indicator.setFont(this->font);
	this->integrity_indicator.setPosition(50.f, this->window->getSize().y - 50.f);
	this->integrity_indicator.setCharacterSize(16);

	this->world_texture.loadFromFile("Images/World.png");
	this->world_icon.setTexture(this->hp_texture);
	this->world_icon.setScale(sf::Vector2f(0.10f, 0.10f));
	this->world_icon.setPosition(50.f, 50.f);

	this->integrityBar.setFillColor(sf::Color(51, 255, 255));
	this->integrityBar.setPosition(50.f, this->window->getSize().y - 30.f);

	this->integrityBarMax.setFillColor(sf::Color(11, 71, 71));
	this->integrityBarMax.setPosition(50.f, this->window->getSize().y - 30.f);
	this->integrityBarMax.setSize(sf::Vector2f(600.f, 5.f));
}

void Game::UpdateUI(int i)
{
	//HP Bar
	this->hp_indicator.setString(std::to_string(this->player[i].getHp()));
	if (((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 >= 75)
	{
		this->hp_indicator.setFillColor(sf::Color(51, 255, 51));

		this->hpBar.setSize( sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()) ,10.f));
		this->hpBar.setFillColor(sf::Color(51, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(11, 71, 11));
	}
	else if (((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 >= 30 && ((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 < 75)
	{
		this->hp_indicator.setFillColor(sf::Color(255, 255, 51));

		this->hpBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()), 10.f));
		this->hpBar.setFillColor(sf::Color(255, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 71, 11));
	}
	else
	{
		this->hp_indicator.setFillColor(sf::Color(255, 51, 51));

		this->hpBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()), 10.f));
		this->hpBar.setFillColor(sf::Color(255, 51, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 11, 11));
	}

	//Shield Bar
	this->shield_indicator.setString(std::to_string(this->player[i].getShield()));
	if (this->player[i].getShield() == 0)
		this->shield_indicator.setFillColor(sf::Color(0, 76, 153));
	else
		this->shield_indicator.setFillColor(sf::Color(102, 178, 255));
	this->shieldBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getShield() / this->player[i].getShieldMax()), 5.f));

	//Integrity Bar
	this->integrity_indicator.setString(std::to_string(this->player[i].getIntegrity()));
	this->integrityBar.setSize(sf::Vector2f(600.f * ((float)this->player[i].getIntegrity() / this->player[i].getMaxIntegrity()), 5.f));
}

void Game::UpdateMousePos(sf::RenderWindow* window)
{
	this->mouse_position = sf::Vector2f(sf::Mouse::getPosition(*window));
}

void Game::SpawnEnemy()
{
	int spawn_normal = rand() % 6;
	int level_stat[] = { 1,2,3,4,5,10 };
	int hp_stat[] = { 1,2,3,4,5,10 };
	int score_stat[] = { 10,20,30,40,50,500 };
	int rand_scale = rand() % 65 + 40;
	float scale = (float)rand_scale / 100;
	int rand_posY = rand() % (window->getSize().y - (int)(120 * scale)) + (int)(60 * scale);
	sf::Vector2f enemy_pos = sf::Vector2f(window->getSize().x, rand_posY);
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
		//UpdateUI
		this->UpdateUI(i);
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
					if (this->enemies[k].getHp() > 0)
						this->enemies[k].receiveDamage(this->player[i].getDamage());
					if (this->enemies[k].getHp() <= 0)
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
		this->enemies[i].updateEnemy(deltaTime);
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

	//HP Bar
	this->window->draw(hp_indicator);
	this->window->draw(hpBarMax);
	this->window->draw(hpBar);

	//Shield Bar
	this->window->draw(shield_indicator);
	this->window->draw(shieldBarMax);
	this->window->draw(shieldBar);

	//Integrity Bar
	this->window->draw(integrity_indicator);
	this->window->draw(integrityBarMax);
	this->window->draw(integrityBar);

	this->window->display();
}
