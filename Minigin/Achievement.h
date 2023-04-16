#pragma once
#include "Observer.h"
#include "RootComponent.h"

namespace dae
{
	class Achievement : public RootComponent, public Observer
	{
	public:
		Achievement(GameObject* pOwner);
		virtual ~Achievement() override = default;
		Achievement(const Achievement& other) = delete;
		Achievement(Achievement&& other) noexcept = delete;
		Achievement& operator=(const Achievement& other) = delete;
		Achievement& operator=(Achievement&& other) noexcept = delete;

		virtual void OnNotify(const std::string& msg, const GameObject* gameObject) override;

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
	};


}
