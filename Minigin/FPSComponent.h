#pragma once
#include <glm/fwd.hpp>
#include <memory>

#include "RootComponent.h"

namespace dae
{
	class TextRenderComponent;

	class FPSComponent : public RootComponent
	{
	public:
		FPSComponent(GameObject* pOwner);
		virtual ~FPSComponent() override = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		glm::uint32_t GetFPS() const;
		void Update() override;
		void FixedUpdate() override;

	private:
		float m_ElapsedSec{};
		glm::uint32_t m_FPS{};
		float m_UpdateTimer{};
		const float m_UpdateInterval{ 1.f };
		std::shared_ptr<TextRenderComponent> m_pText = nullptr;
	};
}
