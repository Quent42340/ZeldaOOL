/*
 * =====================================================================================
 *
 *       Filename:  EventHandler.hpp
 *
 *    Description:  
 *
 *        Created:  08/02/2015 22:19:55
 *       Compiler:  gcc
 *
 *         Author:  Quentin Bazin, <gnidmoo@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include "ApplicationWindow.hpp"

class EventHandler {
	public:
		static void processSDLEvents(ApplicationWindow &window);
};

#endif // EVENTHANDLER_HPP_