#include "Game.hpp"
#include "Menu.hpp"

Game::Game(int lvl, int language, int gameFontParameter) {
    this->lvl = lvl;
    this->language = language;
    this->gameFontParameter = gameFontParameter;
    setLanguage(language);
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
        float xPosition = Menu::window.getSize().x + rand() % 300; // Random x offset
        float yPosition = 0;
        int maxAttempts = 10; // Limit attempts
        int attempt = 0;

        while (!validPosition && attempt < maxAttempts) {
            yPosition = rand() % (Menu::window.getSize().y - 80); // Random vertical position
            validPosition = true;

            // Check overlap
            for (const auto& word : activeWords) {
                if (std::abs(word.getPosition().y - yPosition) < 50 &&
                    std::abs(word.getPosition().x - xPosition) < 220) {
                    validPosition = false;
                    break;
                }
            }
            attempt++;
        }

        if (validPosition) {
            text.setPosition(xPosition, yPosition);
            activeWords.push_back(text);
            wordList.pop_back();
            timeSinceLastSpawn = 0.0f;
        }
    }

    // Move words to the left
    for (auto& word : activeWords) {
        word.move(-(lvl * 20) * deltaTime, 0); // Move left
    }

    // Clear the window
    Menu::window.clear();

    // Draw the active words with highlighting
    for (const auto& word : activeWords) {
        std::string wordStr = word.getString();
        sf::Text matchingPart, remainingPart;

        // Check for match
        if (wordStr.find(userInput) == 0 && !userInput.empty()) {
            // Create the matching part
            matchingPart.setFont(font);
            matchingPart.setString(userInput);
            matchingPart.setCharacterSize(34);
            matchingPart.setFillColor(sf::Color::Red);
            matchingPart.setPosition(word.getPosition());

            // Create the remaining part
            remainingPart.setFont(font);
            remainingPart.setString(wordStr.substr(userInput.size()));
            remainingPart.setCharacterSize(34);
            remainingPart.setFillColor(sf::Color::White);
            remainingPart.setPosition(
                    matchingPart.getPosition().x + matchingPart.getGlobalBounds().width,
                    word.getPosition().y
            );

            // Draw both parts
            Menu::window.draw(matchingPart);
            Menu::window.draw(remainingPart);
        } else {
            // Draw the word as-is
            Menu::window.draw(word);
        }
    }

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

    // Optionally, draw other UI elements
    Menu::window.draw(typedText);
    Menu::window.draw(pointsText);
    Menu::window.draw(iconSprite);

    Menu::window.display(); // Display everything
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


void Game::loadWordList(const std::string& filePath){
    std::ifstream file(filePath);
    std::random_device rd;
    std::mt19937 generator(rd());

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file: " << filePath << "\n";
        return;
    }

    wordList.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            wordList.push_back(word);
        }
    }

    // Shuffle the words
    std::shuffle(wordList.begin(), wordList.end(), generator);

    // Display the shuffled words (optional, can be removed in production)
    for (const auto& shuffledWord : wordList) {
        std::cout << shuffledWord << " ";
    }
    std::cout << "\n";

    file.close();
}

void Game::setLanguage(int language) {
    switch (language) {
        case 1:
            loadWordList("../assets/ENG_Wordlist.txt");
            break;
        case 2:
            loadWordList("../assets/PL_Wordlist.txt");
            break;
        default:
            std::cerr << "Error: Unsupported language selection\n";
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