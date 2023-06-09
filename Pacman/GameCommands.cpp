#include "GameCommands.h"

#include "CollisionTemplates.h"
#include "GameTime.h"
#include "HeroComponent.h"
#include "Minigin.h"
#include "PacmanGame.h"
#include "PlayerCollisionComponent.h"
#include "ServiceLocator.h"
#include "UIMenuComponent.h"
#include "GameObject.h"
#include "GhostCollisionComponent.h"


void pac::MoveCommand::Execute(const dae::InputAction& inputAction)
{
	if(dae::Minigin::GetPaused())
	{
		return;
	}
	auto elapsedSec{dae::GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
	{
		glm::vec3 dir{};
		const float angle{ std::atan2(inputAction.leftStick.y, inputAction.leftStick.x) };
		const float cos{ std::cos(angle) };
		const float sin{ std::sin(angle) };
		if(std::abs(cos) > std::abs(sin))
		{
			dir = { cos, 0.f, 0.f };
		}
		else
		{
			dir = { 0.f, -sin, 0.f };
		}

		auto nextPos{ currentPos + m_Speed * dir * elapsedSec };
		const auto tag{GetActor()->GetTag()};
		if(tag == "player")
		{
			if (!GetActor()->GetComponent<PlayerCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, (int)Layers::level))
			{
				GetActor()->GetTransform()->SetPosition(nextPos);
			}
		}
		if(tag == "enemy")
		{
			if (!GetActor()->GetComponent<GhostCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, (int)Layers::level))
			{
				GetActor()->GetTransform()->SetPosition(nextPos);

			}
		}
	}
}

void pac::HitCommand::Execute()
{
	auto hero{ GetActor()->GetComponent<HeroComponent>() };
	if(!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
		return;
	}
	hero->Damage();
}

void pac::ScoreCommand::Execute()
{
	const auto hero{ GetActor()->GetComponent<HeroComponent>() };
	if (!hero)
	{
		std::cout << "Hero component not found (HitCommand)\n";
		return;
	}
	hero->Pickup(PickupType::pellet);
}

void pac::MusicPauseCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlayPause(0, m_IsPaused);
	m_IsPaused = !m_IsPaused;
}

void pac::SoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundDesc{1, 1.f});
}

void pac::GamePauseCommand::Execute()
{
	const auto menu{ GetActor()->GetComponent<UIMenuComponent>() };
	if(!menu)
	{
		std::cout << "Menu component not found (GamePauseCommand)\n";
		return;
	}
	
	menu->OnNotify("paused");
}

void pac::Next::Execute()
{
	pac::PacmanGame::GoToNextLevel();
}

void pac::GhostMove::Execute()
{

}
