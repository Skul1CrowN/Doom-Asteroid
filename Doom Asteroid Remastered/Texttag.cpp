#include "Texttag.h"

Texttag::Texttag(sf::Font* font, std::string text, sf::Vector2f position)
{
	this->init_position = position;
	this->position = this->init_position;

	this->tag.setFont(*font);
	this->tag.setCharacterSize(18);
	this->tag.setString(text);
	this->tag.setOrigin(sf::Vector2f(this->tag.getLocalBounds().width / 2, this->tag.getLocalBounds().height / 2));
	this->tag.setPosition(this->init_position);

	this->speed = 200.f;
}

void Texttag::updateTextTag(float deltaTime)
{
	this->tag.move(sf::Vector2f(0.f, -speed * deltaTime));
	this->position = this->tag.getPosition();
}

sf::Vector2f Texttag::getInitPosition()
{
	return this->init_position;
}

sf::Vector2f Texttag::getPosition()
{
	return this->position;
}

void Texttag::renderTextTag(sf::RenderTarget& target)
{
	target.draw(tag);
}
