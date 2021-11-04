#include "Player.h"

#include<cmath>
#include<iostream>

Player::Player(sf::Texture* texture, sf::Texture* bullet, sf::Texture* plasma, sf::Texture* rocket, sf::Texture* tricannon, sf::Texture* mine, sf::Texture* nuke, sf::Texture* nukeFlak, int integrity)
{
	this->player_texture = texture;
	this->player_sprite.setTexture(*this->player_texture);
	this->player_sprite.setScale(sf::Vector2f(0.15f, 0.15f));
	this->player_sprite.setPosition(sf::Vector2f(50.f, 540.f));
	this->angle = 0;

	this->maxIntegrity = integrity;
	this->integrity = this->maxIntegrity;
	this->maxHp = 100;
	this->hp = this->maxHp;
	this->maxShield = 50;
	this->shield = 0;

	this->hull_breach = 0;
	this->repaired = 0.f;
	this->repairRequired = 10.f;
	this->decayRate = 0.2;

	this->normal_damage = 1;
	this->laser_damage = 3;
	this->plasma_damage = 1;
	this->rocket_damage = 5;
	this->flak_damage = 1;
	this->tri_damage = 1;
	this->mine_damage = 1;
	this->nuke_damage = 10;
	this->nuke_flak_damage = 10;

	this->weapon_type = 1;
	this->type_runner = this->weapon_type;
	this->laser_ammo = 0;
	this->plasma_ammo = 0;
	this->rocket_ammo = 0;
	this->tri_ammo = 0;
	this->mine_ammo = 0;
	this->nuke_ammo = 0;

	this->speed = 500.f;

	this->maxDelayShoot = 0.25f;
	this->delayShoot = this->maxDelayShoot;

	//Hp bar
	this->hpBar.setSize(sf::Vector2f(80.f, 5.f));
	this->hpBar.setFillColor(sf::Color(51, 255, 51));
	this->hpBar.setOrigin(sf::Vector2f(
		this->hpBar.getLocalBounds().width / 2,
		this->hpBar.getLocalBounds().height / 2)
	);

	this->hpBarMax.setSize(sf::Vector2f(80.f, 5.f));
	this->hpBarMax.setFillColor(sf::Color(11, 71, 11));
	this->hpBarMax.setOrigin(sf::Vector2f(
		this->hpBarMax.getLocalBounds().width / 2,
		this->hpBarMax.getLocalBounds().height / 2)
	);

	//Shield bar
	this->shieldBar.setSize(sf::Vector2f(80.f, 5.f));
	this->shieldBar.setFillColor(sf::Color(102, 178, 255));
	this->shieldBar.setOrigin(sf::Vector2f(
		this->shieldBar.getLocalBounds().width / 2,
		this->shieldBar.getLocalBounds().height / 2)
	);

	this->shieldBarMax.setSize(sf::Vector2f(80.f, 5.f));
	this->shieldBarMax.setFillColor(sf::Color(0, 76, 153));
	this->shieldBarMax.setOrigin(sf::Vector2f(
		this->shieldBarMax.getLocalBounds().width / 2,
		this->shieldBarMax.getLocalBounds().height / 2)
	);
	
	//Repair Bar
	this->repairBar.setFillColor(sf::Color(255, 255, 255));
	this->repairBar.setSize(sf::Vector2f(80.f, 5.f));
	this->repairBar.setOrigin(sf::Vector2f(
		this->repairBar.getLocalBounds().width / 2,
		this->repairBar.getLocalBounds().height / 2)
	);

	this->repairBarMax.setFillColor(sf::Color(101, 101, 101));
	this->repairBarMax.setSize(sf::Vector2f(80.f, 5.f));
	this->repairBarMax.setOrigin(sf::Vector2f(
		this->repairBarMax.getLocalBounds().width / 2,
		this->repairBarMax.getLocalBounds().height / 2)
	);

	this->bullet_texture = bullet;
	this->plasma_texture = plasma;
	this->rocket_texture = rocket;
	this->tri_texture = tricannon;
	this->mine_texture = mine;
	this->nuke_texture = nuke;
	this->nukeFlak_texture = nukeFlak;
	this->menu_cooldown = 1;
	this->rightclick = 1;

}

std::vector<Bullet>& Player::get_bullets()
{
	return this->bullets;
}

std::vector<Laser>& Player::get_lasers()
{
	return this->lasers;
}

std::vector<Plasma>& Player::get_plasmas()
{
	return this->plasmas;
}

std::vector<Rocket>& Player::get_rockets()
{
	return this->rockets;
}

