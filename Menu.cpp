#include "Menu.hpp"
#include "Settings.hpp"
#include "Game.hpp"

sf::RenderWindow Menu::window;
bool Menu::openSettingsFlag = false;
int Menu::lvlFlag = 1;
int Menu::fontFlag = 1;
int Menu::languageFlag = 1;

Menu::Menu(int width, int height, int lvl, int language, int gameFontParameter) {
    window.create(sf::VideoMode(width, height), "MONKEY TYPER", sf::Style::Titlebar | sf::Style::Close);
    this->lvl = lvl;
    this->gameFontParameter = gameFontParameter;
    this->language = language;

    if (!backgroundTexture.loadFromFile("../assets/background.jpg")) {
        std::cerr << "Failed to load background image. "
                  << "Ensure 'background.jpg' is in the correct directory.\n";
        exit(EXIT_FAILURE);
    }
    backgroundSprite.setTexture(backgroundTexture);

    buttonStart.setSize(sf::Vector2f(300, 100));
    buttonStart.setPosition(362, 650);
    buttonStart.setFillColor(sf::Color::Yellow);
    buttonStart.setOutlineThickness(5);
    buttonStart.setOutlineColor(sf::Color::Blue);

    buttonSettings.setSize(sf::Vector2f(300, 100));
    buttonSettings.setPosition(662, 800);
    buttonSettings.setFillColor(sf::Color::Yellow);
    buttonSettings.setOutlineThickness(5);
    buttonSettings.setOutlineColor(sf::Color::Blue);

    button3.setSize(sf::Vector2f(300, 100));
    button3.setPosition(62, 800);
    button3.setFillColor(sf::Color::Yellow);
    button3.setOutlineThickness(5);
    button3.setOutlineColor(sf::Color::Blue);

    if (!font.loadFromFile("../assets/main.ttf")) {
        std::cerr << "Error loading font\n";
    }


    setGameFont(gameFontParameter);
    setLvl(lvl);
    setLanguage(language);

    setupButtonText(text1, "Play", buttonStart);
    setupButtonText(text2, "Settings", buttonSettings);
    setupButtonText(text3, "Exit", button3);
    testFontText.setFont(gameplayFont);
    testFontText.setString("AaBbCc");
    testFontText.setCharacterSize(34);
    testFontText.setFillColor(sf::Color::Yellow);
    testFontText.setOutlineThickness(5);
    testFontText.setOutlineColor(sf::Color::Black);

    mainText.setFont(font);
    mainText.setString("Monkey Typer");
    mainText.setCharacterSize(90);
    mainText.setFillColor(sf::Color::Yellow);
    mainText.setPosition(220, 50);

    mainText1.setFont(font);
    mainText1.setString("Monkey Typer");
    mainText1.setCharacterSize(90);
    mainText1.setFillColor(sf::Color::Black);
    mainText1.setPosition(225, 55);

    setupSettingsText(fontText, "Font:");

    lvlText.setPosition(100, 200);
    langText.setPosition(100, 250);
    fontText.setPosition(100, 300);
    testFontText.setPosition(200, 300);


}

void Menu::setLanguage(int language) {
    switch (language) {
        case 1:
            setupSettingsText(langText, "Language: ENG");
            break;
        case 2:
            setupSettingsText(langText, "Language: PL");
            break;
    }
}

void Menu::setLvl(int lvl) {
    switch (lvl) {
        case 1:
            setupSettingsText(lvlText, "Difficulty: Easy");
            break;
        case 2:
            setupSettingsText(lvlText, "Difficulty: Medium");
            break;
        case 3:
            setupSettingsText(lvlText, "Difficulty: Hard");
            break;
        case 4:
            setupSettingsText(lvlText, "Difficulty: Pro");
            break;
    }
}

void Menu::setGameFont(int gameFontParameter) {
    switch (gameFontParameter) {
        case 1:
            if (!gameplayFont.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 2:
            if (!gameplayFont.loadFromFile("../assets/RedGlass.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 3:
            if (!gameplayFont.loadFromFile("../assets/Azonix.otf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        default:
            if (!gameplayFont.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
    }
}

void Menu::run() {
    while (window.isOpen()) {
        setGameFont(gameFontParameter);
        setLvl(lvl);
        setLanguage(language);
        if (openSettings && settings) {
            settings->renderSettings();
            settings->processEvents();
            setSettings();
        }else if(openGame && game){
            game->renderGame();
            game->processGame();

        } else {
            this -> processEvents();
            this -> render();
        }
    }
}



void Menu::setupButtonText(sf::Text& text, const std::string& str, const sf::RectangleShape& button) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(34);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect buttonBounds = button.getGlobalBounds();
    sf::FloatRect textBounds = text.getGlobalBounds();

    text.setPosition(
            buttonBounds.left + (buttonBounds.width / 2.f) - (textBounds.width / 2.f),
            buttonBounds.top + (buttonBounds.height / 2.f) - (textBounds.height / 2.f) - 5.f
    );
}

void Menu::setupSettingsText(sf::Text& text, const std::string& str) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(34);
    text.setFillColor(sf::Color::Yellow);
    text.setOutlineThickness(5);
    text.setOutlineColor(sf::Color::Black);
}

void Menu::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleMouseClick(event.mouseButton.x, event.mouseButton.y);
        }
    }
}

void Menu::handleMouseClick(int x, int y) {
    sf::Vector2f mousePos(x, y);

    if (buttonStart.getGlobalBounds().contains(mousePos)) {
        openGame = true;
        game = new Game(lvl, language, gameFontParameter);
    } else if (buttonSettings.getGlobalBounds().contains(mousePos)) {
        openSettings = true;
        openSettingsFlag = true;
        settings = new Settings(lvl, language, gameFontParameter); // Create Settings instance
    } else if (button3.getGlobalBounds().contains(mousePos)) {
        std::cout << "Exit button clicked\n";
        window.close();
    }
}


void Menu::render() {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(buttonStart);
        window.draw(buttonSettings);
        window.draw(button3);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(mainText1);
        window.draw(mainText);
        window.draw(lvlText);
        window.draw(langText);
        window.draw(fontText);
        window.draw(testFontText);
        window.display();
}

void Menu::setSettings() {
    this->lvl = lvlFlag;
    this->language = languageFlag;
    this->gameFontParameter = fontFlag;
    this->openSettings = openSettingsFlag;
}

