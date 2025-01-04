#include "Game.hpp"

Game::Game(int lvl, int language, int gameFontParameter) {
    this->lvl = lvl;
    this->language = language;
    this->gameFontParameter = gameFontParameter;
    setLanguage(language);
    setLvl(lvl);
    setGameFont(gameFontParameter);


}

void Game::renderGame() {
    Menu::window.clear();

    Menu::window.display();
}

void Game::processGame() {
    sf::Event event;
    while (Menu::window.pollEvent(event)) {
        // Handle window close event
        if (event.type == sf::Event::Closed) {
            Menu::window.close();
        }

        // Handle key press event
        if (event.type == sf::Event::KeyPressed) {
            // Print the key that was pressed
            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                std::cout << "Key Pressed: " << static_cast<char>('A' + event.key.code - sf::Keyboard::A) << "\n";
            } else if (event.key.code == sf::Keyboard::Space) {
                std::cout << "Space bar pressed!\n";
            } else {
                std::cout << "Other key pressed: " << event.key.code << "\n";
            }
        }
    }

}



void Game::setLanguage(int language) {
    switch (language) {
        case 1:

            break;
        case 2:

            break;
    }
}

void Game::setLvl(int lvl) {
    switch (lvl) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
    }
}

void Game::setGameFont(int gameFontParameter) {
    switch (gameFontParameter) {
        case 1:
            if (!font.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 2:
            if (!font.loadFromFile("../assets/RedGlass.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 3:
            if (!font.loadFromFile("../assets/StarWars.otf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        case 4:
            if (!font.loadFromFile("../assets/Azonix.otf")) {
                std::cerr << "Error loading font\n";
            }
            break;
        default:
            if (!font.loadFromFile("../assets/main.ttf")) {
                std::cerr << "Error loading font\n";
            }
            break;
    }
}
