#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "RootComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextRenderComponent final : public RootComponent
	{
	public:
		TextRenderComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextRenderComponent() override = default;

		TextRenderComponent(const TextRenderComponent& other) = delete;
		TextRenderComponent(TextRenderComponent&& other) = delete;
		TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
		TextRenderComponent& operator=(TextRenderComponent&& other) = delete;

		void SetText(const std::string& text);
		//void SetPosition(float x, float y);

		virtual void Update() override;
		virtual void FixedUpdate() override {}
		virtual void Render() const override;
		
	private:
		bool m_needsUpdate;
		std::string m_text;
		//TransformComponent m_transform{};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
