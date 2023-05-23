#pragma once
#include <memory>
#include <string>

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
		TextureComponent2D(GameObject* pOwner, const std::string& filename, float left, float bottom, float width, float height, bool isDynamic);
		virtual ~TextureComponent2D() override = default;

		TextureComponent2D(const TextureComponent2D& other) = delete;
		TextureComponent2D(TextureComponent2D&& other) noexcept = delete;
		TextureComponent2D& operator=(const TextureComponent2D& other) = delete;
		TextureComponent2D& operator=(TextureComponent2D&& other) noexcept = delete;

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		void Render() const override;

		std::pair<float, float> GetTextureDimensions() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
		Rectf m_Rect;
		const bool m_IsDynamic;

	};
}
