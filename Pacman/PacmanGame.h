#pragma once
#include <memory>
#include <string>
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

		static void LoadGame();

	private:
		//Reads level structure from file, and adds GameObjects to scene
		static void ReadLevelFromFile(const std::string& levelPath, const std::shared_ptr<dae::Font>& font, dae::Scene& scene);

		//Creates player and respective UI elements
		static void CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font, dae::Scene& scene);

		static dae::GameObject* CreateTile(glm::vec2 position);

		struct GameField
		{
			float rows;
			float cols;
			float tileSize;
		};

		static GameField m_GameField;
	};

}

