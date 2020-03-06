#pragma once

#include <SFML/Audio.hpp>

namespace Eligos
{
    class IAudio
    {
    public:
        virtual ~IAudio() = default;
        virtual void load(const std::string) = 0;
        virtual void Play() = 0;
        virtual void Stop() = 0;
    };

    class SfmlSound : public IAudio
    {
    private:
        sf::SoundBuffer m_buffer;
        sf::Sound m_Sound;
    public:
        SfmlSound() = default;
        virtual void load(const std::string str)
        {
            m_buffer.loadFromFile(str);
            m_Sound.setBuffer(m_buffer);
            m_Sound.setVolume(75);
        }
        virtual void Play()
        {
            m_Sound.play();
        }
        virtual void Stop()
        {
            m_Sound.stop();
        }
        virtual ~SfmlSound() { Stop(); };
    };

    class SfmlMusic : public IAudio
    {
    private:
        sf::Music m_music;
    public:
        SfmlMusic() {}
        virtual void load(const std::string str)
        {
            m_music.openFromFile(str);
        }
        virtual void Play()
        {
            m_music.play();
        }
        virtual void Stop()
        {
            m_music.stop();
        }
        virtual ~SfmlMusic() { Stop(); };
    };
} // namespace Eligos