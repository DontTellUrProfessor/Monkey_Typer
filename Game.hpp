#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.hpp"


class Game {
public:
    Game(int lvl, int language, int gameFontParameter);
    void renderGame();
    void processGame();


private:
    int lvl, language, gameFontParameter;
    sf::Font font;
    sf::Text typedText, targetText;

    void setLanguage(int language);
    void setLvl(int lvl);
    void setGameFont(int gameFontParameter);


};


