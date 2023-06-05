#ifndef GHOSTCOMPONENT
#define GHOSTCOMPONENT

#include <string>

#include "Observer.h"
#include "RootComponent.h"

namespace pac
{
	class GhostState;

	class GhostComponent : public dae::RootComponent, dae::Observer<const std::string&>
	{
	public:
		GhostComponent(dae::GameObject* pOwner, const std::string& type);
		virtual ~GhostComponent() override;
		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;

		virtual void OnNotify(const std::string& msg) override;
		virtual void OnSubjectDestroyed() override {}
		void OnCollision() const;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		const std::string m_Type;
		GhostState* m_pState;
	};
}

#endif //GHOSTCOMPONENT
