/*
 * =====================================================================================
 *
 *       Filename:  Font.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/09/2014 20:41:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef FONT_HPP_
#define FONT_HPP_

#include "Color.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

class Font : public Sprite {
	public:
		Font();
		~Font();
		
		void drawChar(float x, float y, char c);
		void drawString(float x, float y, std::string str, Color color = Color::text);
		void drawTextBox(float x, float y, u16 width, u16 height, std::string str, Color color = Color::text);
		
		u16 charWidth() const { return m_frameWidth; }
		u16 charHeight() const { return m_frameHeight; }
		
	private:
		Shader m_shader;
};

#endif // FONT_HPP_
