#pragma once
#include "MiniginPCH.h"
#include "Singleton.h"
#include <functional>
#include <map>

namespace dae
{
	class EventManager : public Singleton<EventManager>
	{
	public:
		EventManager() = default;
		virtual ~EventManager() override = default;
		EventManager(const EventManager& other) = delete;
		EventManager(EventManager&& other) noexcept = delete;
		EventManager& operator=(const EventManager& other) = delete;
		EventManager& operator=(EventManager&& other) noexcept = delete;

		void Init();

		void Update();

		void AttachEvent(const std::string& eventName, std::function<void()> eventHandle); 
		void SendEvent(const std::string& eventName);

	private:
		struct Event
		{
			const std::string eventName;
			std::function<void()> eventHandle;
		};

		static const int MAX_ARGS = 16;

		int m_Head;
		int m_Tail;

		std::string m_Events[MAX_ARGS];

		std::map<std::string, std::function<void()>> m_EventQueue{};

	};
}
