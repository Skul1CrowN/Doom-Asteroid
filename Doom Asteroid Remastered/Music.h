#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Music
{
private:
	
	sf::Music game_music;
	sf::Music menu_music;
	sf::Music game_over_music;

	std::string filGameName[5] = {
		"Musics/music1.wav",
		"Musics/music2.wav",
		"Musics/music3.wav",
		"Musics/music4.wav",
		"Musics/music5.wav"
	};

	int game_music_index;
public:

	Music();

	void PlayMenuMusic();

	void StopMenuMusic();

	void PlayGameMusic();

	void StopGameMusic();

	void PlayGameOverMusic();

	void StopGameOverMusic();

	void setGameMusicIndex(int index);

	sf::Music& getMenuMusic();
	sf::Music& getGameMusic();
	sf::Music& getGameOverMusic();
};

