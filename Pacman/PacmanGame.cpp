#include "PacmanGame.h"

#include <algorithm>
#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Scene.h"
#include "CollisionTemplates.h"
#include "Command.h"
#include "FmodSoundSystem.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "GhostCollisionComponent.h"
#include "GhostComponent.h"
#include "GhostManager.h"
#include "GhostMoveComponent.h"
#include "HealthDisplayComponent.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "TextRenderComponent.h"
#include "TextureComponent2D.h"
#include "HeroComponent.h"
#include "LevelManager.h"
#include "Minigin.h"
#include "PelletCollisionComponent.h"
#include "PlayerCollisionComponent.h"
#include "PowerPelletCollisionComponent.h"
#include "ServiceLocator.h"
#include "SoundLogger.h"
#include "TileCollisionComponent.h"
#include "TransitionComponent.h"
#include "UIMenuComponent.h"

pac::GameField pac::PacmanGame::m_GameField{ 19.f, 19.f, 24.f, 0.f, 0.f };
std::vector<dae::GameObject*> pac::PacmanGame::m_pPlayers{};
dae::GameObject* pac::PacmanGame::m_pMenu{nullptr};
int pac::PacmanGame::m_Levels{ 1 };
bool pac::PacmanGame::m_CanAddPlayers{true};
bool pac::PacmanGame::m_CanAddGhosts{true};
pac::PacmanGame::GameMode pac::PacmanGame::m_GameMode{pac::PacmanGame::GameMode::Solo};
int pac::PacmanGame::m_MaxLevels{3};

void pac::PacmanGame::LoadMain()
{
	m_Levels = 1;
	std::cout << "starting\n";
	auto& scene = dae::SceneManager::GetInstance().CreateScene("main");

	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12) };
	auto parent = std::make_unique<dae::GameObject>("parent", static_cast<int>(Layers::UI));
	auto fps = std::make_shared<dae::FPSComponent>(parent.get());

	auto text = std::make_shared<dae::TextRenderComponent>(parent.get(), "FPS: 00", font);
	parent->AddComponent(text);
	parent->AddComponent(fps);

	scene.AddPersistent(std::move(parent));

	auto menu = std::make_unique<dae::GameObject>("menu", static_cast<int>(Layers::UI));
	menu->GetTransform()->SetPosition(dae::Minigin::m_WindowInfo.m_Height / 2.f, dae::Minigin::m_WindowInfo.m_Width / 2.f, 0.f);
	auto ui = std::make_shared<UIMenuComponent>(menu.get(), "Main Menu", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	auto comp = std::make_shared<TransitionComponent>(menu.get());
	menu->AddComponent(ui);
	menu->AddComponent(comp);

	m_pMenu = menu.get();

	scene.AddPersistent(std::move(menu));

	std::cout << "In solo mode both keyboard and mouse can be used\n";
	std::cout << "In 1 v 1 and co-op, keyboard input is disabled\n";
	std::cout << "Controls:\n\t Start/Enter: Pause game \n\t Left analogue stick/D-pad/WASD: move character\n";
	std::cout << "For testing purposes, press 'N' to got to the next level\n";

	//Register sounds
	dae::ServiceLocator::RegisterSoundSystem(new dae::SoundLogger(new dae::FmodSoundSystem));

	auto& soundManager{ dae::ServiceLocator::GetSoundSystem() };
	soundManager.AddSound("Sounds/game_start.wav");
	soundManager.AddSound("Sounds/death_1.wav");
	soundManager.AddSound("Sounds/eat_ghost.wav");
	soundManager.AddSound("Sounds/wakawaka.wav");
	soundManager.AddSound("Sounds/power_pellet.wav");
	soundManager.PlaySound(dae::SoundDesc{ 0, 1.f, true });

	//soundManager.AddSound("S_BatteringRamHit_04.wav");

	auto pauseCommand{ std::make_shared<pac::MusicPauseCommand>() };
	auto soundCommand{ std::make_shared<pac::SoundCommand>() };
	auto nextLevel{ std::make_shared<pac::Next>() };
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_p, dae::InputType::pressed, pauseCommand);
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_o, dae::InputType::pressed, soundCommand);
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_n, dae::InputType::pressed, nextLevel);

	std::cout << "Press 'p' to pause background music\n";
	std::cout << "Press 'o' to play sound effect (sound effect will not play if other sound effect is still playing)\n";

	//Register layers & collision
	auto& collisionManager{ dae::CollisionManager::GetInstance() };
	collisionManager.Init();

	for (int iter = 0; iter < 5; ++iter)
	{
		collisionManager.AddLayer();
	}

	collisionManager.SetLayerCollision(static_cast<int>(Layers::enemy), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::enemy), static_cast<int>(Layers::level));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::enemy));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::level), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::level));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::pickup));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::pickup), static_cast<int>(Layers::player));

	dae::SceneManager::GetInstance().NextScene();
}

