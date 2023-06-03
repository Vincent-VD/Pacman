#pragma once
#include <memory>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace dae
{
	class Font;
	class Scene;
	class GameObject;
}

namespace pac
{
	class PacmanGame
	{
	public:
		PacmanGame() = default;
		~PacmanGame() = default;
		PacmanGame(const PacmanGame& other) = delete;
		PacmanGame(PacmanGame&& other) noexcept = delete;
		PacmanGame& operator=(const PacmanGame& other) = delete;
		PacmanGame& operator=(PacmanGame&& other) noexcept = delete;

		enum class GameMode
		{
			Solo,
			Versus,
			Coop
		};

		static void LoadMain();
		static void LoadGame();
		static void SaveGame(const std::string& name);

		static void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }

		static void GoToNextLevel();

	private:
		//Reads level structure from file, and adds GameObjects to scene
		static void ReadLevelFromFile(const std::string& levelPath/*, dae::GameObject* menu*/);

		//Creates player and respective UI elements
		static void CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font, dae::Scene& scene, dae::GameObject* menu);

		static dae::GameObject* CreateTile(glm::vec2 position);

		struct GameField
		{
			float rows;
			float cols;
			float tileSize;
		};

		static GameField m_GameField;

		static std::vector<dae::GameObject*> m_pPlayers;

		static int m_Levels;

		static bool m_CanAddPlayers;

		static GameMode m_GameMode;

		static int m_CurrLevel;
	};

}

