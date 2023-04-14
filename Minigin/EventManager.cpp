#include "EventManager.h"

void dae::EventManager::Init()
{
}

void dae::EventManager::AttachEvent(const std::string& eventName, std::function<void()> /*eventHandle*/)
{
	std::cout << eventName;
}

void dae::EventManager::SendEvent(const std::string& eventName)
{
	std::cout << eventName;
}
