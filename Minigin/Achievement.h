#pragma once
#include "Observer.h"

namespace dae
{
	class Achievement : public Observer<std::string>
	{
	public:
		Achievement();

		virtual void OnNotify(std::string args) override;
		virtual void OnSubjectDestroyed() override;
	};
}
