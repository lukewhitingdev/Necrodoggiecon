#pragma once
#include "Dependencies/FMOD/api/core/inc/fmod.hpp"
class CAudio
{
public:
	CAudio(FMOD::Sound* sound, FMOD::ChannelGroup* group) : sound(sound), group(group), channel(nullptr) {};
	CAudio(FMOD::Sound* sound, FMOD::ChannelGroup* group, FMOD::Channel* chanel) : sound(sound), group(group), channel(chanel) {};
	FMOD::Sound* sound;
	FMOD::ChannelGroup* group;
	FMOD::Channel* channel;
};