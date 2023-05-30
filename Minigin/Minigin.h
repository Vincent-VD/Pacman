#pragma once
#include <string>
#include <functional>

namespace dae
{

	struct WindowInfo
	{
		float m_Width{};
		float m_Height{};
	};

	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, const WindowInfo& windowInfo = {640.f, 480.f});
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		static WindowInfo m_WindowInfo;
		static void SetPaused(bool paused) { m_IsPaused = paused; }
		static bool GetPaused() { return m_IsPaused; }


	private:
		static constexpr float MsPerFrame = 16.6f;
		static bool m_IsPaused;
	};
}