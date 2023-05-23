#include "GameCommands.h"

#include "HeroComponent.h"
#include "PlayerCollisionComponent.h"
#include "ServiceLocator.h"


void pac::MoveCommand::Execute(const dae::InputAction& inputAction)
{
	auto elapsedSec{dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
	{
		auto nextPos{ currentPos + m_Speed * glm::vec3(inputAction.leftStick.x, -inputAction.leftStick.y, 0.f) * elapsedSec };
		if(!GetActor()->GetComponent<PlayerCollisionComponent>()->CheckCollisionAtPosition(nextPos))
		{
			GetActor()->GetTransform()->SetPosition(nextPos);
		}
		else
		{
			std::cout << "Cannot move due to collision\n";
		}
	}
}

void pac::HitCommand::Execute()
{
	auto hero{ GetActor()->GetComponent<HeroComponent>()};
	if(!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
	}
	hero->Damage();
}

void pac::ScoreCommand::Execute()
{
	auto hero{ GetActor()->GetComponent<HeroComponent>() };
	if (!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
	}
	hero->Pickup(PickupType::apple);
}

void pac::PauseCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlayPause(0, m_IsPaused);
	m_IsPaused = !m_IsPaused;
}

void pac::SoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundDesc{1, 1.f});
}
