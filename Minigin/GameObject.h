#pragma once
#include <list>

#include <memory>
#include <vector>
#include "TransformComponent.h"

namespace dae
{
	//class TransformComponent;
	class RootComponent;
	class Texture2D;

	class GameObject final
	{
	public:
		GameObject(const std::string& tag);
		~GameObject()
		{
			std::cout << m_Tag << std::endl;
		}

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Destroy() { m_MarkedForDeletion = true; }
		const bool IsMarkedForDeletion() const { return m_MarkedForDeletion; }

		std::string GetTag() { return m_Tag; }

		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render() const;

		//Getters
		TransformComponent* GetTransform() const;

		//Template component funtions
		template<typename Component>
		std::shared_ptr<Component> GetComponent() const;
		template<typename Component>
		std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> pComponent);
		template<typename Component>
		void RemoveComponent(std::shared_ptr<Component> pComponent);

		void SetParent(GameObject* parent, bool keepWorldTransform);
		GameObject* GetParent() const;

		/*size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;*/

	private:
		bool m_MarkedForDeletion{ false };
		std::string m_Tag;

		std::unique_ptr<TransformComponent> m_pTransform{};
		std::vector<std::shared_ptr<RootComponent>> m_pComponents;
		std::vector<std::unique_ptr<GameObject>> m_pChildren;
		GameObject* m_pParent{ nullptr };
	};

	template<typename Component>
	inline std::shared_ptr<Component> GameObject::GetComponent() const
	{
		//todo: this doesn't work. why?
		/*for (auto& component : m_pComponents)
		{
			if (auto curr = std::dynamic_pointer_cast<Component>(component))
			{
				return std::shared_ptr<Component>(curr.get());
			}
		}
		return std::shared_ptr<Component>(nullptr);*/

		std::shared_ptr<Component> componentToGet = nullptr;

		for (auto& currentComponent : m_pComponents)
		{
			std::shared_ptr<Component> curr{ std::dynamic_pointer_cast<Component>(currentComponent) };
			if (curr)
			{
				componentToGet = curr;
			}
		}
		return componentToGet;
	}

	template<typename Component>
	inline std::shared_ptr<Component> GameObject::AddComponent(std::shared_ptr<Component> component)
	{
		m_pComponents.emplace_back(component);
		return component;
	}

	template <typename Component>
	inline void GameObject::RemoveComponent(std::shared_ptr<Component> pComponentToRemove)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponentToRemove));
		//delete pComponentToRemove;
	}

}
