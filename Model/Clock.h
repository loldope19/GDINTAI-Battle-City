#ifndef MODEL_CLOCK_H
#define MODEL_CLOCK_H

namespace models {
    class Timer {
        private:
            sf::Font& font;
            sf::Text sText;
            sf::Clock sTime;

            int nActualFPS, nFPSCount;
            bool bClockOn;

        public:
            Timer(sf::Font& font);
            ~Timer();

        public:
            void toggleClock();
            void restart();
            void stopClock();
            void draw(sf::RenderWindow& rwWindow);

    };

}

#endif