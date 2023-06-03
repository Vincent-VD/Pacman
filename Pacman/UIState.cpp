#include "UIState.h"

#include <iostream>
#include <fstream>

#include "imgui.h"
#include "InputManager.h"
#include "Minigin.h"
#include "PacmanGame.h"
#include "ResourceManager.h"
#include "SceneManager.h"


pac::UIState* pac::MainMenuState::HandleInput(const std::string& /*action*/)
{
	
	return nullptr;
}

pac::UIState* pac::MainMenuState::Update()
{
	ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	if (ImGui::Button("Play Single"))
	{
		std::cout << "Starting Single\n";
		pac::PacmanGame::SetGameMode(PacmanGame::GameMode::Solo);
		ImGui::End();
		return new PausedState{};

	}
	if (ImGui::Button("Play 1 v 1"))
	{
		std::cout << "Starting 1 v 1\n";
		pac::PacmanGame::SetGameMode(PacmanGame::GameMode::Versus);
		ImGui::End();
		return new WaitState{};

	}
	if (ImGui::Button("Play Co-op"))
	{
		std::cout << "Starting Co-op\n";
		pac::PacmanGame::SetGameMode(PacmanGame::GameMode::Coop);
		ImGui::End();
		return new WaitState{};

	}
	ImGui::End();
	return nullptr;

}

void pac::MainMenuState::OnExit()
{
	pac::PacmanGame::GoToNextLevel();
}

pac::UIState* pac::PausedState::HandleInput(const std::string& action)
{
	if(action == "paused")
	{
		std::cout << "unpausing\n";
		return new IdleState{};
	}
	return nullptr;
}

pac::UIState* pac::PausedState::Update()
{
	ImGui::Begin("Game paused", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImGui::Text("Press ESC to resume");

	ImGui::End();
	return nullptr;
}

pac::UIState* pac::InputState::HandleInput(const std::string& /*action*/)
{
	return nullptr;
}

pac::UIState* pac::InputState::Update()
{
	ImGui::Begin("Game over", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputText("Enter name: ", &m_Name[0], 4); //3 char
	if (ImGui::Button("Enter"))
	{
		std::cout << "Saving...\n";
		ImGui::End();
		return new EndState{};
	}

	ImGui::End();
	return nullptr;
}

void pac::InputState::OnExit()
{
	pac::PacmanGame::SaveGame(m_Name);
}

pac::UIState* pac::EndState::HandleInput(const std::string& /*action*/)
{
	return nullptr;
}

pac::UIState* pac::EndState::Update()
{
	//Read file and display rankings in ImGui window
	ImGui::Begin("Game over", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

	for (auto& [score, name] : m_Scores)
	{
		std::string line{ name + " -- " + std::to_string(score) };
		ImGui::Text(&line[0]);
	}

	ImGui::End();
	return nullptr;
}

void pac::EndState::OnEnter()
{
	std::fstream obj(dae::ResourceManager::GetInstance().GetDataPath() + "scores.txt");
	if (obj.eof()) {
		std::cerr << "Cannot open score file" << std::endl;
	}

	std::string line;
	while (std::getline(obj, line))
	{
		std::stringstream stream{};
		std::string nameInFile{};
		int score{};
		stream << line;
		stream >> nameInFile;
		for (int iter{}; iter < 4; ++iter)
		{
			stream.ignore();
		}
		stream >> score;
		std::cout << nameInFile << " -- " << score << std::endl;

		m_Scores.emplace_back(std::make_tuple(score, nameInFile));
	}
}

pac::UIState* pac::IdleState::HandleInput(const std::string& action)
{
	if(action == "paused")
	{
		std::cout << "Game paused\n";
		return new PausedState{};
	}
	if(action == "game over")
	{
		std::cout << "Player died\n";
		return new InputState{};
	}
	return nullptr;
}

pac::UIState* pac::IdleState::Update()
{
	return nullptr;
}

pac::UIState* pac::WaitState::HandleInput(const std::string& /*action*/)
{
	return nullptr;
}

pac::UIState* pac::WaitState::Update()
{
	if(dae::InputManager::GetInstance().GetNrOfPlayers() < 2)
	{
		ImGui::Begin("Waiting for more players...", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		ImGui::Text("Press 'Start' on a controller to join");

		ImGui::End();
		return nullptr;
	}
	return new PausedState{};
}