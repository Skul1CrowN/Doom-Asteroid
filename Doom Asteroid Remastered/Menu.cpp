#include "Menu.h"

Menu::Menu(sf::RenderWindow* window)
{
	//Background
	this->window = window;
	this->background_texture.loadFromFile("Images/menu_background.png");
	this->background_sprite.setTexture(this->background_texture);

	//Logo
	this->logo_texture.loadFromFile("Images/menu_logo.png");
	this->logo_sprite.setTexture(this->logo_texture);
	this->logo_sprite.setOrigin(sf::Vector2f(this->logo_sprite.getLocalBounds().width / 2, this->logo_sprite.getLocalBounds().height / 2));
	this->logo_sprite.setPosition(sf::Vector2f(960.f, 200.f));

	//Font
	this->font.loadFromFile("Fonts/neuropol.ttf");

	//Menu Button
	this->play_text.setFont(font);
	this->play_text.setCharacterSize(36);
	this->play_text.setString("Play!");
	this->play_text.setOrigin(sf::Vector2f(this->play_text.getLocalBounds().width / 2, this->play_text.getLocalBounds().height / 2));
	this->play_text.setPosition(sf::Vector2f(960.f, 450.f));

	this->score_text.setFont(font);
	this->score_text.setCharacterSize(36);
	this->score_text.setString("Leaderboard");
	this->score_text.setOrigin(sf::Vector2f(this->score_text.getLocalBounds().width / 2, this->score_text.getLocalBounds().height / 2));
	this->score_text.setPosition(sf::Vector2f(960.f, 600.f));

	this->quit_text.setFont(font);
	this->quit_text.setCharacterSize(36);
	this->quit_text.setString("Quit");
	this->quit_text.setOrigin(sf::Vector2f(this->quit_text.getLocalBounds().width / 2, this->quit_text.getLocalBounds().height / 2));
	this->quit_text.setPosition(sf::Vector2f(960.f, 750.f));

	this->dev_text.setFont(font);
	this->dev_text.setCharacterSize(24);
	this->dev_text.setString("64010516 Punnawit Wachirasethaherun");
	this->dev_text.setOrigin(sf::Vector2f(this->dev_text.getLocalBounds().width, this->dev_text.getLocalBounds().height / 2));
	this->dev_text.setPosition(sf::Vector2f(1900.f, 20.f));
	this->dev_text.setFillColor(sf::Color(51, 255, 255));

	//Pause Button
	this->pause_text.setFont(font);
	this->pause_text.setCharacterSize(72);
	this->pause_text.setString("Paused");
	this->pause_text.setOrigin(sf::Vector2f(this->pause_text.getLocalBounds().width/2, this->pause_text.getLocalBounds().height / 2));
	this->pause_text.setPosition(sf::Vector2f(960.f, 250.f));

	this->continue_text.setFont(font);
	this->continue_text.setCharacterSize(36);
	this->continue_text.setString("Continue");
	this->continue_text.setOrigin(sf::Vector2f(this->continue_text.getLocalBounds().width/2, this->continue_text.getLocalBounds().height / 2));
	this->continue_text.setPosition(sf::Vector2f(960.f, 400.f));

	this->abandon_text.setFont(font);
	this->abandon_text.setCharacterSize(36);
	this->abandon_text.setString("Abandon");
	this->abandon_text.setOrigin(sf::Vector2f(this->abandon_text.getLocalBounds().width/2, this->abandon_text.getLocalBounds().height / 2));
	this->abandon_text.setPosition(sf::Vector2f(960.f, 500.f));

	//Config Menu
	this->config_texture.loadFromFile("Images/config_background.png");
	this->config_backgroound.setTexture(this->config_texture);

	this->name.setFont(font);
	this->name.setCharacterSize(36);
	this->name.setString("Name:");
	this->name.setOrigin(sf::Vector2f(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2));
	this->name.setPosition(700.f, 390.f);

	this->name_input.setFont(font);
	this->name_input.setCharacterSize(36);
	this->name_input.setOrigin(sf::Vector2f(0, this->name.getLocalBounds().height / 2));
	this->name_input.setPosition(670.f, 460.f);

	this->back_text.setFont(font);
	this->back_text.setCharacterSize(36);
	this->back_text.setString("Back");
	this->back_text.setOrigin(sf::Vector2f(this->back_text.getLocalBounds().width/2, this->back_text.getLocalBounds().height / 2));
	this->back_text.setPosition(650.f, 720.f);

	this->go_text.setFont(font);
	this->go_text.setCharacterSize(36);
	this->go_text.setString("Let's shoot!");
	this->go_text.setOrigin(sf::Vector2f(this->go_text.getLocalBounds().width / 2, this->go_text.getLocalBounds().height / 2));
	this->go_text.setPosition(1200.0f, 720.f);
	
	this->difficulty_text.setFont(font);
	this->difficulty_text.setCharacterSize(36);
	this->difficulty_text.setString("Difficulty:");
	this->difficulty_text.setOrigin(sf::Vector2f(this->difficulty_text.getLocalBounds().width / 2, this->difficulty_text.getLocalBounds().height / 2));
	this->difficulty_text.setPosition(740.f, 540.f);

	this->difficulty_selected.setFont(font);
	this->difficulty_selected.setCharacterSize(36);
	this->difficulty_selected.setString("Easy");
	this->difficulty_selected.setOrigin(sf::Vector2f(this->difficulty_selected.getLocalBounds().width / 2, this->difficulty_selected.getLocalBounds().height / 2));
	this->difficulty_selected.setPosition(930.f, 540.f);
	this->difficulty_selected.setFillColor(sf::Color(51, 255, 51));

	this->difficulty_description.setFont(font);
	this->difficulty_description.setCharacterSize(24);
	this->difficulty_description.setString("Recommended for newbie player");
	this->difficulty_description.setOrigin(sf::Vector2f(0.f, this->difficulty_description.getLocalBounds().height / 2));
	this->difficulty_description.setPosition(650.f, 590.f);

	this->score_multipier_text.setFont(font);
	this->score_multipier_text.setCharacterSize(24);
	this->score_multipier_text.setString("Score Multipier x0.5");
	this->score_multipier_text.setOrigin(sf::Vector2f(0.f, this->score_multipier_text.getLocalBounds().height / 2));
	this->score_multipier_text.setPosition(650.f, 630.f);

	this->escape_bounce = 0;
	this->click_bounce = 0;
	this->type_bounce = 0;
	this->state = 0;
	this->difficulty_input = 0;

	//GameOver
	this->gameover_texture.loadFromFile("Images/gameover_background.png");
	this->gameover_background.setTexture(this->gameover_texture);

	this->game_over_text.setString("Game Over!");
	this->game_over_text.setFont(this->font);
	this->game_over_text.setCharacterSize(56);
	this->game_over_text.setOrigin(sf::Vector2f(this->game_over_text.getLocalBounds().width / 2, this->game_over_text.getLocalBounds().height / 2));
	this->game_over_text.setPosition(sf::Vector2f(960.f, 360.f));
	this->game_over_text.setFillColor(sf::Color(255, 51, 51));

	this->menu_text.setString("Back to Menu");
	this->menu_text.setFont(this->font);
	this->menu_text.setCharacterSize(48);
	this->menu_text.setOrigin(sf::Vector2f(this->menu_text.getLocalBounds().width / 2, this->menu_text.getLocalBounds().height / 2));
	this->menu_text.setPosition(sf::Vector2f(960.f, 720.f));

	this->final_score_text.setFont(this->font);
	this->final_score_text.setCharacterSize(36);
	this->final_score_text.setPosition(sf::Vector2f(960.f, 540.f));

	this->mouseheld = 0;
	this->mouseheldTime = 0.0f;

	this->transition = 0;
	this->transitionCooldown = 0.0f;
}

