#include "UIState.h"

#include <iostream>

#include "imgui.h"
#include "PacmanGame.h"


pac::UIState* pac::MainMenuState::HandleInput()
{
	
	return nullptr;
}

pac::UIState* pac::MainMenuState::Update()
{
	ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	if (ImGui::Button("Play Single"))
	{
		std::cout << "Starting Single\n";
		ImGui::End();
		return new IdleState{};

	}
	if (ImGui::Button("Play 1 v 1"))
	{
		std::cout << "Starting 1 v 1\n";
		ImGui::End();
		return new IdleState{};

	}
	if (ImGui::Button("Play Co-op"))
	{
		std::cout << "Starting Co-op\n";
		ImGui::End();
		return new IdleState{};

	}
	ImGui::End();
	return nullptr;

}

pac::UIState* pac::PausedState::HandleInput()
{
	return nullptr;
}

pac::UIState* pac::PausedState::Update()
{
	ImGui::Text("Game Paused\n, Press ESC to resume");
	return nullptr;
}

pac::UIState* pac::InputState::HandleInput()
{
	return nullptr;
}

pac::UIState* pac::InputState::Update()
{
	ImGui::InputText("Enter name: ", &pac::PacmanGame::PlayerName[0], 3);
	if (ImGui::Button("Enter"))
	{
		std::cout << "Saving...\n";
	}
	return nullptr;
}

void pac::InputState::OnExit()
{
	pac::PacmanGame::SaveGame();
}

pac::UIState* pac::EndState::HandleInput()
{
	return nullptr;
}

pac::UIState* pac::EndState::Update()
{
	//Read file and display rankings in ImGui window
	return nullptr;
}

pac::UIState* pac::IdleState::HandleInput()
{
	return nullptr;
}

pac::UIState* pac::IdleState::Update()
{
	return nullptr;
}
