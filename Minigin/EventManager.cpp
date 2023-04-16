#include "EventManager.h"

void dae::EventManager::Init()
{
}

void dae::EventManager::Update()
{
	if (m_Head == m_Tail)
		return;

	const auto headEvent{ m_Events[m_Head]};

	m_EventQueue.at(headEvent)();

	m_Head = (m_Head + 1) % MAX_ARGS;
}

void dae::EventManager::AttachEvent(const std::string& eventName, std::function<void()> eventHandle)
{
	m_EventQueue.insert(std::pair{eventName, eventHandle});
}

void dae::EventManager::SendEvent(const std::string& eventName)
{
	for(int iter = m_Head; iter != m_Tail; iter = (iter + 1) % MAX_ARGS)
	{
		if(m_Events[iter] == eventName)
		{
			return;
		}
	}

	assert((m_Tail + 1) % MAX_ARGS != m_Head);

	m_Events[m_Tail] = eventName;
	m_Tail = (m_Tail + 1) % MAX_ARGS;
}
