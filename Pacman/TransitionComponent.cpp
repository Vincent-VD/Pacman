#include "TransitionComponent.h"

#include "LevelManager.h"
#include "PacmanGame.h"

pac::TransitionComponent::TransitionComponent(dae::GameObject* pOwner)
	:RootComponent(pOwner)
{
}

void pac::TransitionComponent::LateUpdate()
{
	auto& levelManager{ LevelManager::GetInstance() };
	if(levelManager.GetLevelTransition())
	{
		levelManager.ResetLevelTransition();
		PacmanGame::GoToNextLevel();
	}
}
