#include "Game.h"

Game::Game(sf::RenderWindow* window)
{
	//Backgroud
	this->window = window;
	this->background_texture.loadFromFile("Images/game_background.png");
	this->background_sprite.setTexture(this->background_texture);
	this->background_sprite.setScale(sf::Vector2f(1.2f, 1.2f));

	//Font
	this->font.loadFromFile("Fonts/neuropol.ttf");

	//Player
	this->player_texture.loadFromFile("Images/Spaceship.png");
	this->bullet_texture.loadFromFile("Images/Bullet.png");
	this->plasma_texture.loadFromFile("Images/Plasma.png");
	this->rocket_texture.loadFromFile("Images/Rocket.png");
	this->tri_texture.loadFromFile("Images/TriBullet.png");
	this->mine_texture.loadFromFile("Images/Mine.png");
	this->nuke_texture.loadFromFile("Images/Nuke.png");
	this->nukeFlak_texture.loadFromFile("Images/NukeFlak.png");
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
	this->item_texture[7].loadFromFile("Images/Nuke_Item.png");

	//Weapon Icon
	this->weapon_texture[0].loadFromFile("Images/Normal_Item.png");
	this->weapon_texture[1].loadFromFile("Images/Laser_Item.png");
	this->weapon_texture[2].loadFromFile("Images/Plasma_Item.png");
	this->weapon_texture[3].loadFromFile("Images/Rocket_Item.png");
	this->weapon_texture[4].loadFromFile("Images/TriCannon_Item.png");
	this->weapon_texture[5].loadFromFile("Images/Mine_Item.png");
	this->weapon_texture[6].loadFromFile("Images/Nuke_Item.png");

	this->weapon_disabled[0].loadFromFile("Images/Laser_Item_Disabled.png");
	this->weapon_disabled[1].loadFromFile("Images/Plasma_Item_Disabled.png");
	this->weapon_disabled[2].loadFromFile("Images/Rocket_Item_Disabled.png");
	this->weapon_disabled[3].loadFromFile("Images/TriCannon_Item_Disabled.png");
	this->weapon_disabled[4].loadFromFile("Images/Mine_Item_Disabled.png");
	this->weapon_disabled[5].loadFromFile("Images/Nuke_Item_Disabled.png");

	//Score
	this->score = 0;

	//UI
	this->InitUI();
}

bool& Game::getAlive()
{
	return this->world_alive;
}

int& Game::getScore()
{
	return this->score;
}

