#include "TransformComponent.h"

#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner)
	: m_pOwner(pOwner)
{
}

void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	m_IsWorldDirty = true;
}

void dae::TransformComponent::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
	m_IsWorldDirty = true;
}

void dae::TransformComponent::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	m_IsWorldDirty = true;
}

void dae::TransformComponent::SetDirty()
{
	m_IsWorldDirty = true;
}

const glm::vec3 dae::TransformComponent::GetLocalPosition() const 
{
	return m_Position;
}

const glm::vec3 dae::TransformComponent::GetWorldPosition()
{
	if (m_IsWorldDirty)
	{
		UpdateTransforms();
	}
	return glm::vec3{ m_WorldTransform[3][0], m_WorldTransform[3][1], m_WorldTransform[3][2] };
}

const glm::vec3 dae::TransformComponent::GetLocalRotation() const
{
	return m_Rotation;
}

const glm::vec3 dae::TransformComponent::GetLocalScale() const
{
	return m_Scale;
}

const glm::mat4& dae::TransformComponent::GetLocalTransform()
{
	if(m_IsLocalDirty)
	{
		UpdateTransforms();
	}
	return m_LocalTransform;
}

const glm::mat4& dae::TransformComponent::GetWorldTransform()
{
	if (m_IsWorldDirty)
	{
		UpdateTransforms();
	}
	return m_LocalTransform;
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3{ x, y, z };
	//m_IsLocalDirty = true;
	m_IsWorldDirty = true;
}


void dae::TransformComponent::UpdateTransforms()
{
	// Calculate the local transform
	m_LocalTransform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(m_Rotation)) * glm::scale(glm::mat4(1.0f), m_Scale);
	m_IsLocalDirty = false;

	if (m_IsWorldDirty) {
		// Calculate the world transform
		const auto parent{ m_pOwner->GetParent() };
		if(parent == nullptr)
		{
			m_WorldTransform = m_LocalTransform;
		}
		else
		{
			m_WorldTransform = parent->GetTransform()->GetWorldTransform() + m_LocalTransform;
		}
		m_IsWorldDirty = false;
	}
}
