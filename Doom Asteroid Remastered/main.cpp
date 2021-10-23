#include "Game.h"

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Doom Asteroid", sf::Style::Fullscreen | sf::Style::Close);
	Game game(&window);
	float deltaTime = 0.0f;
	sf::Clock clock;

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
			}
		}
		game.Update(deltaTime);

		game.Render();
	}
	return 0;
}