void Game::InitUI()
{
	//Player Name
	this->player_text.setFont(this->font);
	this->player_text.setPosition(50.f, 30.f);
	this->player_text.setCharacterSize(16);

	//HP UI
	this->hp_indicator.setFont(this->font);
	this->hp_indicator.setPosition(70.f, 50.f);
	this->hp_indicator.setCharacterSize(16);

	this->hp_texture.loadFromFile("Images/HP.png");
	this->hp_icon.setTexture(this->hp_texture);
	this->hp_icon.setScale(sf::Vector2f(0.08f, 0.08f));
	this->hp_icon.setPosition(50.f, 52.f);

	this->hpBar.setPosition(50.f, 75.f);

	this->hpBarMax.setPosition(50.f, 75.f);
	this->hpBarMax.setSize(sf::Vector2f(300.f, 10.f));

	//Shield UI
	this->shield_indicator.setFont(this->font);
	this->shield_indicator.setPosition(150.f, 50.f);
	this->shield_indicator.setCharacterSize(16);

	this->shield_texture.loadFromFile("Images/Shield.png");
	this->shield_icon.setTexture(this->shield_texture);
	this->shield_icon.setScale(sf::Vector2f(0.08f, 0.08f));
	this->shield_icon.setPosition(130.f, 52.f);

	this->shieldBar.setFillColor(sf::Color(102, 178, 255));
	this->shieldBar.setPosition(50.f, 70.f);

	this->shieldBarMax.setFillColor(sf::Color(0, 76, 153));
	this->shieldBarMax.setPosition(50.f, 70.f);
	this->shieldBarMax.setSize(sf::Vector2f(300.f, 5.f));

	//Integrity UI
	this->integrity_indicator.setFont(this->font);
	this->integrity_indicator.setPosition(75.f, this->window->getSize().y - 55.f);
	this->integrity_indicator.setCharacterSize(16);

	this->world_texture.loadFromFile("Images/World.png");
	this->world_icon.setTexture(this->world_texture);
	this->world_icon.setScale(sf::Vector2f(0.10f, 0.10f));
	this->world_icon.setColor(sf::Color(51, 255, 255));
	this->world_icon.setPosition(50.f, this->window->getSize().y - 55.f);

	this->integrityBar.setFillColor(sf::Color(51, 255, 255));
	this->integrityBar.setPosition(50.f, this->window->getSize().y - 30.f);

	this->integrityBarMax.setFillColor(sf::Color(11, 71, 71));
	this->integrityBarMax.setPosition(50.f, this->window->getSize().y - 30.f);
	this->integrityBarMax.setSize(sf::Vector2f(600.f, 5.f));

	//Repaired UI
	this->hull_text.setFont(this->font);
	this->hull_text.setString("Hull Breach!");
	this->hull_text.setPosition(50.f, 50.f);
	this->hull_text.setCharacterSize(18);
	this->hull_text.setFillColor(sf::Color(255, 11, 11));

	this->repair_progress.setFont(this->font);
	this->repair_progress.setPosition(280.f, 50.f);
	this->repair_progress.setCharacterSize(18);

	this->hull_instruction.setFont(this->font);
	this->hull_instruction.setString("Hold Spacebar to repair your ship!");
	this->hull_instruction.setPosition(this->window->getSize().x / 2 - 300.f, 50.f);
	this->hull_instruction.setCharacterSize(24);
	this->hull_instruction.setFillColor(sf::Color(255, 255, 255));
	
	this->repairedBar.setFillColor(sf::Color(255, 255, 255));
	this->repairedBar.setSize(sf::Vector2f(300.f, 5.f));
	this->repairedBar.setPosition(50.f, 70.f);

	this->repairedBarMax.setFillColor(sf::Color(101, 101, 101));
	this->repairedBarMax.setSize(sf::Vector2f(300.f, 5.f));
	this->repairedBarMax.setPosition(50.f, 70.f);

	//Score UI
	this->score_text.setFont(this->font);
	this->score_text.setPosition(1870.f - this->score_text.getLocalBounds().width, 75.f);
	this->score_text.setCharacterSize(20);
	this->score_text.setFillColor(sf::Color(255, 255, 255));
	
	//Difficulty
	this->difficulty_text.setFont(this->font);
	this->difficulty_text.setPosition(1870.f - this->difficulty_text.getLocalBounds().width, 50.f);
	this->difficulty_text.setCharacterSize(20);

	//Weapon UI
	this->weapon_name.setFont(this->font);
	this->weapon_name.setPosition(110.f, 105.f);
	this->weapon_name.setCharacterSize(18);

	this->ammo_amount.setFont(this->font);
	this->ammo_amount.setPosition(110.f, 125.f);
	this->ammo_amount.setCharacterSize(18);

	this->weapon_icon.setScale(sf::Vector2f(0.7f, 0.7f));
	this->weapon_icon.setPosition(50.f, 105.f);

	//Ammo UI
	for (int i = 0; i < 6; i++)
	{
		this->ammo_list[i].setFont(this->font);
		this->ammo_list[i].setPosition(75.f, 162.f + 20.f * i);
		this->ammo_list[i].setCharacterSize(12);
	}

	for (int i = 0; i < 6; i++)
	{
		this->weapon_ammo[i].setScale(sf::Vector2f(0.3f, 0.3f));
		this->weapon_ammo[i].setPosition(50.f, 160.f + 20.f * i);;
	}
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
	this->score_text.setOrigin(sf::Vector2f(this->score_text.getLocalBounds().width,0.f));
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
	case 7:
		this->weapon_icon.setTexture(this->weapon_texture[6]);
		this->weapon_name.setString("Nuke");
		this->ammo_amount.setString(std::to_string(this->player[i].getNukeAmmo()));
		if (this->player[i].getNukeAmmo() <= 0)
			this->ammo_amount.setFillColor(sf::Color(255, 51, 51));
		else
			this->ammo_amount.setFillColor(sf::Color(255, 255, 255));
	default:
		break;
	}
	//Ammo List UI
	this->ammo_list[0].setString(std::to_string(this->player[i].getLaserAmmo()));
	if (this->player[i].getLaserAmmo() <= 0)
	{
		this->weapon_ammo[0].setTexture(weapon_disabled[0]);
		this->ammo_list[0].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[0].setTexture(weapon_texture[1]);
		this->ammo_list[0].setFillColor(sf::Color(255, 255, 255));
	}

	this->ammo_list[1].setString(std::to_string(this->player[i].getPlasmaAmmo()));
	if (this->player[i].getPlasmaAmmo() <= 0)
	{
		this->weapon_ammo[1].setTexture(weapon_disabled[1]);
		this->ammo_list[1].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[1].setTexture(weapon_texture[2]);
		this->ammo_list[1].setFillColor(sf::Color(255, 255, 255));
	}

	this->ammo_list[2].setString(std::to_string(this->player[i].getRocketAmmo()));
	if (this->player[i].getRocketAmmo() <= 0)
	{
		this->weapon_ammo[2].setTexture(weapon_disabled[2]);
		this->ammo_list[2].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[2].setTexture(weapon_texture[3]);
		this->ammo_list[2].setFillColor(sf::Color(255, 255, 255));
	}

	this->ammo_list[3].setString(std::to_string(this->player[i].getTriAmmo()));
	if (this->player[i].getTriAmmo() <= 0)
	{
		this->weapon_ammo[3].setTexture(weapon_disabled[3]);
		this->ammo_list[3].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[3].setTexture(weapon_texture[4]);
		this->ammo_list[3].setFillColor(sf::Color(255, 255, 255));
	}

	this->ammo_list[4].setString(std::to_string(this->player[i].getMineAmmo()));
	if (this->player[i].getMineAmmo() <= 0)
	{
		this->weapon_ammo[4].setTexture(weapon_disabled[4]);
		this->ammo_list[4].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[4].setTexture(weapon_texture[5]);
		this->ammo_list[4].setFillColor(sf::Color(255, 255, 255));
	}
	this->ammo_list[5].setString(std::to_string(this->player[i].getNukeAmmo()));
	if (this->player[i].getNukeAmmo() <= 0)
	{
		this->weapon_ammo[5].setTexture(weapon_disabled[5]);
		this->ammo_list[5].setFillColor(sf::Color(101, 101, 101));
	}
	else
	{
		this->weapon_ammo[5].setTexture(weapon_texture[6]);
		this->ammo_list[5].setFillColor(sf::Color(255, 255, 255));
	}
}

