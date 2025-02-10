#pragma once
#include "Singleton.h"
#include <windows.h>

namespace MZCore
{
	class TimeSystem final : public Singleton<TimeSystem>
	{
	public:
		friend class Singleton<TimeSystem>;
		void Initialize();
		void Update();
		float GetDeltaTime() const;
		int GetFramePerSecond() const;

	private:
		TimeSystem() = default;

	private:
		LARGE_INTEGER _frequency;
		LARGE_INTEGER _startTime;
		LARGE_INTEGER _stopTime;
		float _deltaTime;
	};
}