void pac::PacmanGame::LoadLevel()
{
	ReadLevelFromFile("Level_" + std::to_string(m_Levels) + ".txt");
}

void pac::PacmanGame::SaveGame(const std::string& name)
{
	std::vector<int> scores{};
	std::vector<std::tuple<int, std::string>> scoresInFile;

	for (const auto player : m_pPlayers)
	{
		scores.emplace_back(player->GetComponent<ScoreComponent>()->GetScore());
	}

	const auto maxScore{ *std::ranges::max_element(scores) };

	scoresInFile.emplace_back(std::make_tuple(maxScore, name));

	{
		std::fstream obj(dae::ResourceManager::GetInstance().GetDataPath() + "scores.txt", std::fstream::in);
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

			scoresInFile.emplace_back(std::make_tuple(score, nameInFile));
		}
		obj.close();

		std::sort(scoresInFile.begin(), scoresInFile.end());

		obj.open(dae::ResourceManager::GetInstance().GetDataPath() + "scores.txt", std::fstream::out);
		int iter{};
		for (auto& [score, nameInFile] : scoresInFile)
		{
			if (iter == 10) break; //Save max of 10 scores
			obj << nameInFile.c_str() << " -- " << score << "\n";
			++iter;
		}
		obj.close();
	}
}

void pac::PacmanGame::GoToNextLevel()
{
	m_pMenu->GetComponent<UIMenuComponent>()->OnNotify("loading start");
	LoadLevel();
	if(m_Levels > m_MaxLevels)
	{
		m_Levels = 1;
	}
	dae::SceneManager::GetInstance().NextScene();
	m_pMenu->GetComponent<UIMenuComponent>()->OnNotify("loading end");
}

void pac::PacmanGame::ReadLevelFromFile(const std::string& levelPath/*, dae::GameObject* menu*/)
{
	std::vector<std::shared_ptr<dae::GameObject>> res{};

	auto& scene = dae::SceneManager::GetInstance().CreateScene("level_" + std::to_string(m_Levels));

	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12) };
	const auto currSceneObjs{ dae::SceneManager::GetInstance().GetCurrScene()->GetPersisentObjects() };
	dae::GameObject* menu{};
	

	std::fstream obj(dae::ResourceManager::GetInstance().GetDataPath() + levelPath);
	if (obj.eof()) {
		std::cerr << "Cannot open " << levelPath << std::endl;
	}

	int playerEnc{}; //time P has been encountered already in the file
	m_GameField.leftBound = dae::Minigin::m_WindowInfo.m_Width / 2.f - (m_GameField.cols / 2.f) * m_GameField.tileSize;
	m_GameField.rightBound = dae::Minigin::m_WindowInfo.m_Width / 2.f + (m_GameField.cols / 2.f) * m_GameField.tileSize;
	float y{ dae::Minigin::m_WindowInfo.m_Height / 2.f - (m_GameField.rows / 2.f) * m_GameField.tileSize };
	std::string line;
	while (std::getline(obj, line))
	{
		float x{ dae::Minigin::m_WindowInfo.m_Width / 2.f - (m_GameField.cols / 2.f) * m_GameField.tileSize };
		for (const char& ch : line)
		{
			
			switch(ch)
			{
			case '#':
				CreateTile({ x, y }, scene);
				break;
			case 'P':
				//if (m_Levels > 1) continue;
				for (const auto& currSceneObj : currSceneObjs)
				{
					if(const auto& menuComp{currSceneObj->GetComponent<UIMenuComponent>()})
					{
						menu = currSceneObj.get();
					}
				}
				CreatePlayer(glm::vec3(x, y, 0.f), playerEnc++, font, scene, menu);
				break;
			case 'B':
				CreateGhost({ x, y, 0.f }, GhostTypes::Blinky, scene);
				break;
			case 'C':
				CreateGhost({ x, y, 0.f }, GhostTypes::Inky, scene);
				break;
			case 'R':
				CreateGhost({ x, y, 0.f }, GhostTypes::Clyde, scene);
				break;
			case 'D':
				CreateGhost({ x, y, 0.f }, GhostTypes::Pinky, scene);
				break;
			case ' ':
				CreatePellet({ x, y }, scene);
				break;
			case 'O':
				CreatePowerPellet({ x, y }, scene);
				break;
			default:
				break;
			}
			x += m_GameField.tileSize;
		}
		y += m_GameField.tileSize;

	}
	++m_Levels;
}

