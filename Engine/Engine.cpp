#include "Engine.h"

namespace nc
{
	void Engine::Startup()
	{
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());
		systems.push_back(std::make_unique<EventSystem>());
		systems.push_back(std::make_unique<ResourceSystem>());
		//audio system

		for (auto& system : systems)
		{
			system->Startup();
		}
	}
	void Engine::Shutdown()
	{
		for (auto& system : systems)
		{
			system->Shutdown();
		}
	}
	void Engine::Update(float dt)
	{
		for (auto& system : systems)
		{
			system->Update(dt);
		}
	}
	void Engine::Draw(Core::Graphics& graphics)
	{
		std::for_each(systems.begin(), systems.end(), [graphics](auto& system) mutable
			{
				if (dynamic_cast<GraphicsSystem*>(system.get()))
				{
					dynamic_cast<GraphicsSystem*>(system.get())->Draw(graphics);
				};
			});
	}
	
}