#include "RectCollisionComponent.h"

#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"
#include "SceneManager.h"

dae::RectCollisionComponent::RectCollisionComponent(GameObject* pOwner, const Rectf& rect, bool isDynamic, bool isTrigger)
	: BaseCollisionComponent(pOwner, isDynamic, isTrigger)
	, m_CollisionBox(rect)
{
}

void dae::RectCollisionComponent::Update()
{
	if(m_IsDynamic)
	{
		const auto pOwner{ GetOwner()->GetTransform()->GetWorldPosition() };
		m_CollisionBox.left = pOwner.x;
		m_CollisionBox.bottom = pOwner.y;
	}

	for (BaseCollisionComponent* component : CollisionManager::GetInstance().GetCollisions(SceneManager::GetInstance().GetCurrSceneNumber() - 1))
	{
		if(component == nullptr)
		{
			continue;
		}
		if(CheckCollision(component))
		{
			OnCollision(component);
			m_HasCollided = true;
			//
			//break;
		}
		if(m_HasCollided)
		{
			m_HasCollided = false;
		}
		
	}
}

void dae::RectCollisionComponent::Render() const
{
#if _DEBUG
	const SDL_Rect rect{ static_cast<int>(m_CollisionBox.left), static_cast<int>(m_CollisionBox.bottom), static_cast<int>(m_CollisionBox.width), static_cast<int>(m_CollisionBox.height) };
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(dae::Renderer::GetInstance().GetSDLRenderer(), &rect);
	SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 255);
#endif
}

bool dae::RectCollisionComponent::CheckCollision(const BaseCollisionComponent* other) const
{
	//todo: check for collisions with self
	if(const RectCollisionComponent* rect{ dynamic_cast<const RectCollisionComponent*>(other)})
	{
		//todo: check for tags
		if(!CollisionManager::GetInstance().CheckForCollision(GetOwner()->GetLayer(), rect->GetOwner()->GetLayer()))
		{
			return false;
		}

		const Rectf otherRect{ rect->m_CollisionBox };

		if (HandleBoxCollision(m_CollisionBox, otherRect))
		{
			return true;
		}
	}
	return false;

}

bool dae::RectCollisionComponent::CheckCollisionAtPosition(const glm::vec3& pos) const
{
	const Rectf rectf{ pos.x, pos.y, m_CollisionBox.width, m_CollisionBox.height };

	for (const BaseCollisionComponent* component : CollisionManager::GetInstance().GetCollisions(SceneManager::GetInstance().GetCurrSceneNumber() - 1))
	{

		if (const RectCollisionComponent* rect{ dynamic_cast<const RectCollisionComponent*>(component) })
		{
			//todo: check for tags
			if (!CollisionManager::GetInstance().CheckForCollision(GetOwner()->GetLayer(), rect->GetOwner()->GetLayer()) || component->IsTrigger())
			{
				continue;
			}

			const Rectf otherRect{ rect->m_CollisionBox };

			if(HandleBoxCollision(rectf, otherRect))
			{
				return true;
			}
		}
	}
	return false;
}

bool dae::RectCollisionComponent::HandleBoxCollision(const Rectf& rect1, const Rectf& rect2) const
{
	if (rect1.left < rect2.left + rect2.width &&
		rect1.left + rect1.width > rect2.left &&
		rect1.bottom < rect2.bottom + rect2.height &&
		rect1.height + rect1.bottom > rect2.bottom)
	{
		return true;
	}
	return false;
}

