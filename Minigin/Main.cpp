#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <steam_api.h>

#include "Achievement.h"
#include "CircularMoveComponent.h"
#include "Command.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "LifeComponent.h"
#include "ScoreComponent.h"
#include "TextureComponent2D.h"
#include "UIManager.h"

void load()
{
	using namespace dae;
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_unique<GameObject>("test");
	auto textureComp = std::make_shared<TextureComponent2D>(background.get(), "background.tga", 0.f, 0.f, 640.f, 480.f, false);
	//textureComp->SetTexture("background.tga");
	background->AddComponent(textureComp);
	scene.Add(std::move(background));

	/*auto center = std::make_unique<GameObject>("source");
	center->GetTransform()->SetPosition(100.f, 100.f, 0.f);*/

	auto parent = std::make_unique<GameObject>("parent");
	auto fps = std::make_shared<FPSComponent>(parent.get());
	//go->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<TextRenderComponent>(parent.get(), "FPS: 00", font);
	//auto move = std::make_shared<CircularMoveComponent>(parent.get(), 50.f, 2.f);
	parent->AddComponent(text);
	parent->AddComponent(fps);
	//parent->AddComponent(move);
	//parent->SetParent(center.get(), false);

	auto lives = std::make_unique<GameObject>("hud");
	lives->GetTransform()->SetPosition(100.f, 0.f, 0.f);
	auto livesText = std::make_shared<TextRenderComponent>(lives.get(), "Lives: 3", font);
	lives->AddComponent(livesText);

	auto score = std::make_unique<GameObject>("hud");
	score->GetTransform()->SetPosition(100.f, 10.f, 0.f);
	auto scoreText = std::make_shared<TextRenderComponent>(score.get(), "Score: 0", font);
	score->AddComponent(scoreText);

	auto player1 = std::make_unique<GameObject>("player1");
	player1->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	text = std::make_shared<TextRenderComponent>(player1.get(), "PLAYER 1", font);
	auto input = std::make_shared<InputComponent>(player1.get());
	auto lifeComp = std::make_shared<LifeComponent>(player1.get()/*, livesText.get()*/);
	auto scoreComp = std::make_shared<ScoreComponent>(player1.get(), scoreText.get());
	auto achievementObserver = new Achievement();
	player1->AddComponent(text);
	player1->AddComponent(input);
	player1->AddComponent(lifeComp);
	player1->AddComponent(scoreComp);
	player1->AddObserver(achievementObserver);
	player1->AddObserver(livesText.get());

	auto hitCommand = std::make_shared<HitCommand>(player1.get());
	InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_h, InputType::pressed, hitCommand);

	auto scoreCommand = std::make_shared<ScoreCommand>(player1.get());
	InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_g, InputType::pressed, scoreCommand);

	auto command = std::make_shared<FireCommand>(player1.get());
	auto moveStick = std::make_shared<MoveCommand>(player1.get(), 100.f);

	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::LeftShoulder), InputType::pressed, command);
	InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDL_KeyCode::SDLK_q, InputType::pressed, command);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::leftStick, moveStick, true);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::dpadAxis, moveStick, true);

	auto player2 = std::make_unique<GameObject>("player2");
	player2->GetTransform()->SetPosition(200.f, 100.f, 0.f);
	text = std::make_shared<TextRenderComponent>(player2.get(), "PLAYER 2", font);
	input = std::make_shared<InputComponent>(player2.get());
	player2->AddComponent(text);
	player2->AddComponent(input);
	
	moveStick = std::make_shared<MoveCommand>(player2.get(), 200.f);

	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::LeftShoulder), InputType::pressed, command);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::leftStick, moveStick);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::dpadAxis, moveStick);

	scene.Add(std::move(parent));
	scene.Add(std::move(player1));
	scene.Add(std::move(player2));
	scene.Add(std::move(lives));
	scene.Add(std::move(score));
}

int main(int, char*[])
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}