void Game::setDifficulty(int difficulty)
{
	this->difficulty = difficulty;
	switch (difficulty)
	{
	case 0://Easy
		this->difficulty_text.setString("Easy");
		this->difficulty_text.setFillColor(sf::Color(51, 255, 51));
		this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width,0.f));
		break;
	case 1://Medium
		this->difficulty_text.setString("Medium");
		this->difficulty_text.setFillColor(sf::Color(255, 255, 51));
		this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width, 0.f));
		break;
	case 2://Hard
		this->difficulty_text.setString("Hard");
		this->difficulty_text.setFillColor(sf::Color(255, 128, 51));
		this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width, 0.f));
		break;
	case 3://Insane
		this->difficulty_text.setString("Insane");
		this->difficulty_text.setFillColor(sf::Color(255, 51, 51));
		this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width, 0.f));
		break;
	case 4://Apocalypse
		this->difficulty_text.setString("Apocalypse");
		this->difficulty_text.setFillColor(sf::Color(128, 51, 255));
		this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width, 0.f));
		break;
	default:
		break;
	}
}

void Game::setPlayerName(std::string player_name)
{
	this->player_name = player_name;
	this->player_text.setString(this->player_name);
}

void Game::menuCoolDown()
{
	this->menu_cooldown = true;
	this->menu_freeze = 0.0f;
}

