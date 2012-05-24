#include "Application.h"

using namespace VE;
int main(int argc, const char* argv[])
{
	CApplication* game = CApplication::Create();
	if (!game)
	{
		vWarning("Error creating the application.");
		return EXIT_FAILURE;
	}

	if(game->Init())
	{
		vWarning("Error initializing the application.");
		return EXIT_FAILURE;
	}


	for (size_t i = 0; i < argc; ++i)
	{
		//std::cout << argv[i];
		if (argv[i] == std::string("-loadmap") && (i + 1) < argc)
		{
			game->LoadMap(argv[i+1]);
		}
	}

	int ret = game->Run(argc, argv);
	delete game;
	game = nullptr;
	return ret;
}