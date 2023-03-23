#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "CircularMoveComponent.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "TextureComponent2D.h"

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
	auto input = std::make_shared<InputComponent>(parent.get());
	//auto move = std::make_shared<CircularMoveComponent>(parent.get(), 50.f, 2.f);
	parent->AddComponent(text);
	parent->AddComponent(fps);
	parent->AddComponent(input);
	//parent->AddComponent(move);
	//parent->SetParent(center.get(), false);

	auto command = std::make_shared<FireCommand>(parent.get());
	auto moveUp = std::make_shared<MoveCommand>(parent.get(), glm::vec2{-1.f, 0.f});
	auto moveDown = std::make_shared<MoveCommand>(parent.get(), glm::vec2{1.f, 0.f});
	auto moveLeft = std::make_shared<MoveCommand>(parent.get(), glm::vec2{0.f, -1.f});
	auto moveRight = std::make_shared<MoveCommand>(parent.get(), glm::vec2{0.f, 1.f});
	auto moveStick = std::make_shared<MoveCommand>(parent.get(), glm::vec2{0.f, 0.f});

	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_q, static_cast<unsigned int>(XInputController::ControllerButton::LeftShoulder), InputType::pressed, std::move(command));
	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_w, static_cast<unsigned int>(XInputController::ControllerButton::DPadUp), InputType::held, std::move(moveUp));
	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_s, static_cast<unsigned int>(XInputController::ControllerButton::DPadDown), InputType::held, std::move(moveDown));
	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_a, static_cast<unsigned int>(XInputController::ControllerButton::DPadLeft), InputType::held, std::move(moveLeft));
	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_d, static_cast<unsigned int>(XInputController::ControllerButton::DPadRight), InputType::held, std::move(moveRight));
	InputManager::GetInstance().AddCommand(SDL_KeyCode::SDLK_0, static_cast<unsigned int>(XInputController::ControllerButton::DPadUp), InputType::leftStick, std::move(moveStick));

	scene.Add(std::move(parent));


	//auto child = std::make_unique<GameObject>("child");
	//fps = std::make_shared<FPSComponent>(child.get());
	////go2->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//text = std::make_shared<TextRenderComponent>(child.get(), "FPS: 00", font);
	//child->SetParent(parent.get(), false);
	//move = std::make_shared<CircularMoveComponent>(child.get(), 50.f, -2.f);
	//child->AddComponent(text);
	//child->AddComponent(fps);
	//child->AddComponent(move);
	//scene.Add(go2);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}