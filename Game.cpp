#include "Game.hpp"
#include "Menu.hpp"

Game::Game(int lvl, int language, int gameFontParameter) {
    this->lvl = lvl;
    this->language = language;
    this->gameFontParameter = gameFontParameter;
    setLanguage(language);
    setLvl(lvl);
    setGameFont(gameFontParameter);

    typedText.setFont(font);
    typedText.setString("Your text: ");
    typedText.setCharacterSize(30);
    typedText.setFillColor(sf::Color::White);
    typedText.setPosition(0,990);

}

void Game::renderGame() {
    float deltaTime = clock.restart().asSeconds();
    timeSinceLastSpawn += deltaTime;

    // Spawn new words at the right intervals
    if (timeSinceLastSpawn >= spawnInterval && !wordList.empty()) {
        sf::Text text;
        text.setFont(font);
        text.setString(wordList.back());  // Get the last word from wordList
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(Menu::window.getSize().x, rand() % (Menu::window.getSize().y - 50)); // Random vertical position

        activeWords.push_back(text);  // Add the new word to activeWords
        wordList.pop_back();  // Remove the word from wordList so it's not added again
        timeSinceLastSpawn = 0.0f;  // Reset the spawn timer
    }

    // Move words to the left
    for (auto& word : activeWords) {
        word.move(-100 * deltaTime, 0); // Move left at 100 pixels per second
    }

    // Remove words that are off-screen
    activeWords.erase(
            std::remove_if(activeWords.begin(), activeWords.end(),
                           [](const sf::Text& word) {
                               return word.getPosition().x + word.getGlobalBounds().width < 0;
                           }),
            activeWords.end());

    // Clear the window and draw everything
    Menu::window.clear();

    // Optionally, draw typedText or other UI elements here
    Menu::window.draw(typedText);  // Assuming typedText is some pre-defined text to show

    // Draw the active moving words
    for (const auto& word : activeWords) {
        Menu::window.draw(word);
    }

    Menu::window.display();  // Display the updated frame
}

void Game::processGame() {
    sf::Event event;
    while (Menu::window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Menu::window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') { // Backspace
                if (!userInput.empty()) {
                    userInput.pop_back();
                }
            } else if (event.text.unicode < 128) { // Printable ASCII characters
                userInput += static_cast<char>(event.text.unicode);
            }

            typedText.setString("Your text: " + userInput); // Update the text object
        }

    }

}

void Game::runGame(){



}



void Game::setLanguage(int language) {
    switch (language) {
        case 1:

            break;
        case 2:
            std::string line;
            std::ifstream file("../assets/PL_Wordlist.txt");
            std::random_device rd;
            std::mt19937 generator(rd());
            if (!file.is_open()) {
                std::cerr << "Error: Could not open the wordlist file \n";
                return;
            }
            while (std::getline(file, line)) {
                Game::wordList.clear();

                // Split the line into words
                std::istringstream iss(line);
                std::string word;
                while (iss >> word) {
                    wordList.push_back(word);
                }

                // Shuffle the words
                std::shuffle(wordList.begin(), wordList.end(), generator);

                // Display the shuffled words
                for (const auto& shuffledWord : wordList) {
                    std::cout << shuffledWord << " ";
                }
                std::cout << "\n";
            }

            file.close();
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
