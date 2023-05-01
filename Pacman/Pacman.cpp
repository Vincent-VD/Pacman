#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <SDL.h>

#include "GameObject.h"
#include "Command.h"
#include "Font.h"
#include "FPSComponent.h"
#include "InputComponent.h"
#include "LifeComponent.h"
#include "Minigin.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "ScoreComponent.h"
#include "TextureComponent2D.h"
#include "TextRenderComponent.h"

using namespace dae;

void CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font, dae::Scene& scene);

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_unique<GameObject>("test");
	auto textureComp = std::make_shared<TextureComponent2D>(background.get(), "background.tga", 0.f, 0.f, 640.f, 480.f, false);
	//textureComp->SetTexture("background.tga");
	background->AddComponent(textureComp);
	scene.Add(std::move(background));

	auto parent = std::make_unique<GameObject>("parent");
	auto fps = std::make_shared<FPSComponent>(parent.get());
	//go->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<TextRenderComponent>(parent.get(), "FPS: 00", font);
	//auto move = std::make_shared<CircularMoveComponent>(parent.get(), 50.f, 2.f);
	parent->AddComponent(text);
	parent->AddComponent(fps);

	CreatePlayer(glm::vec3(100.f, 100.f, 0.f), true, font, scene);
	CreatePlayer(glm::vec3(200.f, 100.f, 0.f), false, font, scene);

	scene.Add(std::move(parent));
}

void CreatePlayer(glm::vec3 position, bool useKeyboard, const std::shared_ptr<dae::Font>& font, dae::Scene& scene)
{
	using namespace dae;
	auto lives = std::make_unique<GameObject>("lives");
	lives->GetTransform()->SetPosition(position.x, 0.f, 0.f);
	auto livesText = std::make_shared<TextRenderComponent>(lives.get(), "Lives: 3", font);
	lives->AddComponent(livesText);

	auto score = std::make_unique<GameObject>("score");
	score->GetTransform()->SetPosition(position.x, 10.f, 0.f);
	auto scoreText = std::make_shared<TextRenderComponent>(score.get(), "Score: 0", font);
	score->AddComponent(scoreText);

	auto player1 = std::make_unique<GameObject>("player1");
	player1->GetTransform()->SetPosition(position);
	auto input = std::make_shared<InputComponent>(player1.get());
	auto text = std::make_shared<TextRenderComponent>(player1.get(), "PLAYER " + std::to_string(input->GetPlayerID() + 1), font);
	auto lifeComp = std::make_shared<LifeComponent>(player1.get(), livesText.get());
	auto scoreComp = std::make_shared<ScoreComponent>(player1.get(), scoreText.get());
	player1->AddComponent(text);
	player1->AddComponent(input);
	player1->AddComponent(lifeComp);
	player1->AddComponent(scoreComp);

	auto hitCommand = std::make_shared<HitCommand>(player1.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonX), InputType::pressed, hitCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_h, InputType::pressed, hitCommand);

	auto scoreCommand = std::make_shared<ScoreCommand>(player1.get());
	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::ButtonY), InputType::pressed, scoreCommand);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDLK_g, InputType::pressed, scoreCommand);

	auto command = std::make_shared<FireCommand>(player1.get());
	auto moveStick = std::make_shared<MoveCommand>(player1.get(), 100.f);

	InputManager::GetInstance().AddControllerCommand(input->GetPlayerID(), static_cast<unsigned int>(XInputController::ControllerButton::LeftShoulder), InputType::pressed, command);
	if (useKeyboard) InputManager::GetInstance().AddKeyboardCommand(input->GetPlayerID(), SDL_KeyCode::SDLK_q, InputType::pressed, command);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::leftStick, moveStick, useKeyboard);
	InputManager::GetInstance().AddAxisCommand(input->GetPlayerID(), InputType::dpadAxis, moveStick, useKeyboard);

	scene.Add(std::move(lives));
	scene.Add(std::move(score));
	scene.Add(std::move(player1));

}

int main(int, char* [])
{
	/*if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;*/
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}