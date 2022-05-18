/**
Program: 1942
Filename: Audio.cpp
@author: © Reuben Miller
Course: BSc (Hons)/HND Games Programming
Module: CSY1044 Video Games Architecture and Optimisation
Tutor: Dr. Anastasios G. Bakaoukas
Date: 17/05/22
*/
/*
File: Audio.cpp
Disclaimer: The following source code is the sole work of the author unless otherwise stated.
Copyright (C) Reuben Miller. All Rights Reserved.
*/

// HEADER FILES
#include "Audio.h"

/*
	CONSTRUCTOR (TO SET ALL THE INITIAL VARIABLES)
*/
void Audio::init(std::string loc, bool music)
{
	// SET VARIABLES
	isMusic = music;
	location = loc;


	// IF NOT MUSIC THEN LOAD SOUND
	if (!music)
	{
		buffer.loadFromFile(location);
		sound.setBuffer(buffer);
	}
	// OTHER WISE LOAD THE MUSIC
	else
	{
		musicPlayer.openFromFile(location);
	}
}


/*
	PLAYS THE SELECTED MUSIC/SOUND CLIP
*/
void Audio::play()
{
	// IF MUSIC THEN PLAY THE SONG AND MAKE IT LOOP INFINITLY
	if (isMusic)
	{
		musicPlayer.setLoop(true);
		musicPlayer.play();
	}
	// OTHERWISE PLAY THE SOUND EFFECT SELECTED
	else
	{
		sound.play();
	}
}

/*
	STOPS THE SELECTED MUSIC/SOUND FROM PLAYING
*/
void Audio::stop()
{
	// IF MUSIC THEN STOP THE MUSIC
	if (isMusic)
	{
		musicPlayer.stop();
	}
	// OTHERWISE STOP THE SOUND CLIP
	else
	{
		sound.stop();
	}
}

/*
	LOAD THE AUDIO FROM THE SELECTED FILE AND SAVE IT INTO THE LIST OF AUDIO FILES
		# MEANING EACH CLIP WILL BE AN INSTANCE OF THIS CLASS AND SO EACH SOUND CLIP CAN BE
		# MANIPULATED INDEPENDENTLY OF THE OTHER CLIPS
*/
void Audio::loadAudio(std::string loc, bool music)
{
	audio.push_back(new Audio());
	audio.back()->init(loc, music);
}

/*
	SETS THE VOLUME OF THE CLIP WHEN PLAYING (THIS IS USED BY THE PAUSE MENU TO CHANGE THE
	VOLUME OFTHE VARIOUS CLIPS)
*/
void Audio::setVolume(float volume)
{
	this->musicPlayer.setVolume(volume);
	this->sound.setVolume(volume);
}

