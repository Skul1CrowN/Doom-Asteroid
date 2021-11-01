#include "Game.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Doom Asteroid", sf::Style::Fullscreen | sf::Style::Close);
	sf::Image icon;
	icon.loadFromFile("./Images/Asteroid.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Game game(&window);
	Menu menu(&window);
	Scoreboard score(&window);

	float deltaTime = 0.0f;
	sf::Clock clock;


	bool focus = 1;
	bool menu_trans = 1;
	bool game_init = 1;

	int action;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				focus = 1;
				break;
			case sf::Event::LostFocus:
				focus = 0;
				break;
			}
		}
		if (focus)
		{
			action = menu.getState();

			switch (action)
			{
			case 0://Menu
				game.stopMusic();
				menu.stopGameOverMusic();
				menu.updateMusic();
				score.resetReturntoMenu();
				menu.updateMenuButton(deltaTime);
				menu.drawMainMenu();
				game.Reset();
				break;
			case 1://Config
				menu_trans = 1;
				game_init = 1;
				menu.updateConfig(deltaTime);
				menu.updateNameInput(ev, deltaTime);
				menu.updateMusic();
				menu.drawConfig();
				break;
			case 2:// Game
				menu.stopMusic();
				game.updateMusic();
				if (menu_trans)
				{
					game.menuCoolDown();
					menu_trans = 0;
				}
				if (game_init)
				{
					game.setPlayerName(menu.getPlayerName());
					game.setDifficulty(menu.getDifficulty());
					game.Init();
					game_init = 0;
				}
				game.Update(deltaTime);
				game.Render();
				menu.checktriggerPause();
				if (!game.getAlive())
					menu.setScore(game.getScore());
				break;
			case 3://Leaderboard
				score.transitionDelay();
				score.updateButton(deltaTime);
				score.updateScore();
				score.render();
				menu.updateMusic();
				menu.backToMenu(score.returnToMenu());
				break;
			case 4: // Tutorial
				menu.updateTutorial(deltaTime);
				menu.drawTutorial();
				menu.updateMusic();
				break;
			case 5:// Quit
				window.close();
				break;
			case 6: // Pause
				menu_trans = 1;
				menu.updatePause(deltaTime);
				menu.drawPause();
				break;
			case 7: // Game Over
				game.stopMusic();
				menu.updateGameOverMusic();
				menu.updateGameOver(deltaTime);
				menu.drawGameOver();
			default:
				break;
			}
		}
	}
	return 0;
}