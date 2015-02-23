/*
 * =====================================================================================
 *
 *       Filename:  Window.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/09/2014 19:50:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <memory>

#include "SDLHeaders.hpp"
#include "Shader.hpp"
#include "Types.hpp"

class Window {
	public:
		Window();
		Window(const Window &) = delete;
		Window(Window &&) = delete;
		
		void initGL();
		
		void clear();
		void update();
		
		bool isOpen() const { return m_isOpen; }
		void close() { m_isOpen = false; }
		
	private:
		using SDL_WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
		using SDL_GLContextPtr = std::unique_ptr<void, decltype(&SDL_GL_DeleteContext)>;
		
		SDL_WindowPtr m_window{nullptr, SDL_DestroyWindow};
		SDL_GLContextPtr m_context{nullptr, SDL_GL_DeleteContext};
		
		Shader m_shader;
		
		bool m_isOpen = false;
		
		u16 m_width = 0;
		u16 m_height = 0;
};

#endif // WINDOW_HPP_
