#include "Application.h"
#include "Client.h"
#include "../MZEngine/IMZEngine.h"

bool Application::Initialize()
{
	engine = CreateEngine();
	if(!engine->Initialize())
	{
		return false;
	}
	client = new Client();
	client->Initialize();
	return true;
}

void Application::Run()
{
	engine->Run();
}

void Application::Finalize()
{
	engine->Finalize();
	ReleaseEngine();
}
