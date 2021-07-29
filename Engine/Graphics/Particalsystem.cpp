#include "Particalsystem.h"
#include "../Math/Random.h"
namespace nc
{
    void ParticleSystem::Startup()
    {
        particle.resize(1000);
    }

    void ParticleSystem::Shutdown()
    {
        particle.clear();
    }

    void ParticleSystem::Update(float dt)
    {
        for (Particle& particle : particle)
        {
            if (particle.isActive)
            {
                particle.lifetime -= dt;
                particle.isActive = particle.lifetime > 0;
                particle.prevPosition = particle.position;
                particle.position += particle.velocity * dt;

            }
        }


    }

    void ParticleSystem::Draw(Core::Graphics& graphics)
    {
        for (const Particle& particle : particle)
        {
            if (particle.isActive)
            {
                graphics.SetColor(particle.color);
                graphics.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.prevPosition.y + 10);

            }
        }
    }

    void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, const Color& color, float speed)
    {
        for (size_t i = 0; i < count; i++)
        {
            auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
            if (particles != particle.end())
            {
                particles->isActive = true;
                particles->lifetime = lifetime;
                particles->position = position;
                particles->prevPosition = position;
                particles->color = color;

                particles->velocity = Vector2{ RandomRange(-1, 1), RandomRange(-1, 1) } *(speed * Random());
            }
        }
    }
    void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, const std::vector<Color>& colors, float speed, float angle, float angleRange)
    {
        for (size_t i = 0; i < count; i++)
        {
            auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
            if (particles != particle.end())
            {
                particles->isActive = true;
                particles->lifetime = lifetime;
                particles->position = position;
                particles->prevPosition = position;
                particles->color = colors[rand() % colors.size()];

                particles->velocity = nc::Vector2::Rotate(nc::Vector2::right, angle + nc::RandomRange(-angleRange, angleRange)) * (speed * Random());
            }
        }
    }
}