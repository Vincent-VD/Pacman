#ifndef PACMAN_GAME
#define PACMAN_GAME

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
	enum class GhostTypes;

	struct GameField
	{
		float rows;
		float cols;
		float tileSize;
		float leftBound;
		float rightBound;
	};

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
		static void LoadLevel();
		static void SaveGame(const std::string& name);

		static GameField GetGameField() { return m_GameField; }

		static void SetGameMode(GameMode gameMode) { m_GameMode = gameMode; }
		static GameMode GetGameMode() { return m_GameMode; }

		static void CreateGhost(glm::vec3 position, GhostTypes type, dae::Scene& scene);

		static void CreatePellet(glm::vec2 position, dae::Scene& scene);

		static void CreatePowerPellet(glm::vec2 position, dae::Scene& scene);

		static void GoToNextLevel();

	private:
		//Reads level structure from file, and adds GameObjects to scene
		static void ReadLevelFromFile(const std::string& levelPath/*, dae::GameObject* menu*/);

		//Creates player and respective UI elements
		static void CreatePlayer(glm::vec3 position, int playerEnc, const std::shared_ptr<dae::Font>& font, dae::Scene& scene);
		
		static void CreateTile(glm::vec2 position, dae::Scene& scene);

		static GameField m_GameField;

		static std::vector<dae::GameObject*> m_pPlayers;

		static dae::GameObject* m_pMenu;

		static int m_Levels;

		static bool m_CanAddPlayers;
		static bool m_CanAddGhosts;

		static GameMode m_GameMode;

		static int m_MaxLevels;
	};
}

#endif //PACMAN_GAME