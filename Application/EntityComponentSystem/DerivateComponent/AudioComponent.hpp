#pragma once

#include <iostream>
#include "ISound.hpp"
#include "Component.hpp"

class AudioComponent : public Components
{
public:
    enum type_audio {SOUND, MUSIC};
    type_audio m_type;
    Eligos::IAudio *audio;
public:
    AudioComponent() = default;
    AudioComponent(int id) : Components(id, getCompId()){};
    virtual ~AudioComponent() = default;
    static Components *Create(const int &id) { return new AudioComponent(id); };
    virtual void modify(const std::string str) {
        if (str.find("Sound") != std::string::npos)
            audio = new Eligos::SfmlSound();
        else
        {
            audio = new Eligos::SfmlMusic();
        }
        std::cout << "--------------------------------------------------" << std::endl;
        audio->load(str);
        audio->Play();
    }
    virtual void dump() {}
    virtual Components *clone() { return new AudioComponent(*this); }
    int getEntityId() const { return m_entityId; }
    static int getCompId() { return 6; };
};