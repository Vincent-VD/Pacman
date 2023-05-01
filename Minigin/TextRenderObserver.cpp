#include "TextRenderObserver.h"

#include "TextRenderComponent.h"

void dae::TextRenderObserver::OnNotify(int score)
{
	m_pTextRenderComponent->SetText(std::to_string(score));
}

void dae::TextRenderObserver::OnSubjectDestroyed()
{
}
