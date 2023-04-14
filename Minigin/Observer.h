#pragma once
#include "MiniginPCH.h"
namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		virtual void OnNotify(const std::string& msg, const GameObject* gameObject) = 0;
	};
}
