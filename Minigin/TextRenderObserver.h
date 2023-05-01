#pragma once
#include "Observer.h"

namespace dae
{
	class TextRenderComponent;

	class TextRenderObserver : public Observer<int>
	{
	public:
		TextRenderObserver(TextRenderComponent* textRenderComponent)
			: Observer<int>()
			, m_pTextRenderComponent(textRenderComponent)
		{}

		virtual void OnNotify(int score) override;
		virtual void OnSubjectDestroyed() override;

	private:
		TextRenderComponent* m_pTextRenderComponent;
	};
}


