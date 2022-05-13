/*****************************************************************//**
 * \file   CAudio.h
 * \brief  Helper class that encapsulates audio parameters for the audio system. Used to de-couple FMOD from the audio system.
 * 
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Dependencies/FMOD/api/core/inc/fmod.hpp"
class CAudio
{
public:
	CAudio(std::string path, FMOD::Sound* sound, FMOD::ChannelGroup* group) : sound(sound), group(group), channel(nullptr) {};
	CAudio(std::string path, FMOD::Sound* sound, FMOD::ChannelGroup* group, FMOD::Channel* chanel) : path(path), sound(sound), group(group), channel(chanel) {};
	std::string path;
	FMOD::Sound* sound;
	FMOD::ChannelGroup* group;
	FMOD::Channel* channel;
};