void pac::PacmanGame::CreatePlayer(glm::vec3 position, int playerEnc, const std::shared_ptr<dae::Font>& font, dae::Scene& scene, dae::GameObject* menu)
{
	if(!m_pPlayers.empty() && !m_CanAddPlayers)
	{
		switch(m_GameMode)
		{
		case GameMode::Coop:
			m_pPlayers[playerEnc]->GetTransform()->SetPosition(position);
			break;
		case GameMode::Versus:
			if(playerEnc == 0)
			{
				m_pPlayers[1]->GetTransform()->SetPosition(position);
			}
			break;
		case GameMode::Solo:
			if (playerEnc == 0)
			{
				m_pPlayers[0]->GetTransform()->SetPosition(position);
			}
			break;
		}
		return;
	}

	if (!m_CanAddPlayers)
	{
		return;
	}
	using namespace dae;

	const int playerId{ InputManager::GetInstance().GetNewPlayerId() };

	auto lives = std::make_unique<GameObject>("lives", static_cast<int>(Layers::UI));
	lives->GetTransform()->SetPosition(0.f, static_cast<float>(playerId + 1) * (Minigin::m_WindowInfo.m_Height / 3.f), 0.f);
	const auto livesText = std::make_shared<TextRenderComponent>(lives.get(), "Lives: 3", font);
	lives->AddComponent(livesText);

	auto score = std::make_unique<GameObject>("score", static_cast<int>(Layers::UI));
	score->GetTransform()->SetPosition(0.f, static_cast<float>(playerId + 1) * (Minigin::m_WindowInfo.m_Height / 3.f) + 10.f, 0.f);
	const auto scoreText = std::make_shared<TextRenderComponent>(score.get(), "Score: 0", font);
	score->AddComponent(scoreText);

	auto player = std::make_unique<GameObject>("player", static_cast<int>(Layers::player));
	player->GetTransform()->SetPosition(position);
	const auto input = std::make_shared<InputComponent>(player.get(), playerId);
	const float spriteOffset{ static_cast<float>(playerId) * 32.f };
	const auto texture = std::make_shared<TextureComponent2D>(player.get(), "PacSpriteSheet.png",
															  Rectf{ position.x, position.y, m_GameField.tileSize, m_GameField.tileSize },
															  Rectf{ spriteOffset, spriteOffset, 32.f, 32.f },
															  2, true, true);
	const auto hero = std::make_shared<pac::HeroComponent>(player.get());
	const auto lifeComp = std::make_shared<pac::HealthDisplayComponent>(player.get(), hero.get(), livesText.get());
	const auto scoreComp = std::make_shared<pac::ScoreComponent>(player.get(), hero.get(), scoreText.get());
	const auto collisionComp = std::make_shared<PlayerCollisionComponent>(player.get(), Rectf{ position.x + 1.f, position.y + 1.f, m_GameField.tileSize - 3.f, m_GameField.tileSize - 3.f });
	hero->m_Menu.AddObserver(menu->GetComponent<UIMenuComponent>().get());
	hero->m_Pickup.AddObserver(&GhostManager::GetInstance());
	player->AddComponent(texture);
	player->AddComponent(input);
	player->AddComponent(hero);
	player->AddComponent(lifeComp);
	player->AddComponent(scoreComp);
	player->AddComponent(collisionComp);

	const bool useKeyboard{ (m_GameMode == GameMode::Solo) ? true : false };

	auto pauseCommand = std::make_shared<pac::GamePauseCommand>(menu);
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::Start), InputType::pressed, pauseCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_ESCAPE, InputType::pressed, pauseCommand);

	auto hitCommand = std::make_shared<pac::HitCommand>(player.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonX), InputType::pressed, hitCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_h, InputType::pressed, hitCommand);

	auto scoreCommand = std::make_shared<pac::ScoreCommand>(player.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonY), InputType::pressed, scoreCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_g, InputType::pressed, scoreCommand);

	auto moveStick = std::make_shared<pac::MoveCommand>(player.get(), 100.f);

	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::leftStick, moveStick, useKeyboard);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::dpadAxis, moveStick, useKeyboard);

	m_pPlayers.emplace_back(player.get());
	//LevelManager::GetInstance().RegisterPlayer(position, m_CurrLevel);

	scene.AddPersistent(std::move(lives));
	scene.AddPersistent(std::move(score));
	scene.AddPersistent(std::move(player));

	if (m_GameMode != GameMode::Coop)
	{
		m_CanAddPlayers = false;
	}else
	{
		if(playerEnc == 1)
		{
			m_CanAddPlayers = false;
		}
	}
	
}

