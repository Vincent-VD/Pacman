#ifndef MINIGIN_PCH
#define MINIGIN_PCH

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <list>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma warning (push, 0)
#pragma warning (disable:4201)

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <SDL.h>
#pragma warning (pop)

#endif //MINIGIN_PCH