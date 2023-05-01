#include "GameCommands.h"

#include "HeroComponent.h"


void pac::MoveCommand::Execute(const dae::InputAction& inputAction)
{
	auto elapsedSec{dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
	{
		GetActor()->GetTransform()->SetPosition(currentPos + m_Speed * glm::vec3(inputAction.leftStick.x, -inputAction.leftStick.y, 0.f) * elapsedSec);
	}
}

void pac::HitCommand::Execute([[maybe_unused]] const dae::InputAction& inputAction)
{
	auto hero{ GetActor()->GetComponent<HeroComponent>()};
	if(!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
	}
	hero->Damage();
}

void pac::ScoreCommand::Execute([[maybe_unused]] const dae::InputAction& inputAction)
{
	auto hero{ GetActor()->GetComponent<HeroComponent>() };
	if (!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
	}
	hero->Pickup(PickupType::apple);
}
