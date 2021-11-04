#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Texttag
{
private:
	sf::Text tag;
	float speed;

	sf::Vector2f init_position;
	sf::Vector2f position;
public:
	Texttag(sf::Font* font, std::string text, sf::Vector2f position);

	void updateTextTag(float deltaTime);

	sf::Vector2f getInitPosition();
	sf::Vector2f getPosition();

	void renderTextTag(sf::RenderTarget& target);
};

