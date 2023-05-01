#pragma once
#include "MiniginPCH.h"
namespace dae
{

	template <typename... Args>
	class Observer
	{
	public:
		virtual ~Observer() = default;

		virtual void OnNotify(Args... args) = 0;
		virtual void OnSubjectDestroyed() = 0;
	};

	template <typename... Args>
	class Subject final
	{
	public:
		Subject() = default;
		~Subject() {
			for (auto& observer : m_pObservers)
				observer->OnSubjectDestroyed();
		}
		void AddObserver(Observer<Args...>* observer) {
			m_pObservers.push_back(observer);
		}
		void RemoveObserver(Observer<Args...>* observer)
		{
			m_pObservers.erase(std::remove(
				m_pObservers.begin(),
				m_pObservers.end(), observer),
				m_pObservers.end());
		}
		void Notify(Args... args) {
			for (auto& observer : m_pObservers)
				observer->OnNotify(args...);
		}
	private:
		std::vector<Observer<Args...>*> m_pObservers{};
	};

	
}
