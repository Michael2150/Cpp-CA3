#include <iostream>
#include <memory>
#include <iomanip>
#include "GameEngine.h"
#include "../game/Game.h"

GameEngine* GameEngine::instance = nullptr;
shared_ptr<TileSet> GameEngine::sourceTileSet = nullptr;

void GameEngine::Initialize(int width, int height, const std::string &title) {
    auto timer = sf::Clock();

    this->title = title;
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), this->title, sf::Style::Default);
    this->window->setFramerateLimit(60);

    GameEngine::sourceTileSet = make_shared<TileSet>("resources/environment/tileset.png", sf::Vector2u(8, 8), sf::Vector2u(8, 14));

    // Create the scenes here:
    CreateScene<MenuScene>("resources/tiled/main_menu.json"); // Scene [0]
    CreateScene<Level1>("resources/tiled/level_1_map.json"); // Scene [1]
    CreateScene<Level2>("resources/tiled/level_2_map.json"); // Scene [2]
    CreateScene<EndScene>("resources/tiled/end_screen.json"); // Scene [3]

    cout << "Game engine initialized in " << std::fixed << std::setprecision(6) << timer.restart().asSeconds() << " seconds." << endl;
}

void GameEngine::Start() {
    std::cout << "Starting game engine..." << std::endl;

    auto timer = sf::Clock();

    SetActiveScene(0); // Menu scene

    auto delta_time = 0.f;
    while (window->isOpen()) {
        delta_time = timer.restart().asSeconds();

        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }

                if (event.key.code == sf::Keyboard::Num1) {
                    SetActiveScene(0);
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    SetActiveScene(1);
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    SetActiveScene(2);
                }
                if (event.key.code == sf::Keyboard::Num4) {
                    SetActiveScene(3);
                }

                // if plus key is pressed, increase the gravity
                if (event.key.code == sf::Keyboard::Equal) {
                    current_scene->getWorld()->SetGravity({0.0f, current_scene->getWorld()->GetGravity().y + 100.0f});
                }
                // if minus key is pressed, decrease the gravity
                if (event.key.code == sf::Keyboard::Dash) {
                    current_scene->getWorld()->SetGravity({0.0f, current_scene->getWorld()->GetGravity().y - 100.0f});
                }
            }
        }

        current_scene->Update(delta_time);

        window->clear(sf::Color::Black);

        current_scene->Render(window);

        window->display();

        window->setTitle(this->title + " | FPS: " + std::to_string(1.f / delta_time));
    }
}

GameEngine *GameEngine::getInstance() {
    if (instance == nullptr) {
        instance = new GameEngine();
    }
    return instance;
}

void GameEngine::PlaySound(const string &filePath) {
//    buffer.loadFromFile(filePath);
//    sound.setBuffer(buffer);
//    sound.setVolume(5);
//    sound.setLoop(true);
//    sound.play();
}
