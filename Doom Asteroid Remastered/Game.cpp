#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	//Backgroud
	this->window = window;

	//Font
	this->font.loadFromFile("Fonts/neuropol.ttf");

	//Player
	this->player_texture.loadFromFile("Images/Spaceship.png");
	this->rocket_texture.loadFromFile("Images/Rocket.png");
	this->mine_texture.loadFromFile("Images/Mine.png");
	this->player.push_back(Player(&player_texture,&rocket_texture,&mine_texture));
	this->world_alive = 1;

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
	
	//Items
	this->item_texture[0].loadFromFile("Images/Item_HP.png");
	this->item_texture[1].loadFromFile("Images/Item_Shield.png");
	this->item_texture[2].loadFromFile("Images/Laser_Item.png");
	this->item_texture[3].loadFromFile("Images/Plasma_Item.png");
	this->item_texture[4].loadFromFile("Images/Rocket_Item.png");
	this->item_texture[5].loadFromFile("Images/TriCannon_Item.png");
	this->item_texture[6].loadFromFile("Images/Mine_Item.png");

	//Weapon Icon
	this->weapon_texture[0].loadFromFile("Images/Normal_Item.png");
	this->weapon_texture[1].loadFromFile("Images/Laser_Item.png");
	this->weapon_texture[2].loadFromFile("Images/Plasma_Item.png");
	this->weapon_texture[3].loadFromFile("Images/Rocket_Item.png");
	this->weapon_texture[4].loadFromFile("Images/TriCannon_Item.png");
	this->weapon_texture[5].loadFromFile("Images/Mine_Item.png");

	this->weapon_disabled[0].loadFromFile("Images/Laser_Item_Disabled.png");
	this->weapon_disabled[1].loadFromFile("Images/Plasma_Item_Disabled.png");
	this->weapon_disabled[2].loadFromFile("Images/Rocket_Item_Disabled.png");
	this->weapon_disabled[3].loadFromFile("Images/TriCannon_Item_Disabled.png");
	this->weapon_disabled[4].loadFromFile("Images/Mine_Item_Disabled.png");

	//Score
	this->score = 0;
	
	//UI
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
	this->hp_icon.setScale(sf::Vector2f(0.08f, 0.08f));
	this->hp_icon.setPosition(50.f, 47.f);

	this->hpBar.setPosition(50.f, 70.f);

	this->hpBarMax.setPosition(50.f, 70.f);
	this->hpBarMax.setSize(sf::Vector2f(300.f, 10.f));

	//Shield UI
	this->shield_indicator.setFont(this->font);
	this->shield_indicator.setPosition(150.f, 45.f);
	this->shield_indicator.setCharacterSize(16);

	this->shield_texture.loadFromFile("Images/Shield.png");
	this->shield_icon.setTexture(this->shield_texture);
	this->shield_icon.setScale(sf::Vector2f(0.08f, 0.08f));
	this->shield_icon.setPosition(130.f, 47.f);

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

	//Repaired UI
	this->hull_text.setFont(this->font);
	this->hull_text.setString("Hull Breach!");
	this->hull_text.setPosition(50.f, 45.f);
	this->hull_text.setCharacterSize(18);
	this->hull_text.setFillColor(sf::Color(255, 11, 11));

	this->repair_progress.setFont(this->font);
	this->repair_progress.setPosition(280.f, 45.f);
	this->repair_progress.setCharacterSize(18);

	this->hull_instruction.setFont(this->font);
	this->hull_instruction.setString("Hold Spacebar to repair your ship!");
	this->hull_instruction.setPosition(this->window->getSize().x / 2 - 300.f, 50.f);
	this->hull_instruction.setCharacterSize(24);
	this->hull_instruction.setFillColor(sf::Color(255, 255, 255));
	
	this->repairedBar.setFillColor(sf::Color(255, 255, 255));
	this->repairedBar.setSize(sf::Vector2f(300.f, 5.f));
	this->repairedBar.setPosition(50.f, 65.f);

	this->repairedBarMax.setFillColor(sf::Color(101, 101, 101));
	this->repairedBarMax.setSize(sf::Vector2f(300.f, 5.f));
	this->repairedBarMax.setPosition(50.f, 65.f);

	//Score UI
	this->score_text.setFont(this->font);
	this->score_text.setPosition(1750.f - this->score_text.getLocalBounds().width, 50.f);
	this->score_text.setCharacterSize(20);
	this->score_text.setFillColor(sf::Color(255, 255, 255));

	//Weapon UI
	this->weapon_name.setFont(this->font);
	this->weapon_name.setPosition(110.f, 100.f);
	this->weapon_name.setCharacterSize(18);

	this->ammo_amount.setFont(this->font);
	this->ammo_amount.setPosition(110.f, 120.f);
	this->ammo_amount.setCharacterSize(18);

	this->weapon_icon.setScale(sf::Vector2f(0.7f, 0.7f));
	this->weapon_icon.setPosition(50.f, 100.f);

	this->weapon_selection[0].setTexture(this->weapon_texture[0]);
	this->weapon_selection[1].setTexture(this->weapon_disabled[0]);
	this->weapon_selection[2].setTexture(this->weapon_disabled[1]);
	this->weapon_selection[3].setTexture(this->weapon_disabled[2]);
	this->weapon_selection[4].setTexture(this->weapon_disabled[3]);
	this->weapon_selection[5].setTexture(this->weapon_disabled[4]);
}

