#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>


class Game {
public:
    Game(int lvl, int language, int gameFontParameter);
    void renderGame();
    void processGame();
    void runGame();


private:
    int lvl, language, gameFontParameter;
    sf::Font font;
    sf::Text typedText, targetText;
    std::string userInput;
    std::vector<std::string> wordList;
    sf::Clock clock;
    std::vector<sf::Text> activeWords;
    float spawnInterval = 0.25f;
    float timeSinceLastSpawn = 0.0f;

    void setLanguage(int language);
    void setLvl(int lvl);
    void setGameFont(int gameFontParameter);


};


