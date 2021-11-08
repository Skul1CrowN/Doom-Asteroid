#define _CRT_SECURE_NO_WARNINGS
#include "Scoreboard.h"

Scoreboard::Scoreboard(sf::RenderWindow* window)
{
	//Background
	this->window = window;
	this->background_texture.loadFromFile("Images/leaderboard_background.png");
	this->background_sprite.setTexture(this->background_texture);

	//Font
	this->font.loadFromFile("Fonts/neuropol.ttf");

	//Leaderborad UI
	this->leaderboard_text.setFont(font);
	this->leaderboard_text.setCharacterSize(64);
	this->leaderboard_text.setString("Leaderboard");
	this->leaderboard_text.setOrigin(sf::Vector2f(this->leaderboard_text.getLocalBounds().width / 2, this->leaderboard_text.getLocalBounds().height / 2));
	this->leaderboard_text.setPosition(sf::Vector2f(960.f, 200.f));
	for (int i = 0; i < 5; i++)
	{
		this->num_text[i].setFont(font);
		this->num_text[i].setString(std::to_string(i + 1) + ".");
		this->num_text[i].setCharacterSize(32);
		this->num_text[i].setPosition(sf::Vector2f(600.f, 370.f + i * 80));
		
		this->name_text[i].setFont(font);
		this->name_text[i].setCharacterSize(32);
		this->name_text[i].setPosition(sf::Vector2f(680.f, 370.f + i * 80));

		this->score_text[i].setFont(font);
		this->score_text[i].setCharacterSize(32);
		this->score_text[i].setPosition(sf::Vector2f(1050.f, 370.f + i * 80));
	}

	//Button Text
	this->back_text.setFont(font);
	this->back_text.setCharacterSize(36);
	this->back_text.setString("Back");
	this->back_text.setOrigin(sf::Vector2f(this->back_text.getLocalBounds().width / 2, this->back_text.getLocalBounds().height / 2));
	this->back_text.setPosition(sf::Vector2f(450.f, 850.f));

	this->difficulty_text.setFont(font);
	this->difficulty_text.setCharacterSize(24);
	this->difficulty_text.setString("Difficulty: ");
	this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width / 2, this->difficulty_text.getLocalBounds().height / 2));
	this->difficulty_text.setPosition(sf::Vector2f(870.f, 300.f));

	this->difficulty_selected.setFont(font);
	this->difficulty_selected.setCharacterSize(24);
	this->difficulty_selected.setString("Easy");
	this->difficulty_selected.setFillColor(sf::Color(51, 255, 51));
	this->difficulty_selected.setOrigin(sf::Vector2f(this->difficulty_selected.getLocalBounds().width / 2, this->difficulty_selected.getLocalBounds().height / 2));
	this->difficulty_selected.setPosition(sf::Vector2f(1000.f, 300.f));
	
	this->reset_text.setFont(font);
	this->reset_text.setCharacterSize(32);
	this->reset_text.setString("Reset Score");
	this->reset_text.setOrigin(sf::Vector2f(this->reset_text.getLocalBounds().width / 2, this->reset_text.getLocalBounds().height / 2));
	this->reset_text.setPosition(sf::Vector2f(1380.f, 850.f));

	//Cursor
	this->cursor.loadFromFile("Images/cursor.png");

	this->cursor_sprite.setTexture(this->cursor);

	//Init File when not exist
	for (int i = 0; i < 5; i++)
	{
		fileDir = "./Score/" + fileName[i];
		this->fptr = fopen(fileDir.c_str(), "rb");
		if (this->fptr == NULL)
		{
			this->fptr = fopen(fileDir.c_str(), "wb");
			if (this->fptr == NULL)
			{
				exit(1);
			}
			else
			{
				fclose(this->fptr);
			}
		}
		else
		{
			fclose(this->fptr);
		}
	}
}

bool Scoreboard::sortdesc(const std::tuple<std::string, int>& a, const std::tuple<std::string, int>& b)
{
	return (std::get<1>(a) > std::get<1>(b));
}

void Scoreboard::writeFile(std::string name, int score, int difficulty)
{
	this->user_list.clear();
	readFile(difficulty);
	this->user_tuple = make_tuple(name, score);
	this->user_list.push_back(user_tuple);
	sort(user_list.begin(), user_list.end(), sortdesc);
	while (user_list.size() > 5)
		user_list.pop_back();

	fileDir = "./Score/" + fileName[difficulty];
	this->fptr = fopen(fileDir.c_str(), "wb");
	for (int i = 0; i < user_list.size(); i++)
	{
		this->name = std::get<0>(user_list[i]);
		this->score = std::get<1>(user_list[i]);
		fprintf(fptr, "%s %d\n", this->name.c_str(), this->score);
	}
	fclose(this->fptr);
}

