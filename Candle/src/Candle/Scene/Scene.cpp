#include "cdpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Candle/Renderer/Renderer.h"
#include "Candle/Renderer/Renderer2D.h"

#include <glm/glm.hpp>


namespace Candle {

	Scene::Scene()
	{
		/*if (!GetEntityByUUID(m_MainCameraEntityUUID))
		{
			Entity mainCamera = CreateEntity("Main Camera");
			mainCamera.AddOrReplaceComponent<CameraComponent>();
			mainCamera.AddOrReplaceComponent<TransformComponent>();
			
			m_MainCameraEntityUUID = mainCamera.GetUUID();
		}*/
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();

		TagComponent& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		m_EntityMap[uuid] = entity;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_EntityMap.erase(entity.GetUUID());
		m_Registry.destroy(entity);
	}

	Entity Scene::GetEntityByName(std::string_view name)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const TagComponent& tc = view.get<TagComponent>(entity);
			if (tc.Tag == name)
				return Entity{ entity, this };
		}
		return {};
	}

	Entity Scene::GetEntityByUUID(UUID uuid)
	{
		bool exist = m_EntityMap.find(uuid) != m_EntityMap.end();

		CD_CORE_ASSERT(exist, "Entity Does not Exist!");
		if (exist)
			return { m_EntityMap.at(uuid), this };

		return Entity{};
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update all entities
	}

	void Scene::EditorRender(EditorCamera& editorCam)
	{
		Renderer::BeginScene(editorCam, glm::mat4(1.0f));

		// Debug
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		Renderer::RenderQuad(transform);

		Renderer::EndScene();
	}
	
	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		// static_assert(sizeof(T) == 0);
	}

	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}
}