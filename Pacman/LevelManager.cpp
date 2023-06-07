#include "LevelManager.h"

#include "PacmanGame.h"

void pac::LevelManager::RegisterPellet()
{
	++m_PelletAmount;
}

void pac::LevelManager::DestroyPellet()
{
	--m_PelletAmount;
	if(m_PelletAmount == 0)
	{
		PacmanGame::GoToNextLevel();
	}
}
