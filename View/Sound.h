#ifndef VIEW_SOUND_H
#define VIEW_SOUND_H

#include <unordered_map>
#include <map>
#include <SFML\Audio.hpp>
#include "../Model/Tank.h"

typedef std::unordered_map<std::string, sf::Sound> SoundMap;

namespace views {
    class Sound {
        private:
            std::map<int, sf::SoundBuffer> buffer;

        public:
            SoundMap Sounds;
        
        public:
            Sound();
            ~Sound();
        
        public:
            void updateSound(std::list<TankPtr>& tanks);
            void stopAll();
    };
}

#endif