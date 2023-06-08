#ifndef FPS_COMPONENT
#define FPS_COMPONENT

#include "MiniginPCH.h"

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
		virtual void Update() override;
		virtual void FixedUpdate() override;

	private:
		float m_ElapsedSec{};
		glm::uint32_t m_FPS{};
		float m_UpdateTimer{};
		const float m_UpdateInterval{ 1.f };
		std::shared_ptr<TextRenderComponent> m_pText = nullptr;
	};
}

#endif //FPS_COMPONENT