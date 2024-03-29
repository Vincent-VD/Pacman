#include "Scene.h"
#include "GameObject.h"
#include "UIBaseComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::AddPersistent(std::shared_ptr<GameObject> object)
{
	m_pObjects.emplace_back(object);
	m_pPersistentObjects.emplace_back(object);
}

void Scene::AddPersistentObjects(std::vector<std::shared_ptr<GameObject>> objects)
{
	for (auto& element : objects)
	{
		m_pObjects.emplace_back(element);
		m_pPersistentObjects.emplace_back(element);
	}
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove_if(m_pObjects.begin(), m_pObjects.end(), [object](std::shared_ptr<GameObject> obj) {return obj.get() == object.get(); }), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

std::vector<std::shared_ptr<GameObject>> Scene::GetAndRemovePersisentObjects()
{
	std::vector<std::shared_ptr<GameObject>> res = m_pPersistentObjects;

	for (auto& gameObject : res)
	{
		Remove(gameObject);
		m_pPersistentObjects.erase(std::remove_if(m_pPersistentObjects.begin(), m_pPersistentObjects.end(), [gameObject](std::shared_ptr<GameObject> obj) {return obj.get() == gameObject.get(); }), m_pPersistentObjects.end());
	}

	return res;
}

void Scene::Update()
{
	for(size_t iter = 0; iter < m_pObjects.size(); ++iter)
	{
		const auto& object{ m_pObjects[iter] };
		if (object == nullptr) continue;
		object->Update();
		if(object->IsMarkedForDeletion())
		{
			m_ItersToRemove.emplace_back(iter);
		}
		
	}
	for (auto iter : m_ItersToRemove)
	{
		Remove(m_pObjects[iter]);
	}
	m_ItersToRemove.clear();
}

void Scene::FixedUpdate()
{
	for (auto& object : m_pObjects)
	{
		if (object.get() != nullptr) continue;
		object->FixedUpdate();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_pObjects)
	{
		if (object.get() == nullptr) continue;
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		if (object == nullptr) continue;
		object->Render();
	}
}

void Scene::RenderUI() const
{
	for (const auto& object : m_pObjects)
	{
		if (object == nullptr) continue;
		const auto UIComp{ object->GetComponent<UIBaseComponent>() };
		if(UIComp)
		{
			UIComp->RenderUI();
		}
	}
}

