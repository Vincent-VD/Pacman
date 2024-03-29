#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif


//#include <glm/glm.hpp>
#include <SDL.h>

#include "Minigin.h"
#include "PacmanGame.h"

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run([]() { pac::PacmanGame::LoadMain(); });
	return 0;
}