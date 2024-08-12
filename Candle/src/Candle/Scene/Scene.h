#pragma once
#include "Candle/Core/Timestep.h"
#include "Candle/Core/UUID.h"
#include "Candle/Renderer/EditorCamera.h"

#include "entt.hpp"

namespace Candle
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		Entity GetEntityByName(std::string_view name);
		Entity GetEntityByUUID(UUID uuid);

		void OnUpdate(Timestep ts);
		void EditorRender(EditorCamera& editorCam);

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		// TODO: Refactor this
		UUID m_MainCameraEntityUUID;

		friend class Entity;
	};
}