#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::SetScene(int nr)
{
	m_CurrScene = m_scenes[nr].get();
}

void dae::SceneManager::Update()
{
	m_CurrScene->Update();
}

void dae::SceneManager::FixedUpdate()
{
	m_CurrScene->FixedUpdate();
}

void dae::SceneManager::Render()
{
	m_CurrScene->Render();
}

void dae::SceneManager::RenderUI()
{
	m_CurrScene->RenderUI();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	m_CurrScene = scene.get();
	return *scene;
}
