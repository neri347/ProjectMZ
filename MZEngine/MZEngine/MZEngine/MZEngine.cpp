#include "MZEngine.h"
#include "TimeSystem.h"
#include "RenderSystem.h"

IMZEngine* CreateEngine()
{
	return &MZCore::MZEngine::Instance();
}

void ReleaseEngine()
{
	MZCore::MZEngine::Instance().Release();
}

namespace MZCore
{

	MZEngine::MZEngine()
		: _windowTitle(L"MZEngine"),
		_timeSystem(TimeSystem::Instance()),
		_renderSystem(RenderSystem::Instance())
	{

	}

	MZEngine::~MZEngine()
	{

	}

	bool MZEngine::Initialize()
	{
		// window 창 생성
		if (!CreateWindows())
		{
			return false;
		}
		// 각 시스템 초기화
		_timeSystem.Initialize();
		_renderSystem.Initialize(_hWnd, _screenWidth, _screenHeight);
	}

	void MZEngine::Run()
	{
		MSG msg;

		// Main message loop:
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				DispatchMessage(&msg);
			}
			else
			{
				// Engine Loop
				Loop();
			}
		}
	}

	void MZEngine::Loop()
	{
		_timeSystem.Update();

		_renderSystem.Update(_timeSystem.GetDeltaTime());
		_renderSystem.Render();
	}

	void MZEngine::Finalize()
	{
		UnregisterClass(_windowTitle, _hInstance);
		_renderSystem.Finalize();
	}

	BOOL MZEngine::CreateWindows()
	{
		_hInstance = GetModuleHandle(NULL);
		RegisterWindowClass(_hInstance);
		ChangeResolution();
		if (!InitInstance(_hInstance))
		{
			return FALSE;
		}
		return TRUE;
	}

	ATOM MZEngine::RegisterWindowClass(HINSTANCE hInstance)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _windowTitle;
		wcex.hIconSm = NULL;

		return RegisterClassExW(&wcex);
	}

	void MZEngine::ChangeResolution()
	{
		// change resolution depending on display settings
		DEVMODE dmSettings;
		memset(&dmSettings, 0, sizeof(dmSettings));
		if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
		{
			MessageBox(NULL, L"Could Not Enum Display Settings", L"Error", MB_OK);
			PostQuitMessage(0);
		}

		int result = ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN);
		if (result != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL, L"Display Mode Not Compatible", L"Error", MB_OK);
			PostQuitMessage(0);
		}

		_screenWidth = dmSettings.dmPelsWidth;
		_screenHeight = dmSettings.dmPelsHeight;
	}

	BOOL MZEngine::InitInstance(HINSTANCE hInstance)
	{
		// for windowed mode
		_hWnd = CreateWindowW(_windowTitle, _windowTitle, WS_OVERLAPPEDWINDOW,
			0, 0, _screenWidth, _screenHeight, nullptr, nullptr, hInstance, nullptr);

		// for full screen mode
		/*hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
					0, 0, screenWidth, screenHeight, nullptr, nullptr, hInstance, nullptr);*/

		if (!_hWnd)
		{
			return FALSE;
		}

		SetMenu(_hWnd, NULL);
		ShowWindow(_hWnd, SW_SHOWMAXIMIZED);
		UpdateWindow(_hWnd);

		return TRUE;
	}

	LRESULT CALLBACK MZEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
}
