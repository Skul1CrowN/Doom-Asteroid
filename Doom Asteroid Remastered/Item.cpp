#include "Item.h"

Item::Item(sf::Texture* texture, sf::Vector2f init_position, int type)
{
	this->item_texture = texture;
	this->item_sprite.setTexture(this->item_texture);
	this->item_sprite.setSize(sf::Vector2f(30.f,30.f));
	this->item_sprite.setOrigin(sf::Vector2f(
		this->item_sprite.getLocalBounds().width / 2,
		this->item_sprite.getLocalBounds().height / 2)
	);
	this->item_sprite.setPosition(init_position);
	this->item_type = type;
}

sf::FloatRect Item::getGlobalBounds()
{
	return this->item_sprite.getGlobalBounds();
}

int& Item::getItem()
{
	return this->item_type;
}

void Item::renderItem(sf::RenderTarget& target)
{
	target.draw(this->item_sprite);
}
