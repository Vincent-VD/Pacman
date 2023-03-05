#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "Time.h"

using namespace dae;

FPSComponent::FPSComponent(GameObject* pOwner)
	: RootComponent(pOwner)
{

}

glm::uint32_t FPSComponent::GetFPS() const
{
	return m_FPS;
}

void FPSComponent::Update()
{
	if (!m_pText)
		m_pText = GetOwner()->GetComponent<TextRenderComponent>();

	if(m_pText == nullptr)
	{
		std::cout << "FPS Renderer could not receive Text Render Component!\n";
		return;
	}

	m_ElapsedSec = Time::GetInstance().GetDeltaTime();
	m_FPS = Time::GetInstance().GetFPS();
	m_UpdateTimer += m_ElapsedSec;
	if (m_UpdateTimer >= m_UpdateInterval)
	{
		if (m_pText)
		{
			m_pText->SetText("FPS: " + std::to_string(m_FPS));
		}
		m_UpdateTimer = 0.f;
	}
}

void FPSComponent::FixedUpdate()
{

}