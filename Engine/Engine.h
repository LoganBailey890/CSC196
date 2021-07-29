#pragma once
#include"../Engine/Graphics/Particalsystem.h"
#include"../Engine/Audio/AudioSystem.h"


#include"../Engine/Math/Vector2.h"
#include"../Engine/Math/Color.h"
#include"../Engine/Math/Random.h"
#include"../Engine/Math/MathUtilis.h"
#include"../Engine/Math/Transform.h"

#include"../Engine/Graphics/Shape.h"

#include"../Engine/Base/Actor.h"
#include"../Engine/Base/Scene.h"

//framework
#include"../Engine/FrameWork/EventSystem.h"
#include "../Engine/FrameWork/ResorceSystem.h"

#define NOMINMAX
#include"core.h"
#include <vector>
#include <memory>
#include<algorithm>
namespace nc
{
	class Engine
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		template<typename T>
		T* Get();
	private:
		std::vector<std::unique_ptr<System>> systems;
	};
	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems)
		{
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}