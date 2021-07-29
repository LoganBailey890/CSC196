#pragma once
#include"Base/Actor.h"


class Enemy2 : public nc::Actor
{
public:
    Enemy2(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform , shape }, speed{ speed }  {}

    void Update(float dt) override;
    void OnCollision(Actor* actor) override;

private:
    float speed = 300;
 
};