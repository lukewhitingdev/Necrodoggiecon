#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
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