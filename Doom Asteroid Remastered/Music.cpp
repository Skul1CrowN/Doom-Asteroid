#include "Music.h"

Music::Music()
{
	this->menu_music.openFromFile("Musics/mainmenu.wav");
	this->game_over_music.openFromFile("Musics/gameover.wav");
}

void Music::PlayMenuMusic()
{
	this->menu_music.play();
}

void Music::StopMenuMusic()
{
	this->menu_music.stop();
}

void Music::PlayGameMusic()
{
	this->game_music.openFromFile(this->filGameName[game_music_index]);
	this->game_music.play();
}

void Music::StopGameMusic()
{
	this->game_music.stop();
}

void Music::PlayGameOverMusic()
{
	this->game_over_music.play();
}

void Music::StopGameOverMusic()
{
	this->game_over_music.stop();
}

void Music::setGameMusicIndex(int index)
{
	this->game_music_index = index;
}

sf::Music& Music::getMenuMusic()
{
	return this->menu_music;
}

sf::Music& Music::getGameMusic()
{
	return this->game_music;
}

sf::Music& Music::getGameOverMusic()
{
	return this->game_over_music;
}
