#include "Game.h"
#include"../Actor/Player.h"
#include"../Actor/Enemy.h"
#include "Actor/Enemy2.h"
#include"../Actor/Projectile.h"


void Game::Initialize()
{
    engine = std::make_unique<nc::Engine>(); // New Engine()
    engine->Startup();
    scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();

    engine->Get<nc::AudioSystem>()->AddAudio("explosion", "explosion.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("player_fire", "PlayerShots.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("player_explosion", "PlayerExlosion.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("enemy_fire", "EnemyShot.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("enemy_explosion", "EnemyExlosion.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("BGK", "BackGround.mp3");

    engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
    engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
    scene->RemoveAllActor();
    engine->Shutdown();
}

void Game::Update(float dt)
{
    stateTimer += dt;

    //(this->*stateFunction)(dt);

    switch (state)
    {
    case Game::eState::TitleScreen:
        if (Core::Input::IsPressed(VK_SPACE))
        {
            state = eState::StartGame;
        }
        break;
    case Game::eState::StartGame:
        score = 0;
        lives = 1;
        state = eState::StartLevel;
        break;
    case Game::eState::StartLevel:
        scene->engine->Get<nc::AudioSystem>()->PlayAudio("BGK");
        UpdateLevelStart(dt);
        state = eState::Game;
        break;
    case Game::eState::Game:
        if (scene->GetActors<Enemy>().size() == 0)
        {
            if (scene->GetActors<Enemy2>().size() == 0)
            {
               state = eState::Gameover;
            }
        }
        break;
    case Game::eState::Gameover:
        scene->RemoveAllActor();
        if (Core::Input::IsPressed(VK_SPACE))
        {
            state = eState::TitleScreen;
        }
        break;
    default:
        break;
    }

    engine->Update(dt);
    scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
    switch (state)
    {
    case Game::eState::TitleScreen:

        graphics.SetColor(nc::Color::cyan);
        graphics.DrawString(380, 320 + static_cast<int>(std::sin(stateTimer * 6.0f) * 10.0f), "HECTOR");


        graphics.SetColor(nc::Color::red);
        graphics.DrawString(340, 360, "Press Space to Start");
        break;
    case Game::eState::StartGame:

        break;
    case Game::eState::StartLevel:
        break;
    case Game::eState::Game:
        break;
    case Game::eState::Gameover:
        graphics.SetColor(nc::Color::red);
        graphics.DrawString(340, 360, "GameOver");
        graphics.DrawString(360, 380, "Presse Space to restart");
        break;
    default:
        break;
    }
    graphics.SetColor(nc::Color::white);
    graphics.DrawString(30, 20, std::to_string(score).c_str());
    graphics.DrawString(750, 20, std::to_string(lives).c_str());
    scene->Draw(graphics);
    engine->Draw(graphics);
}
void Game::UpdateTitle(float dt)
{
    if (Core::Input::IsPressed(VK_SPACE))
    {
        stateFunction = &Game::UpdateLevelStart;

        //state = eState::StartGame;
    }
}

void Game::UpdateLevelStart(float dt)
{
    scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0, 3 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Player.txt"), 300.0f));
    for (size_t i = 0; i < 2; i++)
    {
        scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{ nc::RandomRange(0.0f,800), nc::RandomRange(0.0f,600)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Enemy.txt"), 100.0f));
    }

    for (size_t i = 0; i < 4; i++)
    {
        scene->AddActor(std::make_unique<Enemy2>(nc::Transform{ nc::Vector2{ nc::RandomRange(0.0f,800), nc::RandomRange(0.0f,600)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Enemy2.txt"), 100.0f));
        
    }
    state = eState::Game;

}

void Game::OnAddPoints(const nc::Event& event)
{
    score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const nc::Event& event)
{
    lives--;
    std::cout << std::get<std::string>(event.data) << std::endl;
    state = eState::Gameover;
}