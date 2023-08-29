#pragma once

#include <fmod.h>
#include <string>
#include <unordered_map>

class SoundManager
{
public:
    static void init();
    static void terminate();
    static void play(std::string const&);
    static void update();
protected:
    static FMOD_SYSTEM* system;
    static FMOD_CHANNEL* channel;
    static std::unordered_map<std::string, FMOD_SOUND*> entires;
};