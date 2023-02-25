#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "Scene.h"
#include "TextureComponent2D.h"

void load()
{
	using namespace dae;
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>("test");
	auto fps = std::make_shared<FPSComponent>(go.get());
	go->GetTransform()->SetPosition(0, 0, 0.f);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto text = std::make_shared<TextRenderComponent>(go.get(), "FPS: 00", font);
	go->AddComponent(text);
	go->AddComponent(fps);
	scene.Add(go);

	//auto go1 = std::make_shared<GameObject>("test");
	//auto textureComp = std::make_shared<TextureComponent2D>(go1.get(), "background.tga", 0, 0, 640, 480, false);
	////textureComp->SetTexture("background.tga");
	//go1->AddComponent(textureComp);
	//scene.Add(go1);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}