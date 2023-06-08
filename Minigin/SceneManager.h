#ifndef SCENE_MANAGER
#define SCENE_MANAGER

#include "MiniginPCH.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		Scene* GetCurrScene() const { return m_CurrScene.get(); }
		int GetCurrSceneNumber() const { return m_CurrSceneNr; }

		void Reset();

		void NextScene();

		void Update();
		void FixedUpdate();
		void Render();
		void RenderUI();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<Scene> m_CurrScene;
		int m_CurrSceneNr{-1};
	};
}

#endif //SCENE_MANAGER