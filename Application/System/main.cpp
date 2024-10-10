#include "System.h"
#include <iostream>

int main() {
	
	try
	{
		System::theSystem().startSystem();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}


	return 0;
} 