void Scoreboard::readFile(int difficulty)
{
	fileDir = "./Score/" + fileName[difficulty];
	this->fptr = fopen(fileDir.c_str(), "rb");
	while (fscanf(fptr, "%s %d\n", temp, &score) == 2)
	{
		this->name = temp;
		this->user_tuple = make_tuple(name, score);
		this->user_list.push_back(this->user_tuple);
	}
	fclose(this->fptr);
}

void Scoreboard::resetFile()
{
	for (int i = 0; i < 5; i++)
	{
		fileDir = "./Score/" + fileName[i];
		this->fptr = fopen(fileDir.c_str(), "wb");
		fclose(this->fptr);
	}
}

bool Scoreboard::returnToMenu()
{
	return this->toMenu;
}

void Scoreboard::resetReturntoMenu()
{
	this->toMenu = 0;
}

void Scoreboard::updateDifficulty()
{
	this->difficulty_input = (this->difficulty_input + 1) % 5;
	switch (this->difficulty_input)
	{
	case 0:
		this->difficulty_selected.setString("Easy");
		this->difficulty_selected.setFillColor(sf::Color(51, 255, 51));
		break;
	case 1:
		this->difficulty_selected.setString("Medium");
		this->difficulty_selected.setFillColor(sf::Color(255, 255, 51));
		break;
	case 2:
		this->difficulty_selected.setString("Hard");
		this->difficulty_selected.setFillColor(sf::Color(255, 128, 51));
		break;
	case 3:
		this->difficulty_selected.setString("Insane");
		this->difficulty_selected.setFillColor(sf::Color(255, 51, 51));
		break;
	case 4:
		this->difficulty_selected.setString("Apocalypse");
		this->difficulty_selected.setFillColor(sf::Color(128, 51, 255));
	default:
		break;
	}
}

void Scoreboard::transitionDelay()
{
	this->transition = 1;
}

void Scoreboard::updateScore()
{
	this->user_list.clear();
	for (int i = 0; i < 5; i++)
	{
		name_text[i].setString("");
		score_text[i].setString("");
	}
	readFile(this->difficulty_input);
	for (int i = 0; i < user_list.size(); i++)
	{
		name_text[i].setString(std::get<0>(user_list[i]));
		score_text[i].setString(std::to_string(std::get<1>(user_list[i])));
	}
}

void Scoreboard::updateButton(float deltaTime)
{
	//Cursor
	this->cursor_sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition()));

	//Mouse Debounce
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->mouseheldTime += deltaTime;
	else
		this->mouseheldTime = 0;

	if (this->mouseheldTime >= 0.3f)
		this->mouseheld = 1;
	else
		this->mouseheld = 0;

	//Transition Debounce
	if (transition)
	{
		if (transitionCooldown < 0.3f)
			this->transitionCooldown += deltaTime;
		else
			this->transition = 0;
	}
	else
		this->transitionCooldown = 0.0f;

	//Back
	if (this->back_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->back_text.setScale(sf::Vector2f(1.1f, 1.1f));
		this->back_text.setFillColor(sf::Color(255, 0, 0));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->toMenu = 1;
		}
	}
	else
	{
		this->back_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->back_text.setFillColor(sf::Color(255, 255, 255));
	}

	//Difficulty
	if (this->difficulty_selected.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->difficulty_selected.setScale(sf::Vector2f(1.1f, 1.1f));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			if (!click_bounce)
			{
				click_bounce = 1;
				this->updateDifficulty();
			}
		}
		else
			click_bounce = 0;
	}
	else
	{
		this->difficulty_selected.setScale(sf::Vector2f(1.0f, 1.0f));
	}

	//Reset Score
	if (this->reset_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->reset_text.setScale(sf::Vector2f(1.1f, 1.1f));
		this->reset_text.setFillColor(sf::Color(255, 0, 0));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->resetFile();
		}
	}
	else
	{
		this->reset_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->reset_text.setFillColor(sf::Color(255, 255, 255));
	}
}

void Scoreboard::render()
{
	this->window->clear();

	this->window->draw(this->background_sprite);

	this->window->draw(this->leaderboard_text);

	this->window->draw(this->back_text);

	this->window->draw(this->difficulty_text);

	this->window->draw(this->difficulty_selected);

	this->window->draw(this->reset_text);

	for (int i = 0; i < 5; i++)
	{
		this->window->draw(this->num_text[i]);

		this->window->draw(this->name_text[i]);
		
		this->window->draw(this->score_text[i]);
	}

	this->window->draw(cursor_sprite);

	this->window->display();
}