std::vector<Bullet>& Player::get_flaks()
{
	return this->flaks;
}

std::vector<Mine>& Player::get_mines()
{
	return this->mines;
}

std::vector<Nuke>& Player::get_nukes()
{
	return this->nukes;
}

std::vector<Bullet>& Player::get_nukeFlak()
{
	return this->nuke_flaks;
}

std::vector<TriCannon>& Player::get_tricannons()
{
	return this->tricannons;
}

sf::FloatRect Player::getGlobalBounds()
{
	return this->player_sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
	return this->player_sprite.getPosition();
}

int& Player::getIntegrity()
{
	return this->integrity;
}

int& Player::getMaxIntegrity()
{
	return this->maxIntegrity;
}

int& Player::getHp()
{
	return this->hp;
}

int& Player::getHpMax()
{
	return this->maxHp;
}

int& Player::getShield()
{
	return this->shield;
}

int& Player::getShieldMax()
{
	return this->maxShield;
}

int& Player::getWeaponType()
{
	return this->weapon_type;
}

int& Player::getLaserAmmo()
{
	return this->laser_ammo;
}

int& Player::getPlasmaAmmo()
{
	return this->plasma_ammo;
}

int& Player::getRocketAmmo()
{
	return this->rocket_ammo;
}

int& Player::getTriAmmo()
{
	return this->tri_ammo;
}

int& Player::getMineAmmo()
{
	return this->mine_ammo;
}

int& Player::getNukeAmmo()
{
	return this->nuke_ammo;
}

void Player::explosionFlak(sf::Vector2f position)
{
	float angle = 0;
	for (int i = 0; i < 32; i++)
	{
		angle += 11.25;
		this->flaks.push_back(Bullet(this->bullet_texture,position, angle));
	}
}

void Player::nukeExplosionFlak(sf::Vector2f position)
{
	float angle = 0;
	for (int i = 0; i < 72; i++)
	{
		angle += 5.0;
		this->nuke_flaks.push_back(Bullet(this->nukeFlak_texture, position, angle));
	}
}

bool& Player::getHullBreach()
{
	return this->hull_breach;
}

float& Player::getRepaired()
{
	return this->repaired;
}

float& Player::getRepairRequired()
{
	return this->repairRequired;
}

bool& Player::getInvincibility()
{
	return this->invincibility;
}

int& Player::getNormalDamage()
{
	return this->normal_damage;
}

int& Player::getLaserDamage()
{
	return this->laser_damage;
}

int& Player::getPlasmaDamage()
{
	return this->plasma_damage;
}

int& Player::getRocketDamage()
{
	return this->rocket_damage;
}

int& Player::getFlakDamage()
{
	return this->flak_damage;
}

int& Player::getTriDamage()
{
	return this->tri_damage;
}

int& Player::getMineDamage()
{
	return this->mine_damage;
}

int& Player::getNukeDamage()
{
	return this->nuke_damage;
}

int& Player::getNukeFlakDamage()
{
	return this->nuke_flak_damage;
}

void Player::setMenuFreeze(bool menu_cooldown)
{
	this->menu_cooldown = menu_cooldown;
}

void Player::repairHP(int hp)
{
	this->hp += hp;
	if (this->hp > this->maxHp)
		this->hp = this->maxHp;
}

void Player::receivedShield(int shield)
{
	this->shield += shield;
	if (this->shield > this->maxShield)
		this->shield = this->maxShield;
}

void Player::gainLaserAmmo(int amount)
{
	this->laser_ammo += amount;
}

void Player::gainPlasmaAmmo(int amount)
{
	this->plasma_ammo += amount;
}

void Player::gainRocketAmmo(int amount)
{
	this->rocket_ammo += amount;
}

void Player::gainTriAmmo(int amount)
{
	this->tri_ammo += amount;
}

void Player::gainMineAmmo(int amount)
{
	this->mine_ammo += amount;
}

void Player::gainNukeAmmo(int amount)
{
	this->nuke_ammo += amount;
}

void Player::receivedDamage(int damage)
{
	if (this->shield > 0)
	{
		this->shield -= damage;
		if (this->shield < 0)
			this->shield = 0;
	}
	else
	{
		this->hp -= damage;
		if (this->hp < 0)
			this->hp = 0;
	}
}

void Player::receivedWorldDamage(int damage)
{
	this->integrity -= damage;
	if (this->integrity < 0)
		this->integrity = 0;
}

