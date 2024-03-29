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
		if (nextPos.x < m_GameField.leftBound)
		{
			nextPos.x = m_GameField.rightBound;
		}
		if (nextPos.x > m_GameField.rightBound)
		{
			nextPos.x = m_GameField.leftBound;
		}
		const auto tag{GetActor()->GetTag()};
		if(tag == "player")
		{
			if (!GetActor()->GetComponent<PlayerCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, static_cast<int>(Layers::level)))
			{

				GetActor()->GetTransform()->SetPosition(nextPos);
			}
		}
		if(tag == "enemy")
		{
			if (!GetActor()->GetComponent<GhostCollisionComponent>()->CheckLayerCollisionAtPosition(nextPos, static_cast<int>(Layers::level)))
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

void pac::MuteCommand::Execute()
{
	auto& soundSystem{ dae::ServiceLocator::GetSoundSystem() };
	if(m_IsMuted)
	{
		for (int iter = 0; iter < 5; ++iter)
		{
			soundSystem.SetVolume(iter, 1.f);
		}
		m_IsMuted = false;
	}
	else
	{
		for (int iter = 0; iter < 5; ++iter)
		{
			soundSystem.SetVolume(iter, 0.f);
		}
		m_IsMuted = true;
	}
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