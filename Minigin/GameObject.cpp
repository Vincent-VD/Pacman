#include <string>
#include "GameObject.h"

#include <iostream>

#include "Observer.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RootComponent.h"
//#include "TransformComponent.h"


dae::GameObject::GameObject(std::string tag)
	: m_Tag{tag}
	, m_pTransform{ std::make_unique<TransformComponent>(this) }
{
}

void dae::GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update();
	}
	for(auto& pChild : m_pChildren)
	{
		pChild->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}

void dae::GameObject::LateUpdate()
{

}

void dae::GameObject::Render() const
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return m_pTransform.get();
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldTransform)
{
	if (parent == nullptr)
		GetTransform()->SetPosition(GetTransform()->GetWorldPosition());
	else {
		if (keepWorldTransform)
			GetTransform()->SetPosition(GetTransform()->GetWorldPosition() - GetParent()->GetTransform()->GetWorldPosition());
		GetTransform()->SetDirty();
	}
	std::unique_ptr<GameObject> child;
	if (m_pParent != nullptr)
	{
		for (auto it = m_pParent->m_pChildren.begin(); it != m_pParent->m_pChildren.end(); ++it)
		{
			if (it->get() == this)
			{
				child = std::move(*it);
				m_pParent->m_pChildren.erase(it);
				break;
			}
		}
	}
	m_pParent = parent;
	if (parent != nullptr)
	{
		if (child == nullptr)
		{
			child = std::unique_ptr<GameObject>(this);
			m_pParent->m_pChildren.emplace_back(std::move(child));
		}
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::GameObject::RemoveObserver(const Observer* pObserver)
{
	
	for (auto it = m_pObservers.begin(); it != m_pObservers.end(); ++it)
	{
		if (*it == pObserver)
		{
			m_pObservers.erase(it);
			break;
		}
	}
}

void dae::GameObject::NotifyObservers(const std::string& event)
{
	for (auto observer : m_pObservers)
	{
		observer->OnNotify(event, this);
	}
}