void Game::UpdateUI(int i)
{
	//HP Bar
	this->hp_indicator.setString(std::to_string(this->player[i].getHp()));
	if (((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 >= 75)
	{
		this->hp_indicator.setFillColor(sf::Color(51, 255, 51));

		this->hp_icon.setColor(sf::Color(51, 255, 51));
		this->hpBar.setSize( sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()) ,10.f));
		this->hpBar.setFillColor(sf::Color(51, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(11, 71, 11));
	}
	else if (((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 >= 30 && ((float)this->player[i].getHp() / this->player[i].getHpMax()) * 100 < 75)
	{
		this->hp_indicator.setFillColor(sf::Color(255, 255, 51));

		this->hp_icon.setColor(sf::Color(255, 255, 51));
		this->hpBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()), 10.f));
		this->hpBar.setFillColor(sf::Color(255, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 71, 11));
	}
	else
	{
		this->hp_indicator.setFillColor(sf::Color(255, 51, 51));

		this->hp_icon.setColor(sf::Color(255, 51, 51));
		this->hpBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getHp() / this->player[i].getHpMax()), 10.f));
		this->hpBar.setFillColor(sf::Color(255, 51, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 11, 11));
	}

	//Shield Bar
	this->shield_indicator.setString(std::to_string(this->player[i].getShield()));
	if (this->player[i].getShield() == 0)
	{
		this->shield_icon.setColor(sf::Color(0, 76, 153));
		this->shield_indicator.setFillColor(sf::Color(0, 76, 153));
	}
	else
	{
		this->shield_icon.setColor(sf::Color(102, 178, 255));
		this->shield_indicator.setFillColor(sf::Color(102, 178, 255));
	}
	this->shieldBar.setSize(sf::Vector2f(300.f * ((float)this->player[i].getShield() / this->player[i].getShieldMax()), 5.f));

	//Integrity Bar
	this->integrity_indicator.setString(std::to_string(this->player[i].getIntegrity()));
	this->integrityBar.setSize(sf::Vector2f(600.f * ((float)this->player[i].getIntegrity() / this->player[i].getMaxIntegrity()), 5.f));

	//Repaired Bar
	int progress = (this->player[i].getRepaired() / this->player[i].getRepairRequired()) * 100;
	this->repair_progress.setString(std::to_string(progress) + "%");
	this->repairedBar.setSize(sf::Vector2f(300.f * (this->player[i].getRepaired() / this->player[i].getRepairRequired()), 5.f));

	//Score
	this->score_text.setString(std::to_string(this->score));

	//Weapon UI
	switch (this->player[i].getWeaponType())
	{
	case 1:
		this->weapon_icon.setTexture(this->weapon_texture[0]);
		this->weapon_name.setString("Normal Gun");
		this->ammo_amount.setString("");
		break;
	case 2:
		this->weapon_icon.setTexture(this->weapon_texture[1]);
		this->weapon_name.setString("Laser Shot");
		this->ammo_amount.setString(std::to_string(this->player[i].getLaserAmmo()));
		if (this->player[i].getLaserAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
		break;
	case 3:
		this->weapon_icon.setTexture(this->weapon_texture[2]);
		this->weapon_name.setString("Plasma Gun");
		this->ammo_amount.setString(std::to_string(this->player[i].getPlasmaAmmo()));
		if (this->player[i].getPlasmaAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
		break;
	case 4:
		this->weapon_icon.setTexture(this->weapon_texture[3]);
		this->weapon_name.setString("Rocket Launcher");
		this->ammo_amount.setString(std::to_string(this->player[i].getRocketAmmo()));
		if (this->player[i].getRocketAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
		break;
	case 5:
		this->weapon_icon.setTexture(this->weapon_texture[4]);
		this->weapon_name.setString("Tri Cannon");
		this->ammo_amount.setString(std::to_string(this->player[i].getTriAmmo()));
		if (this->player[i].getTriAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
		break;
	case 6:
		this->weapon_icon.setTexture(this->weapon_texture[5]);
		this->weapon_name.setString("Mine Launcher");
		this->ammo_amount.setString(std::to_string(this->player[i].getMineAmmo()));
		if (this->player[i].getMineAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
		break;
	default:
		break;
	}	

}

void Game::UpdateMousePos(sf::RenderWindow* window)
{
	this->mouse_position = sf::Vector2f(sf::Mouse::getPosition(*window));
}

void Game::SpawnEnemy()
{
	int spawn_normal = rand() % 6;
	int spawn_type = rand() % 4;
	int level_stat[] = { 1,2,3,4,5,10 };
	int hp_stat[] = { 1,2,3,4,5,10 };
	int score_stat[] = { 10,20,30,40,50,200 };
	int rand_scale = rand() % 65 + 40;
	float scale = (float)rand_scale / 100;
	int rand_posY = rand() % (window->getSize().y - (int)(120 * scale)) + (int)(60 * scale);
	sf::Vector2f enemy_pos = sf::Vector2f(window->getSize().x, rand_posY);
	this->enemies.push_back(Enemy(&enemy_texture[spawn_normal], hp_stat[spawn_normal], level_stat[spawn_normal], enemy_speed, score_stat[spawn_normal],enemy_pos,scale,spawn_type));
}

void Game::Update(float deltaTime)
{
	this->UpdateMousePos(window);
		
	if (world_alive)
	{
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
						//Enemy Take Damage
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getNormalDamage());
						//Enemy Killed
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
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
			//Laser Update
			for (int j = 0; j < player[i].get_lasers().size(); j++)
			{
				this->player[i].get_lasers()[j].updateLaser();
				//Laser vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_lasers()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						this->player[i].get_lasers().erase(this->player[i].get_lasers().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getLaserDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_lasers()[j].get_position().x > this->window->getSize().x || this->player[i].get_lasers()[j].get_position().x < 0 || this->player[i].get_lasers()[j].get_position().y > this->window->getSize().y || this->player[i].get_lasers()[j].get_position().y < 0)
				{
					this->player[i].get_lasers().erase(this->player[i].get_lasers().begin() + j);
					return;
				}
			}
			//Plasma Update
			for (int j = 0; j < player[i].get_plasmas().size(); j++)
			{
				this->player[i].get_plasmas()[j].updatePlasma();
				//Plasma vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_plasmas()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						this->player[i].get_plasmas().erase(this->player[i].get_plasmas().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getPlasmaDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_plasmas()[j].get_position().x > this->window->getSize().x || this->player[i].get_plasmas()[j].get_position().x < 0 || this->player[i].get_plasmas()[j].get_position().y > this->window->getSize().y || this->player[i].get_plasmas()[j].get_position().y < 0)
				{
					this->player[i].get_plasmas().erase(this->player[i].get_plasmas().begin() + j);
					return;
				}
			}
			//Rocket Update
			for (int j = 0; j < player[i].get_rockets().size(); j++)
			{
				this->player[i].get_rockets()[j].updateRocket();
				//Rocket vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_rockets()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						hitted_index = k;
						this->player[i].explosionFlak(this->enemies[k].getPosition());
						this->player[i].get_rockets().erase(this->player[i].get_rockets().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getRocketDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							if (k > hitted_index)
								hitted_index--;
							if (k == hitted_index)
								hitted_index = -1;
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_rockets()[j].get_position().x > this->window->getSize().x || this->player[i].get_rockets()[j].get_position().x < 0 || this->player[i].get_rockets()[j].get_position().y > this->window->getSize().y || this->player[i].get_rockets()[j].get_position().y < 0)
				{
					this->player[i].get_rockets().erase(this->player[i].get_rockets().begin() + j);
					return;
				}
			}
			//Flak Update
			for (int j = 0; j < player[i].get_flaks().size(); j++)
			{
				this->player[i].get_flaks()[j].updateBullet();
				//Flak vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_flaks()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()) && k != hitted_index)
					{
						this->player[i].get_flaks().erase(this->player[i].get_flaks().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getFlakDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_flaks()[j].get_position().x > this->window->getSize().x || this->player[i].get_flaks()[j].get_position().x < 0 || this->player[i].get_flaks()[j].get_position().y > this->window->getSize().y || this->player[i].get_flaks()[j].get_position().y < 0)
				{
					this->player[i].get_flaks().erase(this->player[i].get_flaks().begin() + j);
					return;
				}
			}
			//Tri Cannon
			for (int j = 0; j < player[i].get_tricannons().size(); j++)
			{
				this->player[i].get_tricannons()[j].updateTriCannon();
				//Tri Cannon vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_tricannons()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						this->player[i].get_tricannons().erase(this->player[i].get_tricannons().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getFlakDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_tricannons()[j].get_position().x > this->window->getSize().x || this->player[i].get_tricannons()[j].get_position().x < 0 || this->player[i].get_tricannons()[j].get_position().y > this->window->getSize().y || this->player[i].get_tricannons()[j].get_position().y < 0)
				{
					this->player[i].get_tricannons().erase(this->player[i].get_tricannons().begin() + j);
					return;
				}
			}
			//Mine Update
			for(int j = 0; j < player[i].get_mines().size(); j++)
			{
				this->player[i].get_mines()[j].updateMine(deltaTime);
				//Mine vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_mines()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						//Mine Health Update
						if (this->player[i].get_mines()[j].getHealth() > 0)
							this->player[i].get_mines()[j].receivedDamage(1);
						if (this->player[i].get_mines()[j].getHealth() <= 0)
							this->player[i].get_mines().erase(this->player[i].get_mines().begin() + j);

						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getMineDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore();
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type = rand() % 7;
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type = rand() % 7;
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				if (this->player[i].get_mines()[j].get_position().x > this->window->getSize().x || this->player[i].get_mines()[j].get_position().x < 0 || this->player[i].get_mines()[j].get_position().y > this->window->getSize().y || this->player[i].get_mines()[j].get_position().y < 0)
				{
					this->player[i].get_mines().erase(this->player[i].get_mines().begin() + j);
					return;
				}
			}
			//World Integrity Check
			if (this->player[i].getIntegrity() <= 0)
				this->world_alive = 0;
		}

		//Update Enemy
		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < player.size(); j++)
			{
				this->enemies[i].updateEnemy(window, this->player[j].getPosition(), this->player[j].getHullBreach(), deltaTime);
				// Enemy vs Player
				if (this->enemies[i].getGlobalBounds().intersects(this->player[j].getGlobalBounds()) && !this->player[j].getHullBreach())
				{
					this->player[j].receivedDamage(this->enemies[i].getLevel());
					this->enemies.erase(this->enemies.begin() + i);
					return;
				}
				//Window Check(World Crushed)
				if (enemies[i].getEnemy().getPosition().x < 0)
				{
					this->player[j].receivedWorldDamage(this->enemies[i].getLevel());
					this->enemies.erase(this->enemies.begin() + i);
					return;
				}
			}
		}

		//Update Items
		for (int i = 0; i < items.size(); i++)
		{
			//Item vs Player
			for (int j = 0; j < player.size(); j++)
			{
				if (this->player[j].getGlobalBounds().intersects(this->items[i].getGlobalBounds()))
				{
					switch (this->items[i].getItem())
					{
					case 0: // Repair
						this->player[j].repairHP(15);
						break;
					case 1: // Shield
						this->player[j].receivedShield(10);
						break;
					case 2: // Laser Ammo
						this->player[j].gainLaserAmmo(10);
						break;
					case 3: // Plasma Ammo
						this->player[j].gainPlasmaAmmo(30);
						break;
					case 4: //Rocket Ammo
						this->player[j].gainRocketAmmo(3);
						break;
					case 5: //Tri Ammo
						this->player[j].gainTriAmmo(20);
						break;
					case 6: //Mine Ammo
						this->player[j].gainMineAmmo(5);
						break;
					default:
						break;
					}
					this->items.erase(this->items.begin() + i);
					return;
				}
			}
		}

		//Update Time
		if (this->delaySpawn < this->maxDelaySpawn)
			this->delaySpawn += deltaTime;

	}
}

void Game::Render()
{
	this->window->clear();
	
	//Player Ship
	for (int i = 0; i < this->player.size(); i++)
		this->player[i].renderPlayer(*this->window);

	//Item
	for (int i = 0; i < this->items.size(); i++)
		this->items[i].renderItem(*this->window);

	//Enemy Asteroid
	for (int i = 0; i < this->enemies.size(); i++)
		this->enemies[i].renderEnemies(*this->window);
	
	//Player UI
	for (int i = 0; i < this->player.size(); i++)
	{
		if (!this->player[i].getHullBreach())
		{
			//HP Bar
			this->window->draw(hp_icon);
			this->window->draw(hp_indicator);
			this->window->draw(hpBarMax);
			this->window->draw(hpBar);

			//Shield Bar
			this->window->draw(shield_icon);
			this->window->draw(shield_indicator);
			this->window->draw(shieldBarMax);
			this->window->draw(shieldBar);
		}
		else
		{
			//Repaired Bar
			this->window->draw(hull_text);
			this->window->draw(repair_progress);
			this->window->draw(hull_instruction);
			this->window->draw(repairedBarMax);
			this->window->draw(repairedBar);
		}
	}

	//Integrity Bar
	this->window->draw(integrity_indicator);
	this->window->draw(integrityBarMax);
	this->window->draw(integrityBar);

	//Score
	this->window->draw(score_text);

	//Weapon UI
	this->window->draw(weapon_name);
	this->window->draw(ammo_amount);
	this->window->draw(weapon_icon);

	//Game Over Scene
	if (!this->world_alive)
	{
		this->window->clear();
	}
	
	this->window->display();
}
