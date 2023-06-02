#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		Scene* GetCurrScene() const { return m_CurrScene; }
		int GetCurrSceneNumber() const { return m_CurrSceneNr; }

		void SetScene(int nr);

		void Update();
		void FixedUpdate();
		void Render();
		void RenderUI();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		Scene* m_CurrScene;
		int m_CurrSceneNr{-1};
	};
}
