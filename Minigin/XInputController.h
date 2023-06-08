#ifndef XINPUT_CONTROLLER
#define XINPUT_CONTROLLER

#include <map>
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class XInputController
	{
		class XInputControllerImpl;
		std::unique_ptr<XInputControllerImpl> m_pImpl;
	public:
		enum class ControllerButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftStick = 0x0040,
			RightStick = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
		};

		void Update() const;
		bool IsHeld(int playerId, unsigned int button) const;
		bool IsPressed(int playerId, unsigned int button) const;
		bool IsReleased(int playerId, unsigned int button) const;

		float GetLeftTriggerPressure(int playerId) const;
		float GetRightTriggerPressure(int playerId) const;
		glm::vec2 GetLeftStickValues(int playerId) const;
		glm::vec2 GetRightStickValues(int playerId) const;
		glm::vec2 GetDPadAxisValues(int playerId) const;

		//Returns amount of controllers connected
		int GetConnectedControllers() const;

		int GetMaxPlayerCount();

		XInputController();
		~XInputController();
		XInputController(const XInputController& other) = delete;
		XInputController(XInputController&& other) noexcept = delete;
		XInputController& operator=(const XInputController& other) = delete;
		XInputController& operator=(XInputController&& other) noexcept = delete;

	private:
		const std::map<unsigned int, glm::vec2> m_DPadDirections  {
		   { static_cast<unsigned>(ControllerButton::DPadUp), { 0, 1 } },
		   { static_cast<unsigned>(ControllerButton::DPadDown), { 0, -1 } },
		   { static_cast<unsigned>(ControllerButton::DPadLeft), { -1, 0 } },
		   { static_cast<unsigned>(ControllerButton::DPadRight), { 1, 0 } }
		};
	};
}

#endif //XINPUT_CONTROLLER