/**
Program: 1942
Filename: Audio.h
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File: Audio.h
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

#pragma once
// HEADER FILES
#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
public:
	// METHODS
	Audio();
	Audio(std::string loc, bool music);
	void setVolume(float volume);
	void loadAudio(std::string loc, bool music);
	void play();
	void stop();

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
