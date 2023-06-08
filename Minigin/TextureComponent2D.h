#ifndef TEXTURE_COMPONENT_2D
#define TEXTURE_COMPONENT_2D

#include "RootComponent.h"
#include "Structs.h"

struct SDL_Texture;
namespace dae
{
	class GameObject;
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D;

	class TextureComponent2D : public RootComponent
	{
	public:
		TextureComponent2D(GameObject* pOwner, const std::string& filename, const Rectf& dest, const Rectf& source, int nrOfFrames = 0, bool isDynamic = false, bool isAnimated = false);
		virtual ~TextureComponent2D() override = default;

		TextureComponent2D(const TextureComponent2D& other) = delete;
		TextureComponent2D(TextureComponent2D&& other) noexcept = delete;
		TextureComponent2D& operator=(const TextureComponent2D& other) = delete;
		TextureComponent2D& operator=(TextureComponent2D&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		void Render() const override;

		int GetFrame() const { return m_CurrFrame; }
		void SetFrame(int frame);

		Rectf GetSourceRect() const { return m_SourceRect; }
		void SetSourceRect(const Rectf& srcRect);

		std::pair<float, float> GetTextureDimensions() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
		Rectf m_DestRect;
		Rectf m_SourceRect;
		const bool m_IsDynamic;
		const bool m_IsAnimated;
		const int m_NrOfFrames;
		int m_CurrFrame{};
		const float m_MaxAnimTime{ 0.5f };
		float m_CurrAnimTime{};

	};
}

#endif //TEXTURE_COMPONENT_2D