#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<algorithm>
#include<string>
class Scoreboard
{
private:
	//Background
	sf::RenderWindow* window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	//Text
	sf::Font font;
	sf::Text leaderboard_text;

	sf::Text num_text[5];
	sf::Text name_text[5];
	sf::Text score_text[5];

	//File Management
	FILE* fptr;
	char temp[255];
	std::string name;
	int score;
	std::tuple<std::string, int> user_tuple;
	std::vector< std::tuple<std::string, int> > user_list;

	std::string fileName[5] = {
		"easy.bin",
		"medium.bin",
		"hard.bin",
		"insane.bin",
		"apocalypse.bin"
	};
	std::string fileDir;
	int difficulty_input = 0;

	//Button Text
	sf::Text back_text;
	sf::Text reset_text;
	sf::Text difficulty_text;;
	sf::Text difficulty_selected;
	
	//Mouse Hold Debounce
	float mouseheld = 0;
	float mouseheldTime = 0.0f;

	//Transition Debounce
	float transition = 0;
	float transitionCooldown = 0.0f;

	//Other Debounce
	bool toMenu = 0;
	bool click_bounce = 0;

	//Cursor
	sf::Texture cursor;
	sf::Sprite cursor_sprite;
public:
	Scoreboard(sf::RenderWindow* window);
	static bool sortdesc(const std::tuple<std::string, int>& a, const std::tuple<std::string, int>& b);
	void writeFile(std::string name, int score, int difficulty);
	void readFile(int difficulty);
	void resetFile();

	bool returnToMenu();
	void resetReturntoMenu();

	void updateDifficulty();
	void transitionDelay();
	void updateScore();
	void updateButton(float deltaTime);
	void render();
};

