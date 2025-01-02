#include "Settings.hpp"
#include "Menu.hpp"

Settings::Settings(int lvl, int language, int gameFontParameter) {
    this->lvl = lvl;
    this->language = language;
    this->gameFontParameter = gameFontParameter;

    if (!settingsBackgroundTexture.loadFromFile("../assets/settingsBackground.jpg")) {
        std::cerr << "Failed to load background image. "
                  << "Ensure 'settingsBackground.jpg' is in the correct directory.\n";
        exit(EXIT_FAILURE);
    }
    settingsBackgroundSprite.setTexture(settingsBackgroundTexture);

    if (!mainFont.loadFromFile("../assets/main.ttf")) {
        std::cerr << "Error loading font\n";
    }

    setLanguage(language);
    setLvl(lvl);
    setGameFont(gameFontParameter);

    title.setFont(mainFont);
    title.setString("Settings");
    title.setCharacterSize(90);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(350 ,50);

    title1.setFont(mainFont);
    title1.setString("Settings");
    title1.setCharacterSize(90);
    title1.setFillColor(sf::Color::Black);
    title1.setPosition(355, 55);

    langText.setPosition(340, 250);

    lvlText.setPosition(330, 370);

    fontText.setFont(mainFont);
    fontText.setString("Font:");
    fontText.setCharacterSize(50);
    fontText.setFillColor(sf::Color::Yellow);
    fontText.setOutlineThickness(7);
    fontText.setOutlineColor(sf::Color::Black);

    fontText.setPosition(80, 670);

    textBackground.setSize(sf::Vector2f(550, 100));
    textBackground.setPosition(220, 645);
    textBackground.setFillColor(sf::Color::Black);

    showFontText.setFont(showFont);
    showFontText.setString("sampletext");
    showFontText.setCharacterSize(70);
    showFontText.setFillColor(sf::Color::White);
    showFontText.setPosition(230, 650);

    setupButton(langButton);
    setupButton(lvlButton);
    setupButton(fontButton);

    langButton.setPosition(650, 250);
    lvlButton.setPosition(720, 370);
    fontButton.setPosition(830, 670);

    buttonSave.setSize(sf::Vector2f(300, 100));
    buttonSave.setPosition(362, 800);
    buttonSave.setFillColor(sf::Color::Yellow);
    buttonSave.setOutlineThickness(5);
    buttonSave.setOutlineColor(sf::Color::Blue);

    saveText.setFont(mainFont);
    saveText.setString("Save");
    saveText.setCharacterSize(34);
    saveText.setFillColor(sf::Color::Black);

    sf::FloatRect buttonBounds = buttonSave.getGlobalBounds();
    sf::FloatRect textBounds = saveText.getGlobalBounds();

    saveText.setPosition(
            buttonBounds.left + (buttonBounds.width / 2.f) - (textBounds.width / 2.f),
            buttonBounds.top + (buttonBounds.height / 2.f) - (textBounds.height / 2.f) - 5.f
    );



}

void Settings::setGameFont(int gameFontParameter) {
    switch (gameFontParameter) {
        case 1:
            if (!showFont.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 2:
            if (!showFont.loadFromFile("../assets/RedGlass.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 3:
            if (!showFont.loadFromFile("../assets/StarWars.otf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 4:
            if (!showFont.loadFromFile("../assets/Azonix.otf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        default:
            if (!showFont.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
    }
}

void Settings::setLvl(int lvl) {
    switch (lvl) {
        case 1:
            setupText(lvlText, "Difficulty: Easy");
            break;
        case 2:
            setupText(lvlText, "Difficulty: Medium");
            break;
        case 3:
            setupText(lvlText, "Difficulty: Hard");
            break;
        case 4:
            setupText(lvlText, "Difficulty: Pro");
            break;
    }
}

void Settings::setLanguage(int language) {
    switch (language) {
        case 1:
            setupText(langText, "Language: ENG");

            break;
        case 2:
            setupText(langText, "Language: PL");
            break;
    }
}

void Settings::renderSettings() {
    Menu::window.clear();

    Menu::window.draw(settingsBackgroundSprite);
    Menu::window.draw(title1);
    Menu::window.draw(title);
    Menu::window.draw(langText);
    Menu::window.draw(lvlText);
    Menu::window.draw(fontText);
    Menu::window.draw(textBackground);
    Menu::window.draw(showFontText);
    Menu::window.draw(langButton);
    Menu::window.draw(lvlButton);
    Menu::window.draw(fontButton);
    Menu::window.draw(buttonSave);
    Menu::window.draw(saveText);

    Menu::window.display();

    if(!isSettings) {
        Menu::openSettingsFlag = false;
        Menu::languageFlag = language;
        Menu::fontFlag = gameFontParameter;
        Menu::lvlFlag = lvl;
    }
}

void Settings::setupText(sf::Text& text, std::string str){
    text.setFont(mainFont);
    text.setString(str);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Yellow);
    text.setOutlineThickness(7);
    text.setOutlineColor(sf::Color::Black);
}

void Settings::setupButton(sf::CircleShape& button) {
    button.setRadius(25);
    button.setPointCount(100);
    button.setFillColor(sf::Color::Yellow);
    button.setOutlineThickness(5);
    button.setOutlineColor(sf::Color::Blue);
}

void Settings::handleMouseClick(int x, int y) {
    sf::Vector2f mousePos(x, y);
    if (langButton.getGlobalBounds().contains(mousePos)){
        language++;
        if (language > 2) {
            language = 1;
        }
        setLanguage(language);
    } else if (lvlButton.getGlobalBounds().contains(mousePos)) {
        lvl++;
        if (lvl > 4) {
            lvl = 1;
        }
        setLvl(lvl);
    } else if (fontButton.getGlobalBounds().contains(mousePos)){
        gameFontParameter++;
        if (gameFontParameter > 4) {
            gameFontParameter = 1;
        }
        setGameFont(gameFontParameter);
    } else if (buttonSave.getGlobalBounds().contains(mousePos)){
        closeSettings();
    }
}

void Settings::processEvents() {
    sf::Event event;
    while(Menu::window.pollEvent(event)){
        if (event.type == sf::Event::Closed) {
            Menu::window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}



void Settings::closeSettings() {
    isSettings = false;
}
