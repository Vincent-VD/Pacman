#ifndef TRANSITION_COMPONENT
#define TRANSITION_COMPONENT

#include <RootComponent.h>

namespace pac
{
	class TransitionComponent : public dae::RootComponent
	{
	public:
		TransitionComponent(dae::GameObject* pOwner);
		virtual ~TransitionComponent() override = default;
		TransitionComponent(const TransitionComponent& other) = delete;
		TransitionComponent(TransitionComponent&& other) noexcept = delete;
		TransitionComponent& operator=(const TransitionComponent& other) = delete;
		TransitionComponent& operator=(TransitionComponent&& other) noexcept = delete;

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void LateUpdate() override;
		virtual void Render() const override {}
	};
}



#endif //TRANSITION_COMPONENT