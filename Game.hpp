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


private:

    int lvl, language, gameFontParameter;
    int pointsCounter = 0;
    sf::Font font, scoreFont;
    sf::Text typedText, targetText, pointsText;
    sf::Texture bananaScoreIcon;
    sf::Sprite iconSprite;
    std::string userInput;
    std::vector<std::string> wordList;
    sf::Clock clock;
    std::vector<sf::Text> activeWords;
    float spawnInterval = 0.25f;
    float timeSinceLastSpawn = 0.0f;
    void loadWordList(const std::string& filePath);
    void setLanguage(int language);
    void setGameFont(int gameFontParameter);


};


