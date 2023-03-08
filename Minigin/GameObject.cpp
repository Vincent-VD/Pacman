#include <string>
#include "GameObject.h"

#include <iostream>

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
	if(parent == nullptr)
	{
		m_pTransform->SetPosition(m_pTransform->GetWorldPosition());
	}
	else if(keepWorldTransform)
	{
		m_pTransform->SetPosition(m_pTransform->GetWorldPosition() - m_pParent->GetTransform()->GetLocalPosition());
	}
	if(m_pParent != nullptr)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = parent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
	m_pTransform->SetDirty();
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::RemoveChild([[maybe_unused]]GameObject* obj)
{
	//m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), obj));
	//todo: what happens to child when gameobject is removed?
}

void dae::GameObject::AddChild(GameObject* obj)
{
	m_pChildren.emplace_back(obj);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}