void pac::PacmanGame::CreateGhost(glm::vec3 position, GhostTypes type, dae::Scene& scene)
{
	if (!m_CanAddGhosts) return;

	if(!m_pPlayers.empty())
	{
		if(m_GameMode == GameMode::Versus)
		{
			m_pPlayers[0]->GetTransform()->SetPosition(position);
		}
	}

	auto ghost = std::make_unique<dae::GameObject>("enemy", static_cast<int>(Layers::enemy));
	ghost->GetTransform()->SetPosition(position);
	const auto collision = std::make_shared<GhostCollisionComponent>(ghost.get(), dae::Rectf{ position.x, position.y, m_GameField.tileSize - 3.f, m_GameField.tileSize - 3.f });
	const auto acceptInput{ (m_GameMode == GameMode::Versus ? true : false) };
	const auto ghostComp = std::make_shared<GhostComponent>(ghost.get(), type, acceptInput);
	float spriteOffset{ (static_cast<int>(type) + 1) * 32.f };
	const auto texture = std::make_shared<dae::TextureComponent2D>(ghost.get(), "PacSpriteSheet.png",
		dae::Rectf{ position.x, position.y, m_GameField.tileSize, m_GameField.tileSize },
		dae::Rectf{ spriteOffset, spriteOffset, 32.f, 32.f },
		4, true, false);
	ghost->AddComponent(collision);
	ghost->AddComponent(texture);
	ghost->AddComponent(ghostComp);

	if(m_GameMode == GameMode::Versus)
	{
		const int playerId{dae::InputManager::GetInstance().GetNewPlayerId() };
		const auto input = std::make_shared<dae::InputComponent>(ghost.get(), playerId);
		auto moveStick = std::make_shared<pac::MoveCommand>(ghost.get(), 100.f);
		const auto currSceneObjs{ dae::SceneManager::GetInstance().GetCurrScene()->GetPersisentObjects() };
		dae::GameObject* menu{};
		for (const auto& currSceneObj : currSceneObjs)
		{
			if (const auto & menuComp{ currSceneObj->GetComponent<UIMenuComponent>() })
			{
				menu = currSceneObj.get();
			}
		}
		auto pauseCommand = std::make_shared<pac::GamePauseCommand>(menu);
		dae::InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), dae::InputType::leftStick, moveStick, false);
		dae::InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), dae::InputType::dpadAxis, moveStick, false);
		dae::InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(dae::XInputController::ControllerButton::Start), dae::InputType::pressed, pauseCommand);

		m_pPlayers.emplace_back(ghost.get());
		m_CanAddGhosts = false;
	}

	GhostManager::GetInstance().RegisterGhost(ghost.get());

	scene.Add(std::move(ghost));
	
}

void pac::PacmanGame::CreatePellet(glm::vec2 position, dae::Scene& scene)
{
	auto go = std::make_unique<dae::GameObject>("pellet", static_cast<int>(Layers::pickup));
	const auto destRect{ dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize} };
	const auto srcRect{ dae::Rectf{0.f, 0.f, 32.f, 32.f} };
	const auto textureComp{ std::make_shared<dae::TextureComponent2D>(go.get(), "Pellet.png", destRect, srcRect) };
	const auto collisionComp{ std::make_shared<PelletCollisionComponent>(go.get(), dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };

	go->GetTransform()->SetPosition(position.x, position.y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	LevelManager::GetInstance().RegisterPellet();

	scene.Add(std::move(go));
}

void pac::PacmanGame::CreatePowerPellet(glm::vec2 position, dae::Scene& scene)
{
	auto go = std::make_unique<dae::GameObject>("power pellet", static_cast<int>(Layers::pickup));
	const auto destRect{ dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize} };
	const auto srcRect{ dae::Rectf{0.f, 0.f, 32.f, 32.f} };
	const auto textureComp{ std::make_shared<dae::TextureComponent2D>(go.get(), "PowerPellet.png", destRect, srcRect) };
	const auto collisionComp{ std::make_shared<PowerPelletCollisionComponent>(go.get(), dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };

	go->GetTransform()->SetPosition(position.x, position.y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	scene.Add(std::move(go));
}

void pac::PacmanGame::CreateTile(glm::vec2 position, dae::Scene& scene)
{
	auto go = std::make_unique<dae::GameObject>("tile", static_cast<int>(Layers::level));
	const auto destRect{ dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize} };
	const auto srcRect{ dae::Rectf{0.f, 0.f, 32.f, 32.f} };
	const auto textureComp{ std::make_shared<dae::TextureComponent2D>(go.get(), "Tile_" + std::to_string(m_Levels) + ".png", destRect, srcRect) };
	const auto collisionComp{ std::make_shared<TileCollisionComponent>(go.get(), dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };

	go->GetTransform()->SetPosition(position.x, position.y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	scene.Add(std::move(go));
}