void Player::updatePlayer(sf::RenderWindow* window, sf::Vector2f mouse_position, float deltaTime)
{
	//Check Hull breach
	if (this->hp <= 0)
	{
		this->hull_breach = 1;
	}

	if (this->hull_breach)
		this->player_sprite.setColor(sf::Color(128, 128, 128));
	else
		this->player_sprite.setColor(sf::Color(255, 255, 255));

	//Update Position
	this->player_position = this->player_sprite.getPosition();

	//Update Center
	this->player_sprite.setOrigin(sf::Vector2f(
		this->player_sprite.getLocalBounds().width / 2,
		this->player_sprite.getLocalBounds().height / 2)
	);

	//Rotation
	this->mouse_distance = mouse_position - player_position;
	if (mouse_distance.y < 0)
		this->angle = -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	else
		this->angle = 180 + -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	if (!this->hull_breach)
		this->player_sprite.setRotation(this->angle);

	//Movement
	if (!this->hull_breach)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player_position.y > 50.f)
		{
			this->player_sprite.move(0.0f, -(this->speed) * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_position.x > 50.f)
		{
			this->player_sprite.move(-(this->speed) * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player_position.y < window->getSize().y - 50.f)
		{
			this->player_sprite.move(0.0f, this->speed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_position.x < window->getSize().x - 50.f)
		{
			this->player_sprite.move(this->speed * deltaTime, 0.0f);
		}
	}

	//Combat
	if (!this->hull_breach && !this->menu_cooldown)
	{
		//Shoot
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->delayShoot >= this->maxDelayShoot)
		{
			switch (this->weapon_type)
			{
			case 1:
				this->bullets.push_back(Bullet(this->bullet_texture, player_position, angle));
				break;
			case 2:
				if (this->laser_ammo > 0)
				{
					this->laser_ammo--;
					this->lasers.push_back(Laser(player_position, angle));
				}
				break;
			case 3:
				if (this->plasma_ammo > 0)
				{
					this->plasma_ammo--;
					this->plasmas.push_back(Plasma(this->plasma_texture,player_position, angle));
				}
				break;
			case 4:
				if (this->rocket_ammo > 0)
				{
					this->rocket_ammo--;
					this->rockets.push_back(Rocket(rocket_texture,player_position, angle));
				}
				break;
			case 5:
				if (this->tri_ammo > 0)
				{
					this->tri_ammo--;
					this->tricannons.push_back(TriCannon(this->tri_texture,player_position, angle-2.5f));
					this->tricannons.push_back(TriCannon(this->tri_texture, player_position, angle));
					this->tricannons.push_back(TriCannon(this->tri_texture, player_position, angle+2.5f));
				}
				break;
			case 6:
				if (this->mine_ammo > 0)
				{
					this->mine_ammo--;
					this->mines.push_back(Mine(mine_texture, player_position, angle));
				}
				break;
			case 7:
				if (this->nuke_ammo > 0)
				{
					this->nuke_ammo--;
					this->nukes.push_back(Nuke(nuke_texture, player_position, angle));
				}
				break;
			default:
				break;
			}
			this->delayShoot = 0;
		}
		//Switch Weapon
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			this->weapon_type = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && this->laser_ammo > 0)
		{
			this->weapon_type = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && this->plasma_ammo > 0)
		{
			this->weapon_type = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && this->rocket_ammo > 0)
		{
			this->weapon_type = 4;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && this->tri_ammo > 0)
		{
			this->weapon_type = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && this->mine_ammo > 0)
		{
			this->weapon_type = 6;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && this->nuke_ammo > 0)
		{
			this->weapon_type = 7;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			if (!rightclick)
			{
				rightclick = 1;
				this->type_runner = this->weapon_type + 1;
				if (this->type_runner == 2 && this->laser_ammo <= 0)
					this->type_runner++;
				if (this->type_runner == 3 && this->plasma_ammo <= 0)
					this->type_runner++;
				if (this->type_runner == 4 && this->rocket_ammo <= 0)
					this->type_runner++;
				if (this->type_runner == 5 && this->tri_ammo <= 0)
					this->type_runner++;
				if (this->type_runner == 6 && this->mine_ammo <= 0)
					this->type_runner++;
				if (type_runner > 6)
					this->type_runner = 1;

				this->weapon_type = this->type_runner;
			}
		}
		else
		{
			rightclick = 0;
		}

		//Update Type Weapon
		switch (this->weapon_type)
		{
		case 1:
			this->weapon_type = 1;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.25f;
			this->maxDelayShoot = 0.25f;
			break;
		case 2:
			this->weapon_type = 2;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.35f;
			this->maxDelayShoot = 0.35f;
			break;
		case 3:
			this->weapon_type = 3;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.1f;
			this->maxDelayShoot = 0.1f;
			break;
		case 4:
			this->weapon_type = 4;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.85f;
			this->maxDelayShoot = 0.85f;
			break;
		case 5:
			this->weapon_type = 5;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.25f;
			this->maxDelayShoot = 0.25f;
			break;
		case 6:
			this->weapon_type = 6;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 0.7f;
			this->maxDelayShoot = 0.7f;
			break;
		case 7:
			this->weapon_type = 7;
			this->delayShoot = this->delayShoot / this->maxDelayShoot * 1.5f;
			this->maxDelayShoot = 1.5f;
			break;
		default:
			break;
		}
	}

	//Hull Breach
	if (this->hull_breach)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			this->repaired += deltaTime;
		}
		else
		{
			this->repaired -= deltaTime * this->decayRate;
			if (this->repaired < 0)
				this->repaired = 0;
		}

		if (this->repaired >= this->repairRequired)
		{
			this->hp += this->maxHp * 0.4f;
			this->hull_breach = 0;
			this->repaired = 0;
			this->repairRequired += 5.f;
			this->decayRate += 0.15f;
			if (this->repairRequired > 90.f)
				this->repairRequired = 90.f;
			if (this->decayRate > 1.7f)
				this->decayRate = 1.7f;
		}
	}
	//Hp bar
	if (((float)this->hp / this->maxHp) * 100 >= 75)
	{
		this->hpBar.setSize(sf::Vector2f(80.f * ((float)this->hp / this->maxHp), 5.f));
		this->hpBar.setFillColor(sf::Color(51, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(11, 71, 11));
	}
	else if (((float)this->hp / this->maxHp) * 100 >= 30 && ((float)this->hp / this->maxHp) * 100 < 75)
	{
		this->hpBar.setSize(sf::Vector2f(80.f * ((float)this->hp / this->maxHp), 5.f));
		this->hpBar.setFillColor(sf::Color(255, 255, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 71, 11));
	}
	else
	{
		this->hpBar.setSize(sf::Vector2f(80.f * ((float)this->hp / this->maxHp), 5.f));
		this->hpBar.setFillColor(sf::Color(255, 51, 51));

		this->hpBarMax.setFillColor(sf::Color(71, 11, 11));
	}
	this->hpBar.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 55.f));
	this->hpBarMax.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 55.f));

	//Shield Bar
	this->shieldBar.setSize(sf::Vector2f(80.f * ((float)this->shield / this->maxShield), 5.f));
	this->shieldBar.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 50.f));
	this->shieldBarMax.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 50.f));

	//Repair Bar
	this->repairBar.setSize(sf::Vector2f(80.f * (this->repaired / this->repairRequired), 5.f));
	this->repairBar.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 50.f));
	this->repairBarMax.setPosition(sf::Vector2f(this->player_position) + sf::Vector2f(0.f, 50.f));

	//Time Update
	if (this->delayShoot < this->maxDelayShoot)
		this->delayShoot += deltaTime;
}