void Menu::setScore(int score)
{
	this->score = score;
	this->final_score_text.setString("Score: " + std::to_string(this->score));
	this->final_score_text.setOrigin(sf::Vector2f(this->final_score_text.getLocalBounds().width / 2, this->final_score_text.getLocalBounds().height / 2));
	this->state = 7;
}

void Menu::updateMenuState(int state)
{
	this->state = state;
	this->transition = 1;
}

void Menu::updateMenuButton(float deltaTime)
{
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

		//Play
		if (this->play_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
		{
			this->play_text.setFillColor(sf::Color(0, 255, 255));
			this->play_text.setScale(sf::Vector2f(1.1f, 1.1f));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
			{
				this->updateMenuState(1);
			}
		}
		else
		{
			this->play_text.setScale(sf::Vector2f(1.0f, 1.0f));
			this->play_text.setFillColor(sf::Color(255, 255, 255));
		}

		//Score
		if (this->score_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
		{
			this->score_text.setScale(sf::Vector2f(1.1f, 1.1f));
			this->score_text.setFillColor(sf::Color(255, 255, 0));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
			{
				this->updateMenuState(0);
			}
		}
		else
		{
			this->score_text.setScale(sf::Vector2f(1.0f, 1.0f));
			this->score_text.setFillColor(sf::Color(255, 255, 255));
		}

		//Quit
		if (this->quit_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
		{
			this->quit_text.setScale(sf::Vector2f(1.1f, 1.1f));
			this->quit_text.setFillColor(sf::Color(255, 0, 0));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
			{
				this->updateMenuState(5);
			}
		}
		else
		{
			this->quit_text.setScale(sf::Vector2f(1.0f, 1.0f));
			this->quit_text.setFillColor(sf::Color(255, 255, 255));
		}
}

void Menu::updatePause(float deltaTime)
{
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

	//Continue
	if (this->continue_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->continue_text.setScale(sf::Vector2f(1.1f, 1.1f));
		this->continue_text.setFillColor(sf::Color(0, 255, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->updateMenuState(2);
		}
	}
	else
	{
		this->continue_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->continue_text.setFillColor(sf::Color(255, 255, 255));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (!this->escape_bounce)
		{
			this->escape_bounce = 1;
			this->updateMenuState(2);
		}
	}
	else
	{
		this->escape_bounce = 0;
	}

	//Abandon
	if (this->abandon_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->abandon_text.setScale(sf::Vector2f(1.1f, 1.1f));
		this->abandon_text.setFillColor(sf::Color(255, 0, 0));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->updateMenuState(0);
		}
	}
	else
	{
		this->abandon_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->abandon_text.setFillColor(sf::Color(255, 255, 255));
	}
}

void Menu::updateConfig(float deltaTime)
{
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
			this->updateMenuState(0);
		}
	}
	else
	{
		this->back_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->back_text.setFillColor(sf::Color(255, 255, 255));
	}

	//Play
	if (this->go_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->go_text.setScale(sf::Vector2f(1.1f, 1.1f));
		this->go_text.setFillColor(sf::Color(0, 255, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->updateMenuState(2);
		}
	}
	else
	{
		this->go_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->go_text.setFillColor(sf::Color(255, 255, 255));
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
}

void Menu::updateGameOver(float deltaTime)
{
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

	//Menu
	if (this->menu_text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->menu_text.setFillColor(sf::Color(0, 255, 255));
		this->menu_text.setScale(sf::Vector2f(1.1f, 1.1f));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseheld && !transition)
		{
			this->updateMenuState(0);
		}
	}
	else
	{
		this->menu_text.setScale(sf::Vector2f(1.0f, 1.0f));
		this->menu_text.setFillColor(sf::Color(255, 255, 255));
	}
}

void Menu::updateNameInput(sf::Event& event, float deltaTime)
{
	this->event = event;
	if (this->player_name == "" && !(this->event.type == sf::Event::TextEntered))
	{
		this->name_input.setString("Type your name");
		this->type_bounce = 0;
	}
	else
	{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode != 32 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !this->type_bounce)
			{
				this->type_bounce = 1;
				if (event.text.unicode == 8 && player_name.length() > 0)
				{
					player_name.erase(player_name.length() - 1);
				}
				else if (event.text.unicode < 128 && player_name.length() < 15 && event.text.unicode != 8)
				{
					player_name += static_cast<char>(event.text.unicode);
				}
				name_input.setString(player_name);
			}
		}
		else
			this->type_bounce = 0;
	}
}

