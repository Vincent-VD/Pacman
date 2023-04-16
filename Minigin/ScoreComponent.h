#pragma once
#include "MiniginPCH.h"
#include "RootComponent.h"

namespace dae
{
	class TextRenderComponent;

	class ScoreComponent : public RootComponent
	{
	public:
		ScoreComponent(GameObject* pOwner);
		virtual ~ScoreComponent() override = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		void IncreaseScore(const std::string& tag);
		void ResetScore();

		int GetScore() const { return m_Score; }

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		int m_Score;
	};
}


