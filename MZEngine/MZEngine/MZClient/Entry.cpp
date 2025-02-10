// MZClient.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Application.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	Application app;
	if (!app.Initialize())
	{
		return FALSE;
	}
	app.Run();
	app.Finalize();
	
	return 0;
}