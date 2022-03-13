#include "pch.h"
#include "Application/General/application.h"
#include "Utilities/APIFactory.h"

int main()
{
#ifdef _DEBUG
	std::cout << "Starting" << std::endl;
#endif
	std::unique_ptr<RW::Application> app;
	RW::APIFactory::createApplication(app);

	app->run();
	
}