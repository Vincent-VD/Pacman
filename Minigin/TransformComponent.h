#pragma once
#include "MiniginPCH.h"
#include "RootComponent.h"

namespace dae
{
    //Code based off query from ChatGPT
	class TransformComponent final
	{
	public:
		TransformComponent(GameObject* pOwner);
		~TransformComponent() = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

        const glm::vec3& GetPosition() const { return m_Position; }
        const glm::vec3& GetRotation() const { return m_Rotation; }
        const glm::vec3& GetScale() const { return m_Scale; }
        const glm::mat4& GetLocalTransform();
        const glm::mat4& GetWorldTransform();

        void SetPosition(float x, float y, float z);
        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::vec3& rotation);
        void SetScale(const glm::vec3& scale);
        void SetDirty();

	private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;
        glm::mat4 m_LocalTransform;
        glm::mat4 m_WorldTransform;
        bool m_IsLocalDirty{ true };
        bool m_IsWorldDirty{ true };

		GameObject* m_pOwner;
		
		void UpdateTransforms();
	};
}