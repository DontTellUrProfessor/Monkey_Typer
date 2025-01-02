#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Settings {
public:
    Settings(int lvl, int language, int gameFontParameter);
    void renderSettings();
    void processEvents();
    void handleMouseClick(int x, int y);


private:
    int lvl, language, gameFontParameter;
    sf::Texture settingsBackgroundTexture;
    sf::Sprite settingsBackgroundSprite;
    sf::Text title, title1, langText, lvlText, fontText, showFontText, saveText;
    sf::Font mainFont, showFont;
    sf::RectangleShape buttonSave, textBackground;
    sf::CircleShape langButton, lvlButton, fontButton;
    bool isSettings = true;

    void setupText(sf::Text& text, std::string str);
    void setupButton(sf::CircleShape& button);

    void setLanguage(int language);
    void setLvl(int lvl);
    void setGameFont(int gameFontParameter);
    void closeSettings();

};
