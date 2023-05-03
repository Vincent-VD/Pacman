#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <SDL.h>

#include "Command.h"
#include "FPSComponent.h"
#include "Minigin.h"
#include "PacmanGame.h"

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run([]() { pac::PacmanGame::LoadGame(); });
	return 0;
}