#include "CircularMoveComponent.h"

#include "GameObject.h"
#include "Time.h"

using namespace dae;

CircularMoveComponent::CircularMoveComponent(GameObject* pOwner, float radius, float moveSpeed)
	: RootComponent(pOwner)
	, m_Radius(radius)
	, m_MoveSpeed(moveSpeed)
{
	auto centerTransform = GetOwner()->GetTransform()->GetWorldTransform();
	m_Center = glm::vec3{ centerTransform[3][0], centerTransform[3][1], centerTransform[3][2] };
}

void CircularMoveComponent::Update()
{
	const float elapsedTime{ Time::GetInstance().GetDeltaTime() };

	m_CurrAngle += m_MoveSpeed * elapsedTime;

	if(GetOwner()->GetParent())
	{
		auto centerTransform = GetOwner()->GetParent()->GetTransform()->GetWorldTransform();
		m_Center = glm::vec3{ centerTransform[3][0], centerTransform[3][1], centerTransform[3][2] };
	}

	glm::vec3 currPos{};

	currPos.x = m_Center.x + cos(m_CurrAngle) * m_Radius;
	currPos.y = m_Center.y + sin(m_CurrAngle) * m_Radius;

	GetOwner()->GetTransform()->SetPosition(currPos);

}