void Game::UpdateMousePos(sf::RenderWindow* window)
{
	this->mouse_position = sf::Vector2f(sf::Mouse::getPosition(*window));
}

void Game::SpawnEnemy()
{
	//Random
	std::string spawn_type = this->spawn_set[this->space_level - 1];
	char type = spawn_type[rand() % 20];
	std::string spawn_move = this->spawn_movement[this->space_level - 1];
	char move = spawn_move[rand() % 20];
	int color;
	int movement;
	switch (type)
	{
	case 'R':
		color = 0;
		break;
	case 'B':
		color = 1;
		break;
	case 'G':
		color = 2;
		break;
	case 'Y':
		color = 3;
		break;
	case 'P':
		color = 4;
		break;
	case 'S':
		color = 5;
		break;
	default:
		break;
	}
	switch (move)
	{
	case 'N':
		movement = 0;
		break;
	case 'S':
		movement = rand() % 2 + 1;
		break;
	case 'T':
		movement = 3;
		break;
	default:
		break;
	}

	int level_stat[] = { 1,2,3,4,5,10 };
	int hp_stat[] = { 1,2,3,4,5,10 };
	int score_stat[] = { 10,20,30,40,50,200 };

	int rand_scale = rand() % 65 + 40;
	float scale = (float)rand_scale / 100;

	int rand_posY = rand() % (window->getSize().y - (int)(120 * scale)) + (int)(60 * scale);
	sf::Vector2f enemy_pos = sf::Vector2f(window->getSize().x, rand_posY);

	this->enemies.push_back(Enemy(&enemy_texture[color], hp_stat[color], level_stat[color], enemy_speed, score_stat[color],enemy_pos,scale, movement));
}

void Game::updateEnemyStat()
{
	switch (this->space_level)
	{
	case 1:
		this->enemy_speed = 100.f;
		this->maxDelaySpawn = 1.0f;
		break;
	case 2:
		this->enemy_speed = 150.f;
		this->maxDelaySpawn = 0.9f;
		break;
	case 3:
		this->enemy_speed = 200.f;
		this->maxDelaySpawn = 0.8f;
		break;
	case 4:
		this->enemy_speed = 250.f;
		this->maxDelaySpawn = 0.7f;
		break;
	case 5:
		this->enemy_speed = 300.f;
		this->maxDelaySpawn = 0.6f;
		break;
	case 6:
		this->enemy_speed = 350.f;
		this->maxDelaySpawn = 0.5f;
		break;
	case 7:
		this->enemy_speed = 400.f;
		this->maxDelaySpawn = 0.4f;
		break;
	case 8:
		this->enemy_speed = 450.f;
		this->maxDelaySpawn = 0.3f;
		break;
	case 9:
		this->enemy_speed = 500.f;
		this->maxDelaySpawn = 0.2f;
		break;
	case 10:
		this->enemy_speed = 550.f;
		this->maxDelaySpawn = 0.1f;
		break;
	default:
		break;
	}
}

void Game::updateMusic()
{
	if (this->music.getGameMusic().getStatus() == sf::SoundSource::Stopped)
	{
		this->music.StopGameMusic();
		this->music_index = (this->music_index + 1) % 5;
		this->music.setGameMusicIndex(music_index);
		this->music.PlayGameMusic();
	}
}

void Game::stopMusic()
{
	this->music.StopGameMusic();
}

