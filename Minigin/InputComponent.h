#pragma once
#include <map>

#include "InputManager.h"
#include "RootComponent.h"
#include "XInputController.h"

namespace dae
{

	class InputComponent : public RootComponent
	{
	public:
		InputComponent(GameObject* pOwner, int playerId)
			: RootComponent(pOwner)
			, m_PlayerIdx(playerId)
		{
		}

		virtual ~InputComponent() override = default;

		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;

		int GetPlayerID() const { return m_PlayerIdx; }

		virtual void Update() override {}
		virtual void FixedUpdate() override {}
		virtual void Render() const override {}

	private:
		const int m_PlayerIdx;
	};

}

