#include "MiniginPCH.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "TextRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "LifeComponent.h"
#include "ScoreComponent.h"

dae::TextRenderComponent::TextRenderComponent(GameObject* pOwner, const std::string& text, const std::shared_ptr<Font>& font)
	: RootComponent(pOwner)
	, m_needsUpdate(true)
	, m_text(text)
	, m_font(font)
	, m_textTexture(nullptr)
{
}

void dae::TextRenderComponent::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextRenderComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextRenderComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

//void dae::TextRenderComponent::OnNotify(int arg, const GameObject* gameObject)
//{
//	if(msg == "player hit" && GetOwner()->GetTag() == "lives")
//	{
//		const int livesLeft{ gameObject->GetComponent<LifeComponent>()->GetLivesLeft() };
//		SetText("Lives: " + std::to_string(livesLeft));
//	}
//	if(msg == "score" && GetOwner()->GetTag() == "score")
//	{
//		const int score{ gameObject->GetComponent<ScoreComponent>()->GetScore() };
//		SetText("Score: " + std::to_string(score));
//	}
//}

//void dae::TextRenderComponent::SetPosition(const float x, const float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}

//void dae::TextRenderComponent::SetFont(const std::shared_ptr<Font>& font)
//{
//	m_font = font;
//}

