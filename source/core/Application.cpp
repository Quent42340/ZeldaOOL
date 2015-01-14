/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/09/2014 19:37:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#include <ctime>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include "Application.hpp"
#include "AudioPlayer.hpp"
#include "Config.hpp"
#include "GameStateManager.hpp"
#include "TimeManager.hpp"
#include "Timer.hpp"

Window Application::window;

Application::Application() {
	srand(time(nullptr));
	
	window.open();
	
	AudioPlayer::init();
	
	GameStateManager::init();
}

Application::~Application() {
	GameStateManager::free();
	
	window.free();
}

void Application::run() {
	while(window.isOpen()) {
		TimeManager::measureLastFrameDuration();
		
		GameStateManager::top()->handleEvents();
		
		TimeManager::updateGame([] {
			GameStateManager::top()->update();
		});
		
		TimeManager::drawGame([] {
			window.clear();
			
			GameStateManager::top()->render();
			
			window.update();
		});
	}
}