void Game::Update(float deltaTime)
{
	this->UpdateMousePos(window);
		
	if (world_alive)
	{
		//Space Level Check
		this->updateEnemyStat();
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
			this->player[i].setMenuFreeze(this->menu_cooldown);//Bounce Play Button
			this->player[i].updatePlayer(window, mouse_position, deltaTime);
			//Bullet Update
			for (int j = 0; j < player[i].get_bullets().size(); j++)
			{
				this->player[i].get_bullets()[j].updateBullet(deltaTime);
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
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore() * this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
				this->player[i].get_lasers()[j].updateLaser(deltaTime);
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
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore() * this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
				this->player[i].get_plasmas()[j].updatePlasma(deltaTime);
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
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
				this->player[i].get_rockets()[j].updateRocket(deltaTime);
				//Rocket vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_rockets()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						rocket_hitted_index = k;
						this->player[i].explosionFlak(this->enemies[k].getPosition());
						this->player[i].get_rockets().erase(this->player[i].get_rockets().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getRocketDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							if (k > rocket_hitted_index)
								rocket_hitted_index--;
							if (k == rocket_hitted_index)
								rocket_hitted_index = -1;
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
				this->player[i].get_flaks()[j].updateBullet(deltaTime);
				//Flak vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_flaks()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()) && k != rocket_hitted_index)
					{
						this->player[i].get_flaks().erase(this->player[i].get_flaks().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getFlakDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
				this->player[i].get_tricannons()[j].updateTriCannon(deltaTime);
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
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
			for (int j = 0; j < player[i].get_mines().size(); j++)
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
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
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
			//Nuke Update
			for (int j = 0; j < player[i].get_nukes().size(); j++)
			{
				this->player[i].get_nukes()[j].updateNuke(deltaTime);
				//Nuke vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_nukes()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()))
					{
						nuke_hitted_index = k;
						this->player[i].nukeExplosionFlak(this->enemies[k].getPosition());
						this->player[i].get_nukes().erase(this->player[i].get_nukes().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getNukeDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							if (k > nuke_hitted_index)
								nuke_hitted_index--;
							if (k == nuke_hitted_index)
								nuke_hitted_index = -1;
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_nukes()[j].get_position().x > this->window->getSize().x || this->player[i].get_nukes()[j].get_position().x < 0 || this->player[i].get_nukes()[j].get_position().y > this->window->getSize().y || this->player[i].get_nukes()[j].get_position().y < 0)
				{
					this->player[i].get_nukes().erase(this->player[i].get_nukes().begin() + j);
					return;
				}
			}
			//Nuke Flak Update
			for (int j = 0; j < player[i].get_nukeFlak().size(); j++)
			{
				this->player[i].get_nukeFlak()[j].updateBullet(deltaTime);
				//Flak vs Enemy
				for (int k = 0; k < enemies.size(); k++)
				{
					if (this->player[i].get_nukeFlak()[j].getGlobalBounds().intersects(this->enemies[k].getGlobalBounds()) && k != nuke_hitted_index)
					{
						this->player[i].get_nukeFlak().erase(this->player[i].get_nukeFlak().begin() + j);
						if (this->enemies[k].getHp() > 0)
							this->enemies[k].receiveDamage(this->player[i].getNukeFlakDamage());
						if (this->enemies[k].getHp() <= 0)
						{
							//Update Score
							this->score += this->enemies[k].getScore() * this->score_multipier;
							//Texttag
							this->texttags.push_back(Texttag(&this->font, std::to_string((int)(this->enemies[k].getScore()* this->score_multipier)), this->enemies[k].getPosition()));
							//Item Spawn
							if (this->enemies[k].getLevel() == 10)
							{
								int item_type;
								char item_char = item_spawn_set[rand() % 20];
								switch (item_char)
								{
								case 'H':
									item_type = rand() % 2;
									break;
								case 'W':
									item_type = rand() % 5 + 2;
									break;
								case 'N':
									item_type = 7;
									break;
								default:
									break;
								}
								this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
							}
							else
							{
								int item_chance = rand() % 100 + 1;
								if (item_chance <= 10)
								{
									int item_type;
									char item_char = item_spawn_set[rand() % 20];
									switch (item_char)
									{
									case 'H':
										item_type = rand() % 2;
										break;
									case 'W':
										item_type = rand() % 5 + 2;
										break;
									case 'N':
										item_type = 7;
										break;
									default:
										break;
									}
									this->items.push_back(Item(&this->item_texture[item_type], this->enemies[k].getPosition(), item_type));
								}
							}
							this->enemies.erase(this->enemies.begin() + k);
						}
						return;
					}
				}
				//Window Check
				if (this->player[i].get_nukeFlak()[j].get_position().x > this->window->getSize().x || this->player[i].get_nukeFlak()[j].get_position().x < 0 || this->player[i].get_nukeFlak()[j].get_position().y > this->window->getSize().y || this->player[i].get_nukeFlak()[j].get_position().y < 0)
				{
					this->player[i].get_nukeFlak().erase(this->player[i].get_nukeFlak().begin() + j);
					return;
				}
			}
			//World Integrity Check
			if (this->player[i].getIntegrity() <= 0)
			{
				//Game Over
				this->world_alive = 0;
				Scoreboard(this->window).writeFile(this->player_name, this->score, this->difficulty);
			}
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
					this->player[j].receivedDamage(this->enemies[i].getLevel() * this->damage_multipier);
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
						this->texttags.push_back(Texttag(&this->font, "+15 Health", this->items[i].getPosition()));
						break;
					case 1: // Shield
						this->player[j].receivedShield(10);
						this->texttags.push_back(Texttag(&this->font, "+10 Shield", this->items[i].getPosition()));
						break;
					case 2: // Laser Ammo
						this->player[j].gainLaserAmmo(10);
						this->texttags.push_back(Texttag(&this->font, "+10 Laser Ammo", this->items[i].getPosition()));
						break;
					case 3: // Plasma Ammo
						this->player[j].gainPlasmaAmmo(40);
						this->texttags.push_back(Texttag(&this->font, "+40 Plasma Ammo", this->items[i].getPosition()));
						break;
					case 4: //Rocket Ammo
						this->player[j].gainRocketAmmo(3);
						this->texttags.push_back(Texttag(&this->font, "+3 Rocket Ammo", this->items[i].getPosition()));
						break;
					case 5: //Tri Ammo
						this->player[j].gainTriAmmo(20);
						this->texttags.push_back(Texttag(&this->font, "+20 Tri Ammo", this->items[i].getPosition()));
						break;
					case 6: //Mine Ammo
						this->player[j].gainMineAmmo(5);
						this->texttags.push_back(Texttag(&this->font, "+5 Mine Ammo", this->items[i].getPosition()));
						break;
					case 7: //Nuke
						this->player[j].gainNukeAmmo(1);
						this->texttags.push_back(Texttag(&this->font, "+1 Nuke", this->items[i].getPosition()));
						break;
					default:
						break;
					}
					this->items.erase(this->items.begin() + i);
					return;
				}
			}
		}

		//Update Texttag
		for (int i = 0; i < this->texttags.size(); i++)
		{
			this->texttags[i].updateTextTag(deltaTime);
			if (this->texttags[i].getInitPosition().y - this->texttags[i].getPosition().y > 200.f)
			{
				this->texttags.erase(this->texttags.begin() + i);
				break;
			}

			if (this->texttags[i].getPosition().y < 0.f)
			{
				this->texttags.erase(this->texttags.begin() + i);
				break;
			}
		}

		//Update Time
		if (this->delaySpawn < this->maxDelaySpawn)
			this->delaySpawn += deltaTime;

		//Increase Max Enemy
		if (this->timeIncreaseSpawn < this->maxTimeIncreaseSpawn)
			this->timeIncreaseSpawn += deltaTime;
		else
		{
			this->maxEnemies++;
			this->timeIncreaseSpawn = 0.0f;
		}

		//Increase Space Level
		if (this->timeIncreaseLevel < 180.f)
			this->timeIncreaseLevel += deltaTime;
		else
		{
			this->space_level++;
			if (this->space_level > this->space_limit)
				this->space_level = this->space_limit;
			this->timeIncreaseLevel = 0.0f;
		}
	}

	//Menu Bounce
	if (this->menu_cooldown)
	{
		if (this->menu_freeze < 0.15f)
			this->menu_freeze += deltaTime;

		if (this->menu_freeze >= 0.15f)
			this->menu_cooldown = false;
	}
}

void Game::Render()
{
	this->window->clear();
	
	//Background
	this->window->draw(this->background_sprite);

	//Player Ship
	for (int i = 0; i < this->player.size(); i++)
		this->player[i].renderPlayer(*this->window);

	//Item
	for (int i = 0; i < this->items.size(); i++)
		this->items[i].renderItem(*this->window);

	//Enemy Asteroid
	for (int i = 0; i < this->enemies.size(); i++)
		this->enemies[i].renderEnemies(*this->window);
	
	//Texttag
	for (int i = 0; i < this->texttags.size(); i++)
		this->texttags[i].renderTextTag(*this->window);

	//Player UI
	this->window->draw(this->player_text);
	this->window->draw(this->difficulty_text);

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
	this->window->draw(world_icon);
	this->window->draw(integrity_indicator);
	this->window->draw(integrityBarMax);
	this->window->draw(integrityBar);

	//Score
	this->window->draw(score_text);

	//Weapon UI
	this->window->draw(weapon_name);
	this->window->draw(ammo_amount);
	this->window->draw(weapon_icon);
	for (int i = 0; i < 6; i++)
	{
		this->window->draw(weapon_ammo[i]);
		this->window->draw(ammo_list[i]);
	}
	
	this->window->display();
}

void Game::Reset()
{
	//Player
	this->player.clear();
	this->world_alive = 1;

	//Enemy
	this->enemies.clear();

	//Item
	this->items.clear();

	//Texttag
	this->texttags.clear();

	//Score
	this->score = 0;

	//Menu Bounce
	this->menu_freeze = 0.0f;
	this->menu_cooldown = 1;

	//Time
	this->delaySpawn = 0.0f;
	this->timeIncreaseSpawn = 0.0f;
	this->timeIncreaseLevel = 0.0f;
}

void Game::Init()
{
	switch (this->difficulty)
	{
	case 0://Easy
		//Player
		this->player.push_back(Player(&player_texture,&bullet_texture, &plasma_texture, &rocket_texture, &tri_texture, &mine_texture, &nuke_texture, &nukeFlak_texture, 1200));
		this->score_multipier = 0.5f;
		//Enemy
		this->space_level = 1;
		this->damage_multipier = 1.f;
		this->maxEnemies = 10;
		this->maxTimeIncreaseSpawn = 180.f;
		this->space_limit = 6;
		break;
	case 1://Medium
		//Player
		this->player.push_back(Player(&player_texture, &bullet_texture, &plasma_texture, &rocket_texture, &tri_texture,&mine_texture, &nuke_texture, &nukeFlak_texture, 1000));
		this->score_multipier = 1.0f;
		//Enemy
		this->space_level = 2;
		this->damage_multipier = 1.f;
		this->maxEnemies = 15;
		this->maxTimeIncreaseSpawn = 150.f;
		this->space_limit = 7;
		break;
	case 2://Hard
		//Player
		this->player.push_back(Player(&player_texture, &bullet_texture, &plasma_texture, &rocket_texture, &tri_texture, &mine_texture, &nuke_texture, &nukeFlak_texture, 800));
		this->score_multipier = 1.5f;
		//Enemy
		this->space_level = 3;
		this->damage_multipier = 2.f;
		this->maxEnemies = 20;
		this->maxTimeIncreaseSpawn = 120.f;
		this->space_limit = 8;
		break;
	case 3://Insane
		//Player
		this->player.push_back(Player(&player_texture, &bullet_texture, &plasma_texture, &rocket_texture, &tri_texture, &mine_texture, &nuke_texture, &nukeFlak_texture, 600));
		this->score_multipier = 2.0f;
		//Enemy
		this->space_level = 4;
		this->damage_multipier = 2.f;
		this->maxEnemies = 25;
		this->maxTimeIncreaseSpawn = 90.f;
		this->space_limit = 9;
		break;
	case 4://Apocalypse
		//Player
		this->player.push_back(Player(&player_texture, &bullet_texture, &plasma_texture, &rocket_texture, &tri_texture, &mine_texture, &nuke_texture, &nukeFlak_texture, 500));
		this->score_multipier = 2.5f;
		//Enemy
		this->space_level = 5;
		this->damage_multipier = 3.f;
		this->maxEnemies = 30;
		this->maxTimeIncreaseSpawn = 60.f;
		this->space_limit = 10;
		break;
	default:
		break;
	}

	this->music_index = rand() % 5;
	this->music.setGameMusicIndex(music_index);
}
