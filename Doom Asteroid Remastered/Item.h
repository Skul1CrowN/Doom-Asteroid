#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Item
{
private:
	//Sprite
	sf::Texture* item_texture;
	sf::RectangleShape item_sprite;

	int item_type;
	//0 Repair
	//1 Shield
	//2 Laser Ammo
	//3 Plasma Ammo
	//4 Rocket Ammo
	//5 Tri-Cannon Ammo
	//6 Mine Ammo
	//7 Nuke
public:
	Item(sf::Texture* texture,sf::Vector2f init_position,int type);

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	int& getItem();

	void renderItem(sf::RenderTarget& target);
};

