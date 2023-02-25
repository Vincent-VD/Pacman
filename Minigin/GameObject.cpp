#include <string>
#include "GameObject.h"

#include <iostream>

#include "ResourceManager.h"
#include "Renderer.h"
#include "RootComponent.h"
#include "TransformComponent.h"


dae::GameObject::GameObject(std::string tag)
	: m_Tag{tag}
	, m_pTransform{new TransformComponent{}}
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

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void dae::GameObject::SetPosition(float x, float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}
