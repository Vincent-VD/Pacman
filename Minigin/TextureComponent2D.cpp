#include "MiniginPCH.h"
#include "TextureComponent2D.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
//#include "TransformComponent.h"

using namespace dae;

Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}

TextureComponent2D::TextureComponent2D(GameObject* pOwner, const std::string& filename, float left, float bottom, float width, float height, bool isDynamic)
	: RootComponent(pOwner)
	, m_Rect(left, bottom, width, height)
	, m_IsDynamic(isDynamic)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent2D::Update()
{
	if (m_IsDynamic)
	{
		const glm::vec3 pos{ GetOwner()->GetTransform()->GetPosition() };

		m_Rect.left = pos.x;
		m_Rect.bottom = pos.y;
	}
}

void TextureComponent2D::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture, m_Rect.left, m_Rect.bottom, m_Rect.width, m_Rect.height);
}

std::pair<float, float> TextureComponent2D::GetTextureDimensions() const
{
	int width{}, height{};
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	return { static_cast<float>(width), static_cast<float>(height) };
}
