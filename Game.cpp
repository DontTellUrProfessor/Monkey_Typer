#include "Game.hpp"
#include "Menu.hpp"

Game::Game(int lvl, int language, int gameFontParameter) {
    this->lvl = lvl;
    this->language = language;
    this->gameFontParameter = gameFontParameter;
    setLanguage(language);
    setLvl(lvl);
    setGameFont(gameFontParameter);

    if (!bananaScoreIcon.loadFromFile("../assets/banana_Points.png")) {
        std::cerr << "Error loading banana Icon\n";
    }
    iconSprite.setTexture(bananaScoreIcon);
    float desiredWidth = 45.f;  // Desired width
    float desiredHeight = 45.f; // Desired height
    float scaleX = desiredWidth / bananaScoreIcon.getSize().x;
    float scaleY = desiredHeight / bananaScoreIcon.getSize().y;
    iconSprite.setScale(scaleX, scaleY);
    iconSprite.setPosition(655, 975);

    typedText.setFont(font);
    typedText.setString("Your text: ");
    typedText.setCharacterSize(45);
    typedText.setFillColor(sf::Color::Yellow);
    typedText.setPosition(0,975);

    pointsText.setFont(font);
    pointsText.setString("Score: " + std::to_string(pointsCounter));
    pointsText.setCharacterSize(45);
    pointsText.setFillColor(sf::Color::Yellow);
    pointsText.setPosition(700, 975);

}

void Game::renderGame() {
    float deltaTime = clock.restart().asSeconds();
    timeSinceLastSpawn += deltaTime;

    // Spawn new words at the right intervals
    if (timeSinceLastSpawn >= spawnInterval && !wordList.empty()) {
        sf::Text text;
        text.setFont(font);
        text.setString(wordList.back());  // Get the last word from wordList
        text.setCharacterSize(34);
        text.setFillColor(sf::Color::White);

        // Generate random position with overlap checking
        bool validPosition = false;
        float xPosition = Menu::window.getSize().x + rand() % 300; // Random x offset from the right
        float yPosition = 0;
        int maxAttempts = 10; // Limit attempts to find a valid position
        int attempt = 0;

        while (!validPosition && attempt < maxAttempts) {
            yPosition = rand() % (Menu::window.getSize().y - 80); // Random vertical position
            validPosition = true;

            // Check overlap with existing words
            for (const auto& word : activeWords) {
                if (std::abs(word.getPosition().y - yPosition) < 50 && // Minimum vertical distance
                    std::abs(word.getPosition().x - xPosition) < 220) { // Minimum horizontal distance
                    validPosition = false;
                    break;
                }
            }
            attempt++;
        }

        // If a valid position was found, spawn the word
        if (validPosition) {
            text.setPosition(xPosition, yPosition);
            activeWords.push_back(text);  // Add the new word to activeWords
            wordList.pop_back();  // Remove the word from wordList so it's not added again
            timeSinceLastSpawn = 0.0f;  // Reset the spawn timer
        }
    }

    // Check if userInput matches any active word
    std::vector<sf::Text> wordsToRemove; // List of words to remove
    for (const auto& word : activeWords) {
        if (word.getString() == userInput) {
            wordsToRemove.push_back(word); // Add the matching word to remove list
        }
    }

    // Remove matching words from activeWords
    for (const auto& word : wordsToRemove) {
        auto it = std::find_if(activeWords.begin(), activeWords.end(),
                               [&word](const sf::Text& activeWord) {
                                   return activeWord.getString() == word.getString();
                               });
        if (it != activeWords.end()) {
            activeWords.erase(it); //Remove matching word
        }
    }

    // Reset userInput if at least one match was found
    if (!wordsToRemove.empty()) {
        userInput = ""; // Clear userInput
        typedText.setString("Your text: "); // Reset typedText to "Your text: "
        pointsCounter++;
        pointsText.setString("Score: " + std::to_string(pointsCounter));
    }

    // Move words to the left
    for (auto& word : activeWords) {
        word.move(-(lvl * 20) * deltaTime, 0); // Move left at speed depending on level
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

    // Draw the active moving words
    for (const auto& word : activeWords) {
        Menu::window.draw(word);
    }

    // Optionally, draw other UI elements
    Menu::window.draw(typedText);
    Menu::window.draw(pointsText);
    Menu::window.draw(iconSprite);

    Menu::window.display();  // Display the updated frame
}


void Game::processGame() {
    sf::Event event;
    while (Menu::window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Menu::window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            // Ignore Tab, Enter, and Space
            if (event.text.unicode == '\t' || event.text.unicode == '\n' || event.text.unicode == ' ') {
                continue; // Skip these characters
            }

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
            Game::wordList.clear();
            while (std::getline(file, line)) {

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