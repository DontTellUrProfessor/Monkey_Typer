#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.hpp"

class Menu {
public:
    static sf::RenderWindow window;
    Menu(int width, int height, int lvl, int language, int gameFontParameter);
    void run();

private:
    sf::RectangleShape buttonStart, buttonSettings, button3;
    sf::Font font, gameplayFont;
    sf::Text text1, text2, text3, mainText, mainText1, lvlText, langText, fontText, testFontText;
    int lvl, gameFontParameter, language;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Settings* settings = nullptr;
    bool openSettings = false;
    int isSettings = 1;

    void setupButtonText(sf::Text& text, const std::string& str, const sf::RectangleShape& button);
    void setupSettingsText(sf::Text& text, const std::string& str);
    void processEvents();
    void handleMouseClick(int x, int y);
    void render();
};
