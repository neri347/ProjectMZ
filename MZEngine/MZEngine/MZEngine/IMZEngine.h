#pragma once
#include <windows.h>

/// MZEngine의 인터페이스
/// 클라이언트에서 인터페이스의 포인터를 통해
/// 엔진의 함수들을 실행시킨다.

class IMZEngine abstract
{
public:
	virtual ~IMZEngine() {};
	virtual bool Initialize() = 0;
	virtual void Run() = 0;
	virtual void Finalize() = 0;
};

__declspec(dllexport) IMZEngine* CreateEngine();
__declspec(dllexport) void ReleaseEngine();