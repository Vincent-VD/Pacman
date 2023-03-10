#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(size_t iter = 0; iter < m_objects.size(); ++iter)
	{
		const auto& object{ m_objects[iter] };
		object->Update();
		if(object->IsMarkedForDeletion())
		{
			m_ItersToRemove.emplace_back(iter);
		}
	}
	for (auto iter : m_ItersToRemove)
	{
		m_objects[iter] = nullptr;
		//delete m_objects[iter].get();
	}
	m_ItersToRemove.clear();

	/*for(auto& object : m_objects)
	{
		object->Update();
	}*/
}

void Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

