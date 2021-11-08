#pragma once
#include "Enemy.h"
#include "Music.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include<iostream>
class Menu
{
private:
	//Score
	int score;

	//Background
	sf::RenderWindow* window;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	sf::Event event;

	//Logo
	sf::Texture logo_texture;
	sf::Sprite logo_sprite;

	//Font
	sf::Font font;

	//State
	int state;
	//0 Menu
	//1 Config
	//2 Play
	//3 Score
	//4 Tutorial
	//5 Quit
	//6 Pause Menu
	//7 Game Over

	//Menu
	sf::Text play_text;
	sf::Text score_text;
	sf::Text tutorial_text;
	sf::Text quit_text;
	sf::Text dev_text;

	//Config
	sf::Texture config_texture;
	sf::Sprite config_backgroound;
	std::string player_name;
	sf::Text name;
	sf::Text name_input;
	sf::Text difficulty_text;
	sf::Text difficulty_description;
	sf::Text score_multipier_text;
	sf::Text difficulty_selected;
	sf::Text back_text;
	sf::Text go_text;
	int difficulty_input;
	//0 Easy
	//1 Normal
	//2 Hard
	//3 Insane
	//4 Apocalypse

	//Pause
	sf::Text pause_text;
	sf::Text continue_text;
	sf::Text abandon_text;
	bool click_bounce;
	bool escape_bounce;
	bool type_bounce;

	//GameOver
	sf::Texture gameover_texture;
	sf::Sprite gameover_background;
	sf::Text game_over_text;
	sf::Text menu_text;
	sf::Text final_score_text;

	//Tutorial
	sf::Texture asteroid_texture;
	std::vector<Enemy> rgb_asteroid;
	sf::Texture how_texture;
	sf::Sprite how_background;
	sf::Texture tutorial_texture;
	sf::Sprite tutorial_sprite;
	sf::Text tutorial_back;

	//Music
	Music music;

	//Cursor
	sf::Texture cursor;
	sf::Sprite cursor_sprite;

	//Mouse Debounce
	bool mouseheld;
	float mouseheldTime;

	//Transition Debounce
	bool transition;
	float transitionCooldown;

	bool valid_name;
public:
	Menu(sf::RenderWindow* window);

	void setScore(int score);
	
	void updateCursor();
	void updateMenuState(int state);
	void updateMenuButton(float deltaTime);
	void updatePause(float deltaTime);
	void updateConfig(float deltaTime);
	void updateGameOver(float deltaTime);
	void updateNameInput(sf::Event& event, float deltaTime);
	void updateTutorial(float deltaTime);
	void updateDifficulty();
	void checktriggerPause();
	void backToMenu(bool trigger);
	void updateMusic();
	void stopMusic();
	void updateGameOverMusic();
	void stopGameOverMusic();

	int& getState();
	std::string& getPlayerName();
	int& getDifficulty();
	void drawMainMenu();
	void drawConfig();
	void drawLeaderBoard();
	void drawTutorial();
	void drawPause();
	void drawGameOver();
};

