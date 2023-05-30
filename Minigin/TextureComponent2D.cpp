#include "MiniginPCH.h"
#include "TextureComponent2D.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GameTime.h"
//#include "TransformComponent.h"

using namespace dae;

TextureComponent2D::TextureComponent2D(GameObject* pOwner, const std::string& filename, const Rectf& dest, const Rectf& source, int nrOfFrames, bool isDynamic, bool isAnimated)
	: RootComponent(pOwner)
	, m_DestRect(dest)
	, m_SourceRect(source)
	, m_IsDynamic(isDynamic)
	, m_IsAnimated(isAnimated)
	, m_NrOfFrames(nrOfFrames)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent2D::Update()
{
	if (m_IsDynamic)
	{
		const glm::vec3 pos{ GetOwner()->GetTransform()->GetWorldPosition() };

		m_DestRect.left = pos.x;
		m_DestRect.bottom = pos.y;
	}

	if(m_IsAnimated)
	{
		const float delta{ GameTime::GetInstance().GetDeltaTime() };
		m_CurrAnimTime += delta;
		if(m_CurrAnimTime >= m_MaxAnimTime)
		{
			m_CurrAnimTime = 0.f;
			m_CurrFrame = (m_CurrFrame + 1) % m_NrOfFrames;
			m_SourceRect.left = m_SourceRect.width * static_cast<float>(m_CurrFrame);
		}
	}

}

void TextureComponent2D::Render() const
{
	if(m_IsAnimated)
	{
		Renderer::GetInstance().RenderTextureAnimation(*m_pTexture, m_SourceRect, m_DestRect);
		return;
	}
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_DestRect.left, m_DestRect.bottom, m_DestRect.width, m_DestRect.height);
}

std::pair<float, float> TextureComponent2D::GetTextureDimensions() const
{
	int width{}, height{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	return { static_cast<float>(width), static_cast<float>(height) };
}
