#pragma once
// HEADER FILES
#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
public:
	// METHODS
	void init(std::string loc, bool music);
	void play();
	void stop();
	void setVolume(float volume);
	void loadAudio(std::string loc, bool music);

	// VARIABLES
	std::vector<Audio*> audio;

private:
	//		VARIABLES
	// SOUND EFFECTS
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string location;

	// BACKGROUND MUSIC
	sf::Music musicPlayer;
	bool isMusic = false;
};