void Player::renderPlayer(sf::RenderTarget& target)
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].renderBullet(target);
	}
	for (int i = 0; i < this->lasers.size(); i++)
	{
		this->lasers[i].renderLaser(target);
	}
	for(int i = 0;i < this->plasmas.size();i++)
	{
		this->plasmas[i].renderPlasma(target);
	}
	for (int i = 0; i < this->rockets.size(); i++)
	{
		this->rockets[i].renderRocket(target);
	}
	for (int i = 0; i < this->flaks.size(); i++)
	{
		this->flaks[i].renderBullet(target);
	}
	for (int i = 0; i < this->tricannons.size(); i++)
	{
		this->tricannons[i].renderTriCannon(target);
	}
	for (int i = 0; i < this->mines.size(); i++)
	{
		this->mines[i].renderMine(target);
	}
	for (int i = 0; i < this->nukes.size(); i++)
	{
		this->nukes[i].renderNuke(target);
	}
	for (int i = 0; i < this->nuke_flaks.size(); i++)
	{
		this->nuke_flaks[i].renderBullet(target);
	}
	target.draw(player_sprite);
	if (!hull_breach)
	{
		target.draw(hpBarMax);
		target.draw(hpBar);
		target.draw(shieldBarMax);
		target.draw(shieldBar);
	}
	else
	{
		target.draw(repairBarMax);
		target.draw(repairBar);
	}
}