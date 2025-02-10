#pragma once

class IMZEngine;
class Client;

class Application
{
public:
	bool Initialize();
	void Run();
	void Finalize();

private:
	IMZEngine* engine;
	Client* client;
};

