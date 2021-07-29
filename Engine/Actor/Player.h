#pragma once
#include"Base/Actor.h"

class Player : public nc::Actor
{
public:
    Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed);

    void Initialize() override;

    void Update(float dt) override;
    void OnCollision(Actor* actor) override;

private:
    float speed = 300;
    float fireRate = 0.1f;
    float fireTimer = 0.0f;
    nc::Vector2 velocity;
};