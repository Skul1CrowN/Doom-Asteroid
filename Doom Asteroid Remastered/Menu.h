#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Menu
{
	//Background
	sf::RenderWindow* window;

	//Font
	sf::Font font;

	//State
	int state;
	//0 Menu
	//1 Input
	//2 Play
	//3 Score
	//4 Tutorial
	//5 Quit

	//Menu
	sf::Text play_text;
	sf::Text score_text;
	sf::Text tutorial;
	sf::Text quit;

	//Input
	sf::Text name;
	sf::Text input;
	sf::Text back;
	sf::Text play_text2;

	//Time
	float delayClick;
	float delayClickMax;
};

