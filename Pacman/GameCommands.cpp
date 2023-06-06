#include "GameCommands.h"

#include "HeroComponent.h"
#include "Minigin.h"
#include "PacmanGame.h"
#include "PlayerCollisionComponent.h"
#include "ServiceLocator.h"
#include "UIMenuComponent.h"
#include "SceneManager.h"


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
		auto nextPos{ currentPos + m_Speed * glm::vec3(inputAction.leftStick.x, -inputAction.leftStick.y, 0.f) * elapsedSec };
		if(!GetActor()->GetComponent<PlayerCollisionComponent>()->CheckCollisionAtPosition(nextPos))
		{
			GetActor()->GetTransform()->SetPosition(nextPos);
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
