#include <iostream>
#include <memory>
#include <iomanip>
#include "GameEngine.h"
#include "../template/Ball.cpp"
#include "../template/FPS_Counter.cpp"
#include "../template/Obstacle.cpp"

GameEngine* GameEngine::instance = nullptr;

void GameEngine::Initialize(int width, int height, const std::string &title) {
    std::cout << "Initializing game engine..." << std::endl;

    // Create fullscreen the game window
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default);

    auto fps = 60;
    this->window->setFramerateLimit(fps);

    // Create the game physics world
    world = new b2World(b2Vec2(0.0f, -9.8f));

    std::cout << "Game engine initialized! Physics interval: " << std::fixed << std::setprecision(6) << physics_engine_steps_interval << " seconds at " << fps << " FPS. = " << physics_engine_steps_interval * fps << " physics steps per second." << std::endl;
}

void GameEngine::Start() {
    std::cout << "Starting game engine..." << std::endl;

    auto fps_counter = std::make_shared<FPSCounter>();
    entities.push_back(fps_counter);

    // Create 50 balls
    for (int i = 0; i < 100; i++){
        auto ball = std::make_shared<BallEntity>();
        entities.push_back(ball);
    }

    auto floor = std::make_shared<ObstacleEntity>(IntRect(100, 100, 1280, 10));
    entities.push_back(floor);

    auto timer = sf::Clock();

    // Start all the entities and components here:
    for (const auto& entity : entities) {
        entity->Start();
    }

    auto delta_time = timer.restart().asSeconds();

    std::cout << "Game started up in " << std::fixed << std::setprecision(6) << delta_time << " seconds." << std::endl;

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
            }

            // Space bar down
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    delta_time *= 5;
                }
            }
        }

        // Update all the entities and components here
        for (const auto& entity : entities) {
            entity->Update(delta_time);
        }

        window->clear(sf::Color::Black);

        world->Step(delta_time, 8, 3);

        // Render all the entities and components here
        for (const auto& entity : entities) {
            entity->Render(window);
        }

        window->display();
    }
}

GameEngine *GameEngine::getInstance() {
    if (instance == nullptr) {
        instance = new GameEngine();
    }
    return instance;
}
