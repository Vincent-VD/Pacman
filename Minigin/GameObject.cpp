#include <string>
#include "GameObject.h"

#include <iostream>

#include "ResourceManager.h"
#include "Renderer.h"
#include "RootComponent.h"
//#include "TransformComponent.h"


dae::GameObject::GameObject(std::string tag)
	: m_Tag{tag}
	, m_pTransform{ new TransformComponent{this} }
{
}

dae::GameObject::~GameObject()
{
	//Remove all components when object is destroyed
	/*for (std::shared_ptr<RootComponent> pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}*/
	delete m_pTransform;
}

void dae::GameObject::Update()
{
	for (auto& pComponent : m_pComponents)
	{
		pComponent->Update();
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
	return m_pTransform;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldTransform)
{
	if(parent == nullptr)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition());
	}
	else if(keepWorldTransform)
	{
		m_pTransform->SetPosition(m_pTransform->GetPosition() - m_pParent->GetTransform()->GetPosition());
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
	//todo: update pos, rot, scale
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::RemoveChild(GameObject* obj)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), obj));
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
