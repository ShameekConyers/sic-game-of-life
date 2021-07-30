#include "src/Env.hpp"
#include <iostream>

int main()
{
	Env env;
	int status_code = env.initialize();
	if (status_code != 0) return status_code;

	env.runLoop();
	env.shutdown();
}
