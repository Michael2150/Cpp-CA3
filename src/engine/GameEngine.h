//
// Created by micha on 26/11/2023.
//

#ifndef CA3_GAMEENGINE_H
#define CA3_GAMEENGINE_H

#include "../entities/Entity.h"
#include "Box2D/Dynamics/b2World.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameEngine {
private:
    static GameEngine* instance;
    RenderWindow* window;
    vector<shared_ptr<Entity>> entities;
    b2World* world;

public:
    static GameEngine* getInstance();

    void Initialize(int width, int height, const std::string& title);
    void Start();

    b2World& getWorld() { return *world; }
};

#endif //CA3_GAMEENGINE_H
