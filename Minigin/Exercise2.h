#pragma once
#include "UIWindow.h"

namespace dae
{
	class Exercise2 : public UIWindow
	{
	public:
		Exercise2(const std::string& windowTitle, ImGuiWindowFlags windowFlags = ImGuiBackendFlags_None);
		virtual ~Exercise2() override = default;
		Exercise2(const Exercise2& other) = delete;
		Exercise2(Exercise2&& other) noexcept = delete;
		Exercise2& operator=(const Exercise2& other) = delete;
		Exercise2& operator=(Exercise2&& other) noexcept = delete;

		virtual void Render() override;

	private:
		bool m_IsOpen{ true };
	};

}

