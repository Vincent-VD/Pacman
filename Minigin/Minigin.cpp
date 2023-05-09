#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include <chrono>
//#include <steam_api.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "FmodSoundSystem.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include "SoundLogger.h"
#include "UIManager.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::WindowInfo  dae::Minigin::m_WindowInfo{};

dae::Minigin::Minigin(const std::string &dataPath, const WindowInfo& windowInfo)
{
	Minigin::m_WindowInfo.m_Width = windowInfo.m_Width;
	Minigin::m_WindowInfo.m_Height = windowInfo.m_Height;

	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int)windowInfo.m_Width,
		(int)windowInfo.m_Height,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	ServiceLocator::Shutdown();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& timer = GameTime::GetInstance();
	auto& UIManager = UIManager::GetInstance();
	//auto& soundManager = ServiceLocator::GetSoundSystem();
	//auto& soundManager = FmodSoundSystem::GetInstance();
	timer.Init(MsPerFrame);
	input.Init();
	UIManager.Init();

	bool doContinue = true;
	//auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	while (doContinue)
	{
		timer.Update();
		lag += timer.GetDeltaTime();

		//SteamAPI_RunCallbacks();

		doContinue = input.ProcessInput();
		while(lag >= Minigin::MsPerFrame)
		{
			sceneManager.FixedUpdate(); //Don't use the deltaTime in this function, use MsPerFrame instead
			lag -= Minigin::MsPerFrame;
		}
		sceneManager.Update();
		renderer.Render();

		const auto sleepTime = timer.GetSleepTime();
		std::this_thread::sleep_for(sleepTime);
	}
}
