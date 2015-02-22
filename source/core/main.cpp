/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Created:  08/02/2015 21:38:59
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>

#include "Application.hpp"
#include "Exception.hpp"
#include "SDLLoader.hpp"

int main(int, char *[]) {
	SDLLoader sdlLoader;
	
	try {
		sdlLoader.load();
		
		Application app;
		
		app.run();
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Fatal error: Unknown error." << std::endl;
		return 1;
	}
	
	return 0;
}

