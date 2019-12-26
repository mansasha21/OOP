#include "Application.h"
#include "Logger.hpp"

int main(int argc, char** argv)
{
	if(argc<4)
	{
		Logger::getInstance() << "Not enough args\n <src><back><output>";
		exit(-1);
	}
	Application app;
	app.start(argv[1], argv[2], argv[3]);
	return 0;
}
