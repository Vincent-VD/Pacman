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
std::string pac::PacmanGame::PlayerName{};

void pac::PacmanGame::LoadGame()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_unique<dae::GameObject>("test", static_cast<int>(Layers::UI));
	auto textureComp = std::make_shared<dae::TextureComponent2D>(background.get(), "background.tga", 0.f, 0.f, dae::Minigin::m_WindowInfo.m_Height, dae::Minigin::m_WindowInfo.m_Width, false);
	//textureComp->SetTexture("background.tga");
	background->AddComponent(textureComp);
	scene.Add(std::move(background));

	auto parent = std::make_unique<dae::GameObject>("parent", static_cast<int>(Layers::UI));
	auto fps = std::make_shared<dae::FPSComponent>(parent.get());
	//go->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<dae::TextRenderComponent>(parent.get(), "FPS: 00", font);
	//auto move = std::make_shared<CircularMoveComponent>(parent.get(), 50.f, 2.f);
	parent->AddComponent(text);
	parent->AddComponent(fps);

	/*CreatePlayer(glm::vec3(100.f, 100.f, 0.f), true, font, scene);
	CreatePlayer(glm::vec3(200.f, 100.f, 0.f), false, font, scene);*/

	scene.Add(std::move(parent));

	ReadLevelFromFile("Level_1.txt", font, scene);

	//Register sounds
	dae::ServiceLocator::RegisterSoundSystem(new dae::SoundLogger(new dae::FmodSoundSystem));

	auto& soundManager{ dae::ServiceLocator::GetSoundSystem() };
	soundManager.AddSound("S_Car_Pain_Edition_Overflow.wav");
	soundManager.PlaySound(dae::SoundDesc{ 0, 1.f });

	soundManager.AddSound("S_BatteringRamHit_04.wav");

	auto pauseCommand{ std::make_shared<pac::PauseCommand>() };
	auto soundCommand{ std::make_shared<pac::SoundCommand>() };
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_p, dae::InputType::pressed, pauseCommand);
	dae::InputManager::GetInstance().AddKeyboardCommand(-1, SDLK_o, dae::InputType::pressed, soundCommand);

	std::cout << "Press 'p' to pause background music\n";
	std::cout << "Press 'o' to play sound effect (sound effect will not play if other sound effect is still playing)\n";

	//Register layers & collision
	auto& collisionManager{ dae::CollisionManager::GetInstance() };

	for(int iter = 0; iter < 4; ++iter)
	{
		collisionManager.AddLayer();
	}

	collisionManager.SetLayerCollision(static_cast<int>(Layers::enemy), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::enemy));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::level), static_cast<int>(Layers::player));
	collisionManager.SetLayerCollision(static_cast<int>(Layers::player), static_cast<int>(Layers::level));

	auto menu = std::make_unique<dae::GameObject>("menu", static_cast<int>(Layers::UI));
	menu->GetTransform()->SetPosition(dae::Minigin::m_WindowInfo.m_Height / 2.f, dae::Minigin::m_WindowInfo.m_Width / 2.f, 0.f);
	auto ui = std::make_shared<UIMenuComponent>(menu.get(), "Main Menu", ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	menu->AddComponent(ui);

	scene.Add(std::move(menu));
}

void pac::PacmanGame::SaveGame()
{
}

void pac::PacmanGame::ReadLevelFromFile(const std::string& levelPath, const std::shared_ptr<dae::Font>& font, dae::Scene& scene)
{
	std::vector<std::shared_ptr<dae::GameObject>> res{};

	std::ifstream obj(dae::ResourceManager::GetInstance().GetDataPath() + levelPath);
	if (!obj.eof()) {
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
				CreatePlayer(glm::vec3(x, y, 0.f), true, font, scene);
				break;
			default:
				break;
			}
			x += m_GameField.tileSize;
		}
		y += m_GameField.tileSize;

	}
}

void pac::PacmanGame::CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font,
	dae::Scene& scene)
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
	const auto hero = std::make_shared<pac::HeroComponent>(player.get());
	const auto lifeComp = std::make_shared<pac::HealthDisplayComponent>(player.get(), hero.get(), livesText.get());
	const auto scoreComp = std::make_shared<pac::ScoreComponent>(player.get(), hero.get(), scoreText.get());
	const auto collisionComp = std::make_shared<PlayerCollisionComponent>(player.get(), Rectf{ position.x + 1.f, position.y + 1.f, m_GameField.tileSize - 3.f, m_GameField.tileSize - 3.f });
	player->AddComponent(text);
	player->AddComponent(input);
	player->AddComponent(hero);
	player->AddComponent(lifeComp);
	player->AddComponent(scoreComp);
	player->AddComponent(collisionComp);

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

	scene.Add(std::move(lives));
	scene.Add(std::move(score));
	scene.Add(std::move(player));
}

dae::GameObject* pac::PacmanGame::CreateTile(glm::vec2 position)
{
	dae::GameObject* go = new dae::GameObject("tile", static_cast<int>(Layers::level));
	const auto textureComp{ std::make_shared<dae::TextureComponent2D>(go, "Tile.png", position.x, position.y, m_GameField.tileSize, m_GameField.tileSize, false) };
	const auto collisionComp{ std::make_shared<TileCollisionComponent>(go, dae::Rectf{position.x, position.y, m_GameField.tileSize, m_GameField.tileSize}) };

	go->GetTransform()->SetPosition(position.x, position.y, 0.f);
	go->AddComponent(textureComp);
	go->AddComponent(collisionComp);

	return go;
}
