#pragma once

#include <bitset>
#include <vector>

#include "RootComponent.h"
#include "Singleton.h"

namespace dae
{
	struct Rectf
	{
		float left;
		float bottom;
		float width;
		float height;
	};

	class BaseCollisionComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:

		void Init();
		void AddCollision(BaseCollisionComponent* collision);
		std::vector<BaseCollisionComponent*> GetCollisions() const { return m_pCollisionComponents; }
		//ONLY sets layer1 to collide with layer 2
		void SetLayerCollision(int layer1, int layer2);
		bool CheckForCollision(int layer1, int layer2) const;

		virtual ~CollisionManager() override = default;
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager(CollisionManager&& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;
		CollisionManager& operator=(CollisionManager&& other) noexcept = delete;

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::vector<BaseCollisionComponent*> m_pCollisionComponents;
		std::vector<std::bitset<4>> m_Layers;
	};

	class BaseCollisionComponent : public RootComponent
	{
	public:
		BaseCollisionComponent(GameObject* pOwner, bool isDynamic);
		virtual ~BaseCollisionComponent() override = default;
		BaseCollisionComponent(const BaseCollisionComponent& other) = delete;
		BaseCollisionComponent(BaseCollisionComponent&& other) noexcept = delete;
		BaseCollisionComponent& operator=(const BaseCollisionComponent& other) = delete;
		BaseCollisionComponent& operator=(BaseCollisionComponent&& other) noexcept = delete;

		virtual void OnCollision(BaseCollisionComponent* other) = 0;

		virtual bool CheckCollision(const BaseCollisionComponent* other) const = 0;

	protected:
		bool m_IsDynamic;
	};
}
