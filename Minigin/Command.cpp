#include "Command.h"

#include "LifeComponent.h"
#include "ScoreComponent.h"

void dae::MoveCommand::Execute(const InputAction& inputAction)
{
	auto elapsedSec{ GameTime::GetInstance().GetDeltaTime() };
	auto currentPos{ GetActor()->GetTransform()->GetWorldPosition() };
	if (glm::length2(inputAction.leftStick) > FLT_EPSILON * FLT_EPSILON)
	{
		GetActor()->GetTransform()->SetPosition(currentPos + m_Speed * glm::vec3(inputAction.leftStick.x, -inputAction.leftStick.y, 0.f) * elapsedSec);
	}
}

void dae::HitCommand::Execute([[maybe_unused]] const InputAction& inputAction)
{
	auto lifeComp{GetActor()->GetComponent<LifeComponent>()};
	assert(lifeComp);
	lifeComp->Hit();
}

void dae::ScoreCommand::Execute([[maybe_unused]] const InputAction& inputAction)
{
	auto scoreComp{ GetActor()->GetComponent<ScoreComponent>() };
	assert(scoreComp);
	scoreComp->IncreaseScore("orb");
}
