#include"Projectile.h"
#include"../Math/MathUtilis.h"
#include"Engine.h"

void Projectile::Update(float dt)
{
    Actor::Update(dt);

    lifetime -= dt;
    if (lifetime <= 0)
    {
        destroy = true;
    }

    transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
    transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
    transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

    std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::yellow };
    scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 10, 0.5f, colors[nc::RandomRandInt(0, colors.size())], 10);


}