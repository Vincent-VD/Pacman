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
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

std::vector<std::shared_ptr<GameObject>> Scene::GetPersisentObjects() const
{
	return m_pPersistentObjects;
}

void Scene::Update()
{
	for(size_t iter = 0; iter < m_pObjects.size(); ++iter)
	{
		const auto& object{ m_pObjects[iter] };
		if (object.get() == nullptr) continue;
		object->Update();
		if(object->IsMarkedForDeletion())
		{
			m_ItersToRemove.emplace_back(iter);
		}
		
	}
	/*for (size_t iter = 0; iter < m_pPersistentObjects.size(); ++iter)
	{
		const auto& persistantObject{ m_pPersistentObjects[iter] };
		persistantObject->Update();
		if (persistantObject->IsMarkedForDeletion())
		{
			m_ItersToRemove.emplace_back(iter);
		}
	}*/
	for (auto iter : m_ItersToRemove)
	{
		m_pObjects[iter] = nullptr;
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
	for (auto& object : m_pObjects)
	{
		if (object.get() == nullptr) continue;
		object->FixedUpdate();
	}

	/*for (auto& object : m_pPersistentObjects)
	{
		object->FixedUpdate();
	}*/
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		if (object.get() == nullptr) continue;
		object->Render();
	}
	/*for (auto& object : m_pPersistentObjects)
	{
		object->Render();
	}*/
}

void Scene::RenderUI() const
{
	for (const auto& object : m_pObjects)
	{
		if (object.get() == nullptr) continue;
		const auto UIComp{ object->GetComponent<UIBaseComponent>() };
		if(UIComp)
		{
			UIComp->RenderUI();
		}
	}
	/*for (const auto& object : m_pPersistentObjects)
	{
		const auto UIComp{ object->GetComponent<UIBaseComponent>() };
		if (UIComp)
		{
			UIComp->RenderUI();
		}
	}*/
}

