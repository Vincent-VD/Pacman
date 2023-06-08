#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <unordered_map>

#include "MiniginPCH.h"
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
		std::string GetDataPath() const { return m_dataPath; }

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_pResources;
	};
}

#endif //RESOURCE_MANAGER