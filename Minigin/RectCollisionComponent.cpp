#include "RectCollisionComponent.h"

#include <SDL_render.h>

#include "GameObject.h"
#include "Renderer.h"

dae::RectCollisionComponent::RectCollisionComponent(GameObject* pOwner, const Rectf& rect, bool isDynamic)
	: BaseCollisionComponent(pOwner, isDynamic)
	, m_CollisionBox(rect)
{
}

void dae::RectCollisionComponent::Update()
{
	for (BaseCollisionComponent* component : CollisionManager::GetInstance().GetCollisions())
	{

		if(CheckCollision(component))
		{
			OnCollision(component);
		}
		/*if (HandleCollision(m_Rect, component->m_Rect, component->m_Tag) && !m_IsColliding)
		{
			detail.m_Tag = component->m_Tag;
			detail.m_CollisionThisFrame = true;
			detail.m_OtherRect = component->m_Rect;
			m_CollisionDetail = detail;
			OnCollision(component);
			m_IsColliding = true;
		}
		else
		{
			m_IsColliding = false;
		}*/
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

		if (m_CollisionBox.left < otherRect.left + otherRect.width &&
			m_CollisionBox.left + m_CollisionBox.width > otherRect.left &&
			m_CollisionBox.bottom < otherRect.bottom + otherRect.height &&
			m_CollisionBox.height + m_CollisionBox.bottom > otherRect.bottom)
		{
			return true;
		}
	}
	return false;

}

