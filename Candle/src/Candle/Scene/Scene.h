#pragma once
#include "entt.hpp"

namespace Candle
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		

	private:
		entt::registry m_Registry;
	};
}