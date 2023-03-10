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
#include "TextureComponent2D.h"

void load()
{
	using namespace dae;
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go1 = std::make_unique<GameObject>("test");
	auto textureComp = std::make_shared<TextureComponent2D>(go1.get(), "background.tga", 0.f, 0.f, 640.f, 480.f, false);
	//textureComp->SetTexture("background.tga");
	go1->AddComponent(textureComp);
	scene.Add(std::move(go1));

	auto go = std::make_unique<GameObject>("parent");
	auto fps = std::make_shared<FPSComponent>(go.get());
	go->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<TextRenderComponent>(go.get(), "FPS: 00", font);
	auto move = std::make_shared<CircularMoveComponent>(go.get(), 50.f, 2.f);
	go->AddComponent(text);
	go->AddComponent(fps);
	go->AddComponent(move);
	scene.Add(std::move(go));

	//auto go2 = std::make_shared<GameObject>("child");
	//fps = std::make_shared<FPSComponent>(go2.get());
	////go2->GetTransform()->SetPosition(100.f, 100.f, 0.f);
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	//text = std::make_shared<TextRenderComponent>(go2.get(), "FPS: 00", font);
	//go2->SetParent(go.get(), false);
	//move = std::make_shared<CircularMoveComponent>(go2.get(), 50.f, -2.f);
	//go2->AddComponent(text);
	//go2->AddComponent(fps);
	//go2->AddComponent(move);
	//scene.Add(go2);
	
	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}