void Menu::updateDifficulty()
{
	this->difficulty_input = (this->difficulty_input + 1) % 5;
	switch (this->difficulty_input)
	{
	case 0:
		this->difficulty_selected.setString("Easy");
		this->difficulty_description.setString("Recommended for newbie player");
		this->score_multipier_text.setString("Score Multipier x0.5");
		this->difficulty_selected.setFillColor(sf::Color(51, 255, 51));
		break;
	case 1:
		this->difficulty_selected.setString("Medium");
		this->difficulty_description.setString("Recommended for normal player");
		this->score_multipier_text.setString("Score Multipier x1.0");
		this->difficulty_selected.setFillColor(sf::Color(255, 255, 51));
		break;
	case 2:
		this->difficulty_selected.setString("Hard");
		this->difficulty_description.setString("Recommended for experienced player");
		this->score_multipier_text.setString("Score Multipier x1.5");
		this->difficulty_selected.setFillColor(sf::Color(255, 128, 51));
		break;
	case 3:
		this->difficulty_selected.setString("Insane");
		this->difficulty_description.setString("For who think its too easy!");
		this->score_multipier_text.setString("Score Multipier x2.0");
		this->difficulty_selected.setFillColor(sf::Color(255, 51, 51));
		break;
	case 4:
		this->difficulty_selected.setString("Apocalypse");
		this->difficulty_description.setString("You have been warned! Are you sure?");
		this->score_multipier_text.setString("Score Multipier x2.5");
		this->difficulty_selected.setFillColor(sf::Color(128, 51, 255));
	default:
		break;
	}
}

