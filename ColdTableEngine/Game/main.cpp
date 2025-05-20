#include <ColdTable/All.h>

int main()
{
	try
	{
		ColdTable::Game game({ 
			{1280, 720},
			ColdTable::Logger::LogLevel::Info
		});

		game.Run();
	}
	catch (const std::runtime_error&)
	{
		return EXIT_FAILURE;
	}
	catch (const std::exception&)
	{
		return EXIT_FAILURE;
	}
	catch (...)
	{
		return EXIT_FAILURE;
	}

	return 0;
}