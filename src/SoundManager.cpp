#include "SoundManager.h"

#include <iostream>

FMOD_SYSTEM* SoundManager::system = nullptr;
FMOD_CHANNEL* SoundManager::channel = 0;
std::unordered_map<std::string, FMOD_SOUND*> SoundManager::entires;

void SoundManager::init()
{
    FMOD_RESULT result;
    result = FMOD_System_Create(&system, FMOD_VERSION);
    void* extraDirverData = 0;
    if (result != FMOD_OK)
    {
        std::cout << "Failed to create fmod system." << std::endl;
    }
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, extraDirverData);
    if (result != FMOD_OK)
    {
        std::cout << "Failed to create fmod system." << std::endl;
    }
}

void SoundManager::terminate()
{
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

void SoundManager::play(std::string const& s)
{
    FMOD_SOUND* sound;
    if (entires.count(s) == 0)
    {
        FMOD_RESULT result;
        result = FMOD_System_CreateSound(system, s.c_str(), FMOD_DEFAULT, 0, &sound);
        if (result != FMOD_OK)
        {
            std::cout << "Failed to load sound " << s << std::endl;
        }
        FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    } else
    {
        sound = entires[s];
    }

    FMOD_System_PlaySound(system, sound, 0, false, &channel);
}

void SoundManager::update()
{
    FMOD_System_Update(system);
}
