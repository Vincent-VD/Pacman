#ifndef ROOT_COMPONENT
#define ROOT_COMPONENT

#include "MiniginPCH.h"

namespace dae
{
	class GameObject;

	class RootComponent
	{
	public:
		RootComponent(GameObject* pOwner);
		virtual ~RootComponent() = default;

		RootComponent(const RootComponent& other) = delete;
		RootComponent(RootComponent&& other) = delete;
		RootComponent& operator=(const RootComponent& other) = delete;
		RootComponent& operator=(RootComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void LateUpdate() {}
		virtual void Render() const {}

		GameObject* GetOwner() const { return m_pGameObject; }

	private:
		GameObject* m_pGameObject;
	};
}

#endif //ROOT_COMPONENT