void Menu::checktriggerPause()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (!this->escape_bounce)
		{
			this->escape_bounce = 1;
			this->updateMenuState(6);
		}
	}
	else
	{
		this->escape_bounce = 0;
	}
}

int& Menu::getState()
{
	return this->state;
}

std::string& Menu::getPlayerName()
{
	return this->player_name;
}

int& Menu::getDifficulty()
{
	return this->difficulty_input;
}

void Menu::drawMainMenu()
{
	this->window->clear();

	this->window->draw(this->background_sprite);

	this->window->draw(this->logo_sprite);

	this->window->draw(this->play_text);

	this->window->draw(this->score_text);

	this->window->draw(this->quit_text);

	this->window->draw(this->dev_text);

	this->window->display();
}

void Menu::drawConfig()
{
	this->window->clear();

	this->window->draw(this->config_backgroound);

	this->window->draw(this->back_text);

	this->window->draw(this->go_text);

	this->window->draw(this->difficulty_text);

	this->window->draw(this->difficulty_selected);

	this->window->draw(this->difficulty_description);

	this->window->draw(this->score_multipier_text);

	this->window->draw(this->name);

	this->window->draw(this->name_input);

	this->window->display();
}

void Menu::drawLeaderBoard()
{
	this->window->clear();

	this->window->display();
}

void Menu::drawPause()
{
	this->window->clear();

	this->window->draw(this->background_sprite);

	this->window->draw(this->pause_text);

	this->window->draw(this->continue_text);

	this->window->draw(this->abandon_text);

	this->window->display();
}

void Menu::drawGameOver()
{
	this->window->clear();

	this->window->draw(this->gameover_background);

	this->window->draw(this->game_over_text);

	this->window->draw(this->final_score_text);

	this->window->draw(this->menu_text);

	this->window->display();
}
