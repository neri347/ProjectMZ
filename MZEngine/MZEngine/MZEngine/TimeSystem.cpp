#include "TimeSystem.h"

namespace MZCore
{

	void TimeSystem::Initialize()
	{
		QueryPerformanceFrequency(&_frequency);
		QueryPerformanceCounter(&_startTime);
	}

	void TimeSystem::Update()
	{
		QueryPerformanceCounter(&_stopTime);
		_deltaTime = static_cast<float>(_stopTime.QuadPart - _startTime.QuadPart) / _frequency.QuadPart;
		QueryPerformanceCounter(&_startTime);
	}

	float TimeSystem::GetDeltaTime() const
	{
		return _deltaTime;
	}

	int TimeSystem::GetFramePerSecond() const
	{
		return static_cast<int>(1.0 / _deltaTime);
	}

}
