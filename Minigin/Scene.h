#ifndef SCENE
#define SCENE

#include "MiniginPCH.h"

#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	//class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void AddPersistent(std::shared_ptr<GameObject> object);
		void AddPersistentObjects(std::vector<std::shared_ptr<GameObject>> objects);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		std::vector<std::shared_ptr<GameObject>> GetAndRemovePersisentObjects();
		std::vector<std::shared_ptr<GameObject>> GetPersisentObjects() const { return m_pPersistentObjects; }

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderUI() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};
		std::vector<std::shared_ptr<GameObject>> m_pPersistentObjects{};

		std::vector<size_t> m_ItersToRemove{};

		static unsigned int m_idCounter; 
	};

}

#endif //SCENE