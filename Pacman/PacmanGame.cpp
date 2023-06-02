#include "PacmanGame.h"

#include <iostream>
#include <fstream>

#include "GameObject.h"
#include "Scene.h"
#include "CollisionTemplates.h"
#include "Command.h"
#include "FmodSoundSystem.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "HealthDisplayComponent.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "TextRenderComponent.h"
#include "TextureComponent2D.h"
#include "HeroComponent.h"
#include "Minigin.h"
#include "PlayerCollisionComponent.h"
#include "ServiceLocator.h"
#include "SoundLogger.h"
#include "TileCollisionComponent.h"
#include "UIMenuComponent.h"

pac::PacmanGame::GameField pac::PacmanGame::m_GameField{ 19.f, 19.f, 24.f };
std::vector<dae::GameObject*> pac::PacmanGame::m_pPlayers{2, nullptr};
int pac::PacmanGame::m_Levels{ 1 };
bool pac::PacmanGame::m_CanAddPlayers{true};

void pac::PacmanGame::LoadGame()
{
	//Register layers & collision
	auto& collisionManager{ dae::CollisionManager::GetInstance() };
	collisionManager.Init();

	for (int iter = 0; iter < 4; ++iter)
	{
		collisionManager.AddLayer();
	}

	collisionManager.SetLayerCollision(static_cast<int>(Layers::enemy), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::enemy));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::level), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::level));

	ReadLevelFromFile("Level_1.txt"/*, font, scene, menu.get()*/);
	ReadLevelFromFile("Level_2.txt"/*, font, scene, menu.get()*/);

	//Register sounds
	dae::ServiceLocator::RegisterSoundSystem(new dae::SoundLogger(new dae::FmodSoundSystem));

	auto& soundManager{ dae::ServiceLocator::GetSoundSystem() };
	soundManager.AddSound("S_Car_Pain_Edition_Overflow.wav");
	soundManager.PlaySound(dae::SoundDesc{ 0, 1.f });

	soundManager.AddSound("S_BatteringRamHit_04.wav");

	auto pauseCommand{ std::make_shared<pac::MusicPauseCommand>() };
	auto soundCommand{ std::make_shared<pac::SoundCommand>() };
	auto nextLevel{ std::make_shared<pac::Next>() };
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_p, dae::InputType::pressed, pauseCommand);
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_o, dae::InputType::pressed, soundCommand);
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_n, dae::InputType::pressed, nextLevel);

	std::cout << "Press 'p' to pause background music\n";
	std::cout << "Press 'o' to play sound effect (sound effect will not play if other sound effect is still playing)\n";

	dae::SceneManager::GetInstance().SetScene(0);
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

void pac::PacmanGame::ReadLevelFromFile(const std::string& levelPath/*, const std::shared_ptr<dae::Font>& font, dae::Scene& scene, dae::GameObject* menu*/)
{
	std::vector<std::shared_ptr<dae::GameObject>> res{};

	auto& scene = dae::SceneManager::GetInstance().CreateScene("level_" + std::to_string(m_Levels));

	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12) };
	std::unique_ptr<dae::GameObject> menu{};
	if(m_CanAddPlayers)
	{	auto parent = std::make_unique<dae::GameObject>("parent", static_cast<int>(Layers::UI));
		auto fps = std::make_shared<dae::FPSComponent>(parent.get());
		
		auto text = std::make_shared<dae::TextRenderComponent>(parent.get(), "FPS: 00", font);
		parent->AddComponent(text);
		parent->AddComponent(fps);

		scene.AddPersistent(std::move(parent));

		menu = std::make_unique<dae::GameObject>("menu", static_cast<int>(Layers::UI));
		menu->GetTransform()->SetPosition(dae::Minigin::m_WindowInfo.m_Height / 2.f, dae::Minigin::m_WindowInfo.m_Width / 2.f, 0.f);
		auto ui = std::make_shared<UIMenuComponent>(menu.get(), "Main Menu", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		menu->AddComponent(ui);
	}
	

	std::fstream obj(dae::ResourceManager::GetInstance().GetDataPath() + levelPath);
	if (obj.eof()) {
		std::cerr << "Cannot open " << levelPath << std::endl;
	}

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
				scene.Add(std::unique_ptr<dae::GameObject>(CreateTile({ x, y })));
				break;
			case 'P':
				if (!m_CanAddPlayers) continue;
				for (auto player : m_pPlayers)
				{
					if(!player)
					{
						CreatePlayer(glm::vec3(x, y, 0.f), true, font, scene, menu.get());
					}
				}
				break;
			default:
				break;
			}
			x += m_GameField.tileSize;
		}
		y += m_GameField.tileSize;

	}
	scene.AddPersistent(std::move(menu));
	++m_Levels;
	m_CanAddPlayers = false;
}

void pac::PacmanGame::CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font, dae::Scene& scene, dae::GameObject* menu)
{
	using namespace dae;
	auto lives = std::make_unique<GameObject>("lives", static_cast<int>(Layers::UI));
	lives->GetTransform()->SetPosition(position.x, 0.f, 0.f);
	auto livesText = std::make_shared<TextRenderComponent>(lives.get(), "Lives: 3", font);
	lives->AddComponent(livesText);

	auto score = std::make_unique<GameObject>("score", static_cast<int>(Layers::UI));
	score->GetTransform()->SetPosition(position.x, 10.f, 0.f);
	auto scoreText = std::make_shared<TextRenderComponent>(score.get(), "Score: 0", font);
	score->AddComponent(scoreText);

	auto player = std::make_unique<GameObject>("player", static_cast<int>(Layers::player));
	player->GetTransform()->SetPosition(position);
	const auto input = std::make_shared<InputComponent>(player.get());
	const auto text = std::make_shared<TextRenderComponent>(player.get(), "PLAYER " + std::to_string(input->GetPlayerID() + 1), font);
	const auto texture = std::make_shared<TextureComponent2D>(player.get(), "PacSpriteSheet.png", Rectf{ position.x, position.y, m_GameField.tileSize, m_GameField.tileSize }, Rectf{ 0.f, 0.f, 32.f, 32.f }, 2, true, true);
	const auto hero = std::make_shared<pac::HeroComponent>(player.get());
	const auto lifeComp = std::make_shared<pac::HealthDisplayComponent>(player.get(), hero.get(), livesText.get());
	const auto scoreComp = std::make_shared<pac::ScoreComponent>(player.get(), hero.get(), scoreText.get());
	const auto collisionComp = std::make_shared<PlayerCollisionComponent>(player.get(), Rectf{ position.x + 1.f, position.y + 1.f, m_GameField.tileSize - 3.f, m_GameField.tileSize - 3.f });
	hero->m_Menu.AddObserver(menu->GetComponent<UIMenuComponent>().get());
	player->AddComponent(texture);
	player->AddComponent(text);
	player->AddComponent(input);
	player->AddComponent(hero);
	player->AddComponent(lifeComp);
	player->AddComponent(scoreComp);
	player->AddComponent(collisionComp);

	auto pauseCommand = std::make_shared<pac::GamePauseCommand>(menu);
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::Start), InputType::pressed, pauseCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_ESCAPE, InputType::pressed, pauseCommand);

	auto hitCommand = std::make_shared<pac::HitCommand>(player.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonX), InputType::pressed, hitCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_h, InputType::pressed, hitCommand);

	auto scoreCommand = std::make_shared<pac::ScoreCommand>(player.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonY), InputType::pressed, scoreCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_g, InputType::pressed, scoreCommand);

	auto command = std::make_shared<FireCommand>(player.get());
	auto moveStick = std::make_shared<pac::MoveCommand>(player.get(), 100.f);

	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::LeftShoulder), InputType::pressed, command);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDL_KeyCode::SDLK_q, InputType::pressed, command);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::leftStick, moveStick, useKeyboard);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::dpadAxis, moveStick, useKeyboard);

	m_pPlayers.emplace_back(player.get());

	scene.AddPersistent(std::move(lives));
	scene.AddPersistent(std::move(score));
	scene.AddPersistent(std::move(player));
}

dae::GameObject* pac::PacmanGame::CreateTile(glm::vec2 position)
{
	dae::GameObject* go = new dae::GameObject("tile", static_cast<int>(Layers::level));
	const auto textureComp{ std::make_shared<dae::TextureComponent2D>(go, "Tile_" + std::to_string(m_Levels) + ".png", dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };
	const auto collisionComp{ std::make_shared<TileCollisionComponent>(go, dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };

	go->GetTransform()->SetPosition(position.x, position.y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	return go;
}
