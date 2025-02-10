#pragma once
#include "Resource.h"
#include "IMZEngine.h"
#include "Singleton.h"

namespace MZCore
{
	class TimeSystem;
	class RenderSystem;
}

namespace MZCore
{

	class MZEngine : public IMZEngine, public Singleton<MZEngine>
	{
	public:
		friend class Singleton<MZEngine>;
		virtual ~MZEngine();
		virtual bool Initialize() override;
		virtual void Run() override;
		virtual void Finalize() override;

	private:
		MZEngine();
		void Loop();

	private:
		BOOL CreateWindows();
		ATOM RegisterWindowClass(HINSTANCE hInstance);
		void ChangeResolution();
		BOOL InitInstance(HINSTANCE hInstance);
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		
	private:
		// window 창 관련
		HINSTANCE _hInstance;
		HWND _hWnd;
		WCHAR _windowTitle[100];
		UINT _screenWidth;
		UINT _screenHeight;

	private:
		// 각 시스템들
		MZCore::TimeSystem& _timeSystem;
		MZCore::RenderSystem& _renderSystem